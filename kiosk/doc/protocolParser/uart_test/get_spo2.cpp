#include <iostream>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <ctime>

int open_uart(const char* dev)
{
    int fd = open(dev, O_RDWR | O_NOCTTY | O_SYNC);
    termios tty{};
    tcgetattr(fd, &tty);
    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);
    tty.c_cflag = CS8 | CREAD | CLOCAL;
    tty.c_lflag = tty.c_iflag = tty.c_oflag = 0;
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 5;
    tcsetattr(fd, TCSANOW, &tty);
    return fd;
}

bool read_frame(int fd, uint8_t &ctrl, std::vector<uint8_t> &payload)
{
    uint8_t nob;
    if (read(fd, &ctrl, 1) != 1) return false;
    if (read(fd, &nob, 1) != 1) return false;
    payload.resize(nob);
    return read(fd, payload.data(), nob) == nob;
}

int main()
{
    int fd = open_uart("/dev/ttyACM0");

    // Idle
    write(fd, "\x96\xAA\xFB\x49\x73", 5);
    usleep(200000);

    // Request SPO2
    write(fd, "\x96\xAA\xF4", 3);

    time_t start = time(nullptr);
    while (time(nullptr) - start < 3) {
        uint8_t ctrl;
        std::vector<uint8_t> p;
        if (!read_frame(fd, ctrl, p)) continue;

        if (ctrl == 0xF4 && p.size() == 1 && p[0] <= 100) {
            std::cout << "SPO2 = " << int(p[0]) << " %\n";
            break;
        }
    }

    close(fd);
}

