#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>
#include <vector>

#define DEV1 "/dev/ttyACM0"
#define DEV2 "/dev/ttyACM1"

#define CTRL_PULSE   0xF2
#define CTRL_SPO2    0xF4
#define CTRL_NIBP    0xF5
#define CTRL_HEIGHT  0xF7
#define CTRL_WEIGHT  0xF8
#define CTRL_TEMP    0xFA
#define CTRL_FW      0xFB

//------------------------------------------------------------
// UART OPEN
//------------------------------------------------------------

int open_uart(const char *dev)
{
    int fd = open(dev,O_RDWR | O_NOCTTY | O_SYNC);

    if(fd < 0)
        return -1;

    struct termios tty;
    memset(&tty,0,sizeof tty);

    if(tcgetattr(fd,&tty)!=0)
    {
        close(fd);
        return -1;
    }

    cfsetospeed(&tty,B9600);
    cfsetispeed(&tty,B9600);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_iflag = 0;
    tty.c_oflag = 0;
    tty.c_lflag = 0;

    tty.c_cc[VMIN]  = 1;
    tty.c_cc[VTIME] = 1;

    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~(PARENB | PARODD);
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    tcsetattr(fd,TCSANOW,&tty);

    return fd;
}

//------------------------------------------------------------
// SEND COMMAND
//------------------------------------------------------------

void send_cmd(int fd,const std::vector<uint8_t>& cmd)
{
    write(fd,cmd.data(),cmd.size());
}

//------------------------------------------------------------
// PROTOCOL PARSER
//------------------------------------------------------------

class ProtocolParser
{

public:

    void parse(uint8_t byte)
    {
        buffer.push_back(byte);

        if(buffer.size() < 2)
            return;

        uint8_t ctrl = buffer[0];
        uint8_t nob  = buffer[1];

        if(buffer.size() < nob + 2)
            return;

        std::vector<uint8_t> data(buffer.begin()+2,
                                  buffer.begin()+2+nob);

        handleFrame(ctrl,nob,data);

        buffer.clear();
    }

private:

    std::vector<uint8_t> buffer;

    //--------------------------------------------------------

    void handleFrame(uint8_t ctrl,
                     uint8_t nob,
                     std::vector<uint8_t>& data)
    {

        switch(ctrl)
        {

        //----------------------------------------------------
        case CTRL_PULSE:
        {
            int bpm = data[0];

            if(bpm < 30)
                std::cout<<"Pulse Error\n";
            else
                std::cout<<"Pulse Rate: "<<bpm<<" bpm\n";

            break;
        }

        //----------------------------------------------------
        case CTRL_SPO2:
        {
            int spo2 = data[0];

            if(spo2 > 100)
                std::cout<<"SpO2 Error\n";
            else
                std::cout<<"SpO2: "<<spo2<<" %\n";

            break;
        }

        //----------------------------------------------------
        case CTRL_NIBP:
        {

            if(nob == 4)
            {
                int status = data[0];
                int sys = (data[1] << 8) | data[2];
                int dia = data[3];

                std::cout<<"NIBP\n";
                std::cout<<"Status: "<<status<<"\n";
                std::cout<<"SYS: "<<sys<<"\n";
                std::cout<<"DIA: "<<dia<<"\n";
            }

            else if(nob == 6)
            {

                int status = data[0];
                int sys = (data[1] << 8) | data[2];
                int dia = data[3];
                int map = data[4];
                int err = data[5];

                std::cout<<"NIBP Result\n";
                std::cout<<"Status: "<<status<<"\n";
                std::cout<<"SYS: "<<sys<<"\n";
                std::cout<<"DIA: "<<dia<<"\n";
                std::cout<<"MAP: "<<map<<"\n";
                std::cout<<"Error: "<<err<<"\n";

            }

            break;
        }

        //----------------------------------------------------
        case CTRL_HEIGHT:
        {
            int height = data[0];
            std::cout<<"Height: "<<height<<" cm\n";
            break;
        }

        //----------------------------------------------------
        case CTRL_WEIGHT:
        {
            int decimal = data[0];
            int fraction = data[1];
            int unit = data[2];

            float weight = decimal + (fraction/10.0);

            std::cout<<"Weight: "<<weight;

            if(unit == 0)
                std::cout<<" kg\n";
            else
                std::cout<<" lb\n";

            break;
        }

        //----------------------------------------------------
        case CTRL_TEMP:
        {

            int dec = data[0];
            int frac = data[1];
            int unit = data[2];

            float temp = dec + frac/10.0;

            std::cout<<"Temperature: "<<temp;

            if(unit==0)
                std::cout<<" C\n";
            else
                std::cout<<" F\n";

            break;
        }

        //----------------------------------------------------
        case CTRL_FW:
        {

            int code = data[0];

            if(code == 0)
                std::cout<<"Firmware Version Byte: "<<data[0]<<"\n";

            break;
        }

        //----------------------------------------------------
        default:
            std::cout<<"Unknown frame\n";
        }

    }

};

//------------------------------------------------------------
// MAIN
//------------------------------------------------------------

int main()
{

    int fd = open_uart(DEV1);

    if(fd < 0)
    {
        std::cout<<"Trying "<<DEV2<<"\n";
        fd = open_uart(DEV2);
    }

    if(fd < 0)
    {
        std::cout<<"UART open failed\n";
        return -1;
    }

    std::cout<<"UART connected\n";

    ProtocolParser parser;

    //--------------------------------------------------------
    // Example commands
    //--------------------------------------------------------

    std::vector<uint8_t> spo2_cmd = {0x96,0xAA,0xF4};
    std::vector<uint8_t> nibp_start = {0x96,0xAA,0xF5,0x01,0x01};
    std::vector<uint8_t> nibp_stop  = {0x96,0xAA,0xF5,0x01,0x00};
    std::vector<uint8_t> height_cmd = {0x96,0xAA,0xF7};
    std::vector<uint8_t> weight_cmd = {0x96,0xAA,0xF8};
    std::vector<uint8_t> temp_cmd   = {0x96,0xAA,0x54};

    //--------------------------------------------------------
    // start NIBP test
    //--------------------------------------------------------

    send_cmd(fd,nibp_start);

    uint8_t buf[256];

    while(true)
    {

        int n = read(fd,buf,sizeof(buf));

        for(int i=0;i<n;i++)
        {
            parser.parse(buf[i]);
        }

    }

    close(fd);

}
