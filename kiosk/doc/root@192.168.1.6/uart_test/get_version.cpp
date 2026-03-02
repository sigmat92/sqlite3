#include <iostream>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <cstring>
#include <ctime>

// ---------------- UART ----------------

int open_uart(const char* dev)
{
    int fd = open(dev, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    termios tty{};
    tcgetattr(fd, &tty);

    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);

    tty.c_cflag = CS8 | CREAD | CLOCAL;
    tty.c_lflag = tty.c_iflag = tty.c_oflag = 0;
    tty.c_cc[VMIN]  = 0;
    tty.c_cc[VTIME] = 10;   // 1s timeout

    tcsetattr(fd, TCSANOW, &tty);
    return fd;
}

void send_cmd(int fd, std::initializer_list<uint8_t> cmd)
{
    write(fd, cmd.begin(), cmd.size());
    tcdrain(fd);
}

// ---------------- FRAME READER ----------------
// Equivalent to Python read_frame()

bool read_frame(int fd, uint8_t &ctrl, std::vector<uint8_t> &payload)
{
    uint8_t nob;

    if (read(fd, &ctrl, 1) != 1)
        return false;

    if (read(fd, &nob, 1) != 1)
        return false;

    payload.resize(nob);
    int r = read(fd, payload.data(), nob);

    return (r == nob);
}

// ---------------- MAIN ----------------

int main()
{
    int fd = open_uart("/dev/ttyACM0");
    if (fd < 0)
        return 1;

    std::cout << "UART opened\n";

    // -------- SEND COMMANDS --------

    send_cmd(fd, {0x96, 0xAA, 0xFB, 0x49, 0x73}); // IDLE
    usleep(100000);

    send_cmd(fd, {0x96, 0xAA, 0xFB, 0x56});       // VERSION REQUEST

    // -------- READ VERSION --------

    int dfu_major = -1;
    int dfu_minor = -1;

    time_t start = time(nullptr);

    while (time(nullptr) - start < 5) {
        uint8_t ctrl;
        std::vector<uint8_t> payload;

        if (!read_frame(fd, ctrl, payload))
            continue;

        if (payload.size() < 2)
            continue;

        uint8_t status = payload[0];
        uint8_t value  = payload[1];

        std::cout << "RX: ctrl=0x"
                  << std::hex << int(ctrl)
                  << " status=" << std::dec << int(status)
                  << " value=" << int(value) << "\n";

        if (ctrl != 0xFB)
            continue;

        // DFU MAJOR
        if (status == 0 && dfu_major < 0) {
            dfu_major = value;
            std::cout << "DFU MAJOR: " << dfu_major << "\n";
            continue;
        }

        // DFU MINOR (special case)
        if (status == 31 && dfu_minor < 0) {
            dfu_minor = value;
            std::cout << "DFU MINOR: " << dfu_minor << "\n";
            break;
        }
    }

    if (dfu_major >= 0 && dfu_minor >= 0) {
        std::cout << "\nDFU VERSION: "
                  << dfu_major << "." << dfu_minor << "\n";
    } else {
        std::cout << "\nFailed to read DFU version\n";
    }

    close(fd);
    return 0;
}

