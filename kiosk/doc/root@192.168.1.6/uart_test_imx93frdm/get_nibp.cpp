#include <iostream>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <cstdint> 
#include <ctime>

bool read_frame(int fd, uint8_t &ctrl, std::vector<uint8_t> &p)
{
    uint8_t nob;
    if (read(fd, &ctrl, 1) != 1) return false;
    if (read(fd, &nob, 1) != 1) return false;
    p.resize(nob);
    return read(fd, p.data(), nob) == nob;
}

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

    // Start NIBP
    write(fd, "\x96\xAA\xF5\x01\x01", 5);

    time_t start = time(nullptr);
    while (time(nullptr) - start < 30) {
        uint8_t ctrl;
        std::vector<uint8_t> p;
        if (!read_frame(fd, ctrl, p)) continue;

        if (ctrl == 0xF5 && p.size() >= 4) {
            int sys = (p[1] << 8) | p[2];
            int dia = p[3];
            int mean = (p.size() >= 5) ? p[4] : -1;

            std::cout << "NIBP SYS=" << sys
                      << " DIA=" << dia
                      << " MEAN=" << mean << "\n";

            break;
        }
    }

    // Stop NIBP
    write(fd, "\x96\xAA\xF5\x01\x00", 5);
    close(fd);
}

