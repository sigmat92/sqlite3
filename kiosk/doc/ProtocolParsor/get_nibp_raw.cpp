#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>

#define DEVICE1 "/dev/ttyACM0"
#define DEVICE2 "/dev/ttyACM1"

int open_uart(const char *dev)
{
    int fd = open(dev, O_RDWR | O_NOCTTY | O_SYNC);
    if(fd < 0)
        return -1;

    struct termios tty;
    memset(&tty,0,sizeof(tty));

    if(tcgetattr(fd,&tty) != 0)
    {
        close(fd);
        return -1;
    }

    cfsetospeed(&tty,B115200);
    cfsetispeed(&tty,B115200);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_iflag &= ~IGNBRK;
    tty.c_lflag = 0;
    tty.c_oflag = 0;

    tty.c_cc[VMIN]  = 1;
    tty.c_cc[VTIME] = 1;

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~(PARENB | PARODD);
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    tcsetattr(fd,TCSANOW,&tty);

    return fd;
}

void dump_hex(unsigned char *buf,int len)
{
    for(int i=0;i<len;i++)
        printf("%02X ",buf[i]);

    printf("\n");
}

int main()
{
    int fd = open_uart(DEVICE1);

    if(fd < 0)
    {
        std::cout<<"Trying "<<DEVICE2<<std::endl;
        fd = open_uart(DEVICE2);
    }

    if(fd < 0)
    {
        std::cout<<"UART open failed\n";
        return -1;
    }

    std::cout<<"UART opened\n";

    /*
      Command based on firmware ESC parser
      96 AA F5 -> NIBP state
    */

    unsigned char start_cmd[] = {0x96,0xAA,0xF5};

    write(fd,start_cmd,sizeof(start_cmd));

    std::cout<<"NIBP Start Command Sent\n";

    unsigned char buf[256];

    while(1)
    {
        int n = read(fd,buf,sizeof(buf));

        if(n > 0)
        {
            std::cout<<"RX "<<n<<" bytes: ";
            dump_hex(buf,n);
        }
    }

    close(fd);
}
