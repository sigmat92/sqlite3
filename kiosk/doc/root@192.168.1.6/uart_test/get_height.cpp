#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int main()
{
    int fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_SYNC);
    termios tty{};
    tcgetattr(fd, &tty);
    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);
    tty.c_cflag = CS8 | CREAD | CLOCAL;
    tty.c_lflag = tty.c_iflag = tty.c_oflag = 0;
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 5;
    tcsetattr(fd, TCSANOW, &tty);

    write(fd, "\x96\xAA\xF7", 3);

    uint8_t ctrl, nob, val;
    read(fd, &ctrl, 1);
    read(fd, &nob, 1);
    read(fd, &val, 1);

    if (ctrl == 0xF7 && nob == 1)
        std::cout << "Height = " << int(val) << "\n";

    close(fd);
}

