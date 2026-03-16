/*
NIBP Communication Summary
Start Measurement
96 AA F5 01 01
Stop Measurement
96 AA F5 01 00
Response
F5 NOB DATA...

If NOB = 4

status
sys_msb
sys_lsb
dia

If NOB = 6

status
sys_msb
sys_lsb
dia
map
error
get_nibp.cpp (Production tester)
*/
#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include <chrono>

#define DEV1 "/dev/ttyACM0"
#define DEV2 "/dev/ttyACM1"

#define CTRL_NIBP 0xF5

#define NIBP_START_1 0x96
#define NIBP_START_2 0xAA

//-------------------------------------------------------
// UART
//-------------------------------------------------------

int open_uart(const char *dev)
{
    int fd = open(dev,O_RDWR | O_NOCTTY | O_SYNC);

    if(fd < 0)
        return -1;

    struct termios tty{};
    tcgetattr(fd,&tty);

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

//-------------------------------------------------------
// SEND COMMAND
//-------------------------------------------------------

void send_nibp_start(int fd)
{
    uint8_t cmd[] = {0x96,0xAA,0xF5,0x01,0x01};
    write(fd,cmd,sizeof(cmd));
}

void send_nibp_stop(int fd)
{
    uint8_t cmd[] = {0x96,0xAA,0xF5,0x01,0x00};
    write(fd,cmd,sizeof(cmd));
}

//-------------------------------------------------------
// STATUS TEXT
//-------------------------------------------------------

const char* statusText(int s)
{
    switch(s)
    {
        case 0: return "Measurement Complete";
        case 1: return "Inflating";
        case 2: return "Deflating";
        case 3: return "Measuring";
        case 4: return "Error";
        default: return "Unknown";
    }
}

//-------------------------------------------------------
// PARSER
//-------------------------------------------------------

class NibpParser
{

    std::vector<uint8_t> buffer;

public:

    bool measurementFinished=false;

    void push(uint8_t b)
    {
        buffer.push_back(b);

        if(buffer.size()<2)
            return;

        uint8_t ctrl=buffer[0];
        uint8_t nob =buffer[1];

        if(buffer.size()<nob+2)
            return;

        if(ctrl==CTRL_NIBP)
        {
            parseFrame(nob);
        }

        buffer.erase(buffer.begin(),buffer.begin()+2+nob);
    }

private:

    void parseFrame(int nob)
    {

        if(nob==4)
        {
            int status=buffer[2];
            int sys=(buffer[3]<<8)|buffer[4];
            int dia=buffer[5];

            std::cout<<"\nNIBP UPDATE\n";
            std::cout<<"Status : "<<statusText(status)<<"\n";
            std::cout<<"SYS    : "<<sys<<" mmHg\n";
            std::cout<<"DIA    : "<<dia<<" mmHg\n";

            if(status==0)
                measurementFinished=true;
        }

        else if(nob==6)
        {
            int status=buffer[2];
            int sys=(buffer[3]<<8)|buffer[4];
            int dia=buffer[5];
            int map=buffer[6];
            int err=buffer[7];

            std::cout<<"\nNIBP RESULT\n";
            std::cout<<"Status : "<<statusText(status)<<"\n";
            std::cout<<"SYS    : "<<sys<<" mmHg\n";
            std::cout<<"DIA    : "<<dia<<" mmHg\n";
            std::cout<<"MAP    : "<<map<<" mmHg\n";
            std::cout<<"Error  : "<<err<<"\n";

            measurementFinished=true;
        }
    }

};

//-------------------------------------------------------
// MAIN
//-------------------------------------------------------

int main()
{

    int fd=open_uart(DEV1);

    if(fd<0)
    {
        std::cout<<"Trying "<<DEV2<<"\n";
        fd=open_uart(DEV2);
    }

    if(fd<0)
    {
        std::cout<<"UART open failed\n";
        return -1;
    }

    std::cout<<"UART connected\n";

    send_nibp_start(fd);

    std::cout<<"Starting NIBP measurement\n";

    NibpParser parser;

    auto start=std::chrono::steady_clock::now();

    uint8_t buf[256];

    while(true)
    {

        int n=read(fd,buf,sizeof(buf));

        for(int i=0;i<n;i++)
            parser.push(buf[i]);

        if(parser.measurementFinished)
        {
            std::cout<<"\nMeasurement finished\n";
            break;
        }

        auto now=std::chrono::steady_clock::now();
        int elapsed=std::chrono::duration_cast<std::chrono::seconds>(now-start).count();

        if(elapsed>120)
        {
            std::cout<<"Timeout -> stopping NIBP\n";
            send_nibp_stop(fd);
            break;
        }
    }

    close(fd);
}
/*
Compile
g++ get_nibp.cpp -o nibp_test
Run
sudo ./nibp_test
Example Output
UART connected
Starting NIBP measurement

NIBP UPDATE
Status : Inflating
SYS    : 0
DIA    : 0

NIBP UPDATE
Status : Deflating
SYS    : 0
DIA    : 0

NIBP RESULT
Status : Measurement Complete
SYS    : 121 mmHg
DIA    : 79 mmHg
MAP    : 93 mmHg
Error  : 0

Measurement finished
How This Fits Your Kiosk Architecture

Device Layer:

Device
 └── NibpDevice
        start()
        stop()
        parseFrame()

Service Layer:

VitalsService
    └── startMeasurement()
            └── NibpDevice.start()

Controller:

NibpReady → update Model

UI:

SYS / DIA / MAP cards update

If you want, I can also show you the final architecture used in real hospital kiosks, which includes:

auto sensor detection

20-second stabilization window

multi-sensor measurement scheduler

Qt signal integration

SQLite measurement logging

This will match exactly the architecture described earlier.
*/
