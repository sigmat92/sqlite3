/**
 *
FRAME: 01 5A F4 01 62 
Pulse : 90 bpm
SpO2  : 98 %

FRAME: FB 02 05 01 FB 
Unknown frame

FRAME: 01 00 F4 01 00 
Pulse : 0 bpm
SpO2  : no finger detected
 *
 */
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>

#define SERIAL_PORT "/dev/ttyACM0"
#define BAUDRATE B9600
#define FRAME_LEN 5

uint8_t frame[FRAME_LEN];
int index_frame = 0;


/* UART setup */

int open_serial(const char *device)
{
    int fd = open(device, O_RDWR | O_NOCTTY);

    if(fd < 0)
    {
        perror("open");
        return -1;
    }

    struct termios tty;
    memset(&tty,0,sizeof tty);

    tcgetattr(fd,&tty);

    cfsetospeed(&tty,BAUDRATE);
    cfsetispeed(&tty,BAUDRATE);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_cflag |= (CLOCAL | CREAD);

    tty.c_cflag &= ~(PARENB | PARODD);
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    tty.c_iflag = 0;
    tty.c_oflag = 0;
    tty.c_lflag = 0;

    tty.c_cc[VMIN]  = 1;
    tty.c_cc[VTIME] = 1;

    tcsetattr(fd,TCSANOW,&tty);

    return fd;
}


/* print frame */

void print_frame(uint8_t *f)
{
    printf("FRAME: ");
    for(int i=0;i<FRAME_LEN;i++)
        printf("%02X ",f[i]);
    printf("\n");
}


/* decode frame */

void decode_frame(uint8_t *f)
{

    /* SPO2 + pulse */

    if(f[0]==0x01 && f[2]==0xF4)
    {

        int pulse = f[1];
        int spo2  = f[4];

        printf("Pulse : %d bpm\n",pulse);

        if(spo2 > 0)
            printf("SpO2  : %d %%\n",spo2);
        else
            printf("SpO2  : no finger detected\n");

        printf("\n");
        return;
    }

    printf("Unknown frame\n\n");
}


/* UART parser */

void parse_byte(uint8_t byte)
{

    /* waiting for header */

    if(index_frame == 0)
    {
        if(byte == 0xFB || byte == 0x01)
        {
            frame[index_frame++] = byte;
        }

        return;
    }

    /* collecting frame */

    frame[index_frame++] = byte;

    if(index_frame == FRAME_LEN)
    {
        print_frame(frame);
        decode_frame(frame);

        index_frame = 0;
    }

}


int main()
{

    int fd = open_serial(SERIAL_PORT);

    if(fd < 0)
        return -1;

    printf("Protocol Parser Started\n\n");

    uint8_t byte;

    while(1)
    {

        int n = read(fd,&byte,1);

        if(n > 0)
            parse_byte(byte);

    }

}
