#include <iostream>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
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
    tty.c_cc[VTIME] = 5;   // 0.5s timeout

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
    std::cout << "Starting temperature read...\n";

    int fd = open_uart("/dev/ttyACM0");
    if (fd < 0)
        return 1;

    // -------- CLEAN START --------
    tcflush(fd, TCIFLUSH);

    // -------- ENTER IDLE --------
    send_cmd(fd, {0x96, 0xAA, 0xFB, 0x49, 0x73});
    usleep(200000);

    // -------- REQUEST TEMP --------
    send_cmd(fd, {0x96, 0xAA, 0x54});

    time_t start = time(nullptr);

    while (time(nullptr) - start < 3) {
        uint8_t ctrl;
        std::vector<uint8_t> payload;

        if (!read_frame(fd, ctrl, payload))
            continue;

        std::cout << "RX: ctrl=0x"
                  << std::hex << int(ctrl)
                  << " payload=";

        for (auto b : payload)
            std::cout << std::hex << int(b) << " ";
        std::cout << std::dec << "\n";

        // Temperature response
        if (ctrl == 0xFA && payload.size() == 3) {
            int temp_int  = payload[0];
            int temp_frac = payload[1];

            // Ignore warm-up frame
            if (temp_int == 0 && temp_frac == 0) {
                std::cout << "Ignoring zero temperature frame\n";
                continue;
            }

            float temperature_f =
                temp_int + temp_frac / 10.0f;

            std::cout << "\nTemperature = "
                      << temperature_f << " °F\n";
            break;
        }
    }

    std::cout << "Done\n";

    // -------- BACK TO IDLE --------
    send_cmd(fd, {0x96, 0xAA, 0xFB, 0x49, 0x73});

    close(fd);
    return 0;
}

