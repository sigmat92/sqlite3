/*
Protocol used from spec:

Start NIBP  : [0x96, 0xAA, 0xF5, 0x01, 0x01]
Stop NIBP   : [0x96, 0xAA, 0xF5, 0x01, 0x00]

Response:
0xF5 <NOB> <DATA>

DATA FORMAT

If NOB = 4
status, sys_msb, sys_lsb, dia

If NOB = 6
status, sys_msb, sys_lsb, dia, map, error
get_nibp.cpp
*/
#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>

#define DEV1 "/dev/ttyACM0"
#define DEV2 "/dev/ttyACM1"

#define CTRL_NIBP 0xF5

//---------------------------------------------------
// UART OPEN
//---------------------------------------------------

int open_uart(const char *dev)
{
    int fd = open(dev, O_RDWR | O_NOCTTY | O_SYNC);

    if(fd < 0)
        return -1;

    struct termios tty;
    memset(&tty,0,sizeof(tty));

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

//---------------------------------------------------
// SEND COMMAND
//---------------------------------------------------

void send_nibp_start(int fd)
{
    unsigned char cmd[] = {0x96,0xAA,0xF5,0x01,0x01};
    write(fd,cmd,sizeof(cmd));
}

void send_nibp_stop(int fd)
{
    unsigned char cmd[] = {0x96,0xAA,0xF5,0x01,0x00};
    write(fd,cmd,sizeof(cmd));
}

//---------------------------------------------------
// NIBP PARSER
//---------------------------------------------------

void parse_frame(unsigned char *buf,int len)
{
    if(len < 2)
        return;

    if(buf[0] != CTRL_NIBP)
        return;

    int nob = buf[1];

    if(nob == 4 && len >= 6)
    {
        int status = buf[2];
        int sys = (buf[3] << 8) | buf[4];
        int dia = buf[5];

        std::cout<<"\nNIBP RESULT\n";
        std::cout<<"Status : "<<status<<"\n";
        std::cout<<"SYS    : "<<sys<<" mmHg\n";
        std::cout<<"DIA    : "<<dia<<" mmHg\n";
    }

    else if(nob == 6 && len >= 8)
    {
        int status = buf[2];
        int sys = (buf[3] << 8) | buf[4];
        int dia = buf[5];
        int map = buf[6];
        int err = buf[7];

        std::cout<<"\nNIBP RESULT\n";
        std::cout<<"Status : "<<status<<"\n";
        std::cout<<"SYS    : "<<sys<<" mmHg\n";
        std::cout<<"DIA    : "<<dia<<" mmHg\n";
        std::cout<<"MAP    : "<<map<<" mmHg\n";
        std::cout<<"Error  : "<<err<<"\n";
    }
}

//---------------------------------------------------
// MAIN
//---------------------------------------------------

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

    send_nibp_start(fd);

    std::cout<<"NIBP START command sent\n";

    unsigned char buf[256];

    while(true)
    {
        int n = read(fd,buf,sizeof(buf));

        if(n > 0)
        {
            parse_frame(buf,n);
        }
    }

    close(fd);
}
/*
Compile
g++ get_nibp.cpp -o nibp_test
Run
sudo ./nibp_test
*/
