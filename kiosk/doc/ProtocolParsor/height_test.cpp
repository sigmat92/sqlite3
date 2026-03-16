#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cstring>
#include <iomanip>
#include <chrono>
#include <thread>

#define SERIAL_PORT "/dev/ttyACM0"   
#define BAUDRATE B9600

int openSerial(const char* port)
{
    int fd = open(port, O_RDWR | O_NOCTTY | O_SYNC);

    if (fd < 0)
    {
        perror("open");
        return -1;
    }

    struct termios tty;
    memset(&tty, 0, sizeof tty);

    if (tcgetattr(fd, &tty) != 0)
    {
        perror("tcgetattr");
        return -1;
    }

    cfsetospeed(&tty, BAUDRATE);
    cfsetispeed(&tty, BAUDRATE);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_iflag = 0;
    tty.c_oflag = 0;
    tty.c_lflag = 0;

    tty.c_cflag |= (CLOCAL | CREAD);

    tty.c_cflag &= ~(PARENB | PARODD);
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    tty.c_cc[VMIN]  = 0;
    tty.c_cc[VTIME] = 10;

    tcsetattr(fd, TCSANOW, &tty);

    return fd;
}

void hexDump(uint8_t* data, int len)
{
    for(int i=0;i<len;i++)
    {
        std::cout << std::hex << std::setw(2)
                  << std::setfill('0')
                  << (int)data[i] << " ";
    }
    std::cout << std::dec << std::endl;
}

void decodeHeight(uint8_t* buf, int len)
{
    for(int i=0;i<len-4;i++)
    {
        if(buf[i] == 0xF7)
        {
            uint8_t nob = buf[i+1];

            if(nob == 3)
            {
                uint8_t status = buf[i+2];
                uint8_t height = buf[i+3];
                uint8_t unit   = buf[i+4];

                std::cout << "HEIGHT FRAME: ";
                hexDump(&buf[i],5);

                if(height == 0x80)
                {
                    std::cout << "Height sensor idle\n";
                }
                else
                {
                    std::cout << "Height = "
                              << (int)height
                              << " cm\n";
                }
            }
        }
    }
}

int main()
{
    int fd = openSerial(SERIAL_PORT);

    if(fd < 0)
    {
        std::cout << "Failed to open serial\n";
        return 1;
    }

    std::cout << "Serial opened\n";

    uint8_t height_cmd[3] = {0x96,0xAA,0xF7};

    write(fd,height_cmd,3);

    std::cout << "Sent height request\n";

    std::cout << "Waiting 2 seconds for sensor response...\n";

    std::this_thread::sleep_for(std::chrono::seconds(2));

    uint8_t buffer[256];

    while(true)
    {
        int n = read(fd,buffer,sizeof(buffer));

        if(n > 0)
        {
            std::cout << "RX ("<<n<<" bytes): ";
            hexDump(buffer,n);

            decodeHeight(buffer,n);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    close(fd);
}
