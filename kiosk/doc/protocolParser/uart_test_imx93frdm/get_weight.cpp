#include <iostream>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <cstdint> 

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

    // Request weight
    write(fd, "\x96\xAA\xF8", 3);

    uint8_t ctrl, nob;
    read(fd, &ctrl, 1);
    read(fd, &nob, 1);

    if (ctrl == 0xF8 && nob == 3) {
        uint8_t p[3];
        read(fd, p, 3);
        float weight = p[0] + p[1] / 10.0f;
        std::cout << "Weight = " << weight << "\n";
    }

    close(fd);
}

