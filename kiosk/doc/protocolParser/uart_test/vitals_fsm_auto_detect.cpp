#include <iostream>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <ctime>

// ================= UART =================

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
    tty.c_cc[VTIME] = 5;   // 0.5s

    tcsetattr(fd, TCSANOW, &tty);
    return fd;
}

void send_cmd(int fd, std::initializer_list<uint8_t> cmd)
{
    write(fd, cmd.begin(), cmd.size());
    tcdrain(fd);
}

bool read_frame(int fd, uint8_t &ctrl, std::vector<uint8_t> &payload)
{
    uint8_t nob;
    if (read(fd, &ctrl, 1) != 1) return false;
    if (read(fd, &nob, 1) != 1) return false;

    payload.resize(nob);
    return read(fd, payload.data(), nob) == nob;
}

// ================= FSM =================

enum class State {
    IDLE,
    SPO2,
    TEMP,
    WEIGHT,
    HEIGHT,
    NIBP_START,
    NIBP_WAIT,
    DONE
};

constexpr int MAX_ATTEMPTS = 3;

int main()
{
    int fd = open_uart("/dev/ttyACM0");
    if (fd < 0) return 1;

    State state = State::IDLE;
    time_t state_ts = time(nullptr);
    int attempts = 0;

    bool hasSpo2   = false;
    bool hasTemp   = false;
    bool hasWeight = false;
    bool hasHeight = false;
    bool hasNibp   = false;

    std::cout << "Starting Vitals FSM...\n";

    while (state != State::DONE) {

        uint8_t ctrl;
        std::vector<uint8_t> p;

        // ---------------- RX ----------------
        if (read_frame(fd, ctrl, p)) {

            switch (ctrl) {

            case 0xF4: // SPO2
                if (state == State::SPO2 &&
                    p.size() == 1 &&
                    p[0] >= 70 && p[0] <= 100) {

                    hasSpo2 = true;
                    std::cout << "SPO2 = " << int(p[0]) << " %\n";
                    state = State::TEMP;
                    attempts = 0;
                }
                break;

            case 0xFA: // TEMP
                if (state == State::TEMP &&
                    p.size() == 3 &&
                    !(p[0] == 0 && p[1] == 0)) {

                    float temp = p[0] + p[1] / 10.0f;
                    hasTemp = true;
                    std::cout << "Temp = " << temp << " F\n";
                    state = State::WEIGHT;
                    attempts = 0;
                }
                break;

            case 0xF8: // WEIGHT
                if (state == State::WEIGHT &&
                    p.size() == 3 &&
                    p[0] > 5) {   // ignore 0 / 3 noise

                    float w = p[0] + p[1] / 10.0f;
                    hasWeight = true;
                    std::cout << "Weight = " << w << "\n";
                    state = State::HEIGHT;
                    attempts = 0;
                }
                break;

            case 0xF7: // HEIGHT
                if (state == State::HEIGHT &&
                    p.size() == 1 &&
                    p[0] > 50) {

                    hasHeight = true;
                    std::cout << "Height = " << int(p[0]) << "\n";
                    state = State::NIBP_START;
                    attempts = 0;
                }
                break;

            case 0xF5: // NIBP
                if (state == State::NIBP_WAIT &&
                    p.size() >= 4) {

                    int sys  = (p[1] << 8) | p[2];
                    int dia  = p[3];
                    int mean = (p.size() >= 5) ? p[4] : 0;

                    hasNibp = true;
                    std::cout << "NIBP SYS=" << sys
                              << " DIA=" << dia
                              << " MEAN=" << mean << "\n";
                    state = State::DONE;
                }
                break;
            }
        }

        // ---------------- TX / STATE ACTION ----------------
        if (time(nullptr) - state_ts >= 1) {

            switch (state) {

            case State::IDLE:
                send_cmd(fd, {0x96, 0xAA, 0xFB, 0x49, 0x73});
                state = State::SPO2;
                attempts = 0;
                break;

            case State::SPO2:
                if (++attempts > MAX_ATTEMPTS) {
                    std::cout << "SPO2 sensor NOT detected\n";
                    state = State::TEMP;
                    attempts = 0;
                } else {
                    send_cmd(fd, {0x96, 0xAA, 0xF4});
                }
                break;

            case State::TEMP:
                if (++attempts > MAX_ATTEMPTS) {
                    std::cout << "Temperature sensor NOT detected\n";
                    state = State::WEIGHT;
                    attempts = 0;
                } else {
                    send_cmd(fd, {0x96, 0xAA, 0x54});
                }
                break;

            case State::WEIGHT:
                if (++attempts > MAX_ATTEMPTS) {
                    std::cout << "Weight sensor NOT detected\n";
                    state = State::HEIGHT;
                    attempts = 0;
                } else {
                    send_cmd(fd, {0x96, 0xAA, 0xF8});
                }
                break;

            case State::HEIGHT:
                if (++attempts > MAX_ATTEMPTS) {
                    std::cout << "Height sensor NOT detected\n";
                    state = State::NIBP_START;
                    attempts = 0;
                } else {
                    send_cmd(fd, {0x96, 0xAA, 0xF7});
                }
                break;

            case State::NIBP_START:
                send_cmd(fd, {0x96, 0xAA, 0xF5, 0x01, 0x01});
                state = State::NIBP_WAIT;
                attempts = 0;
                break;

            case State::NIBP_WAIT:
                if (++attempts > 15) {
                    std::cout << "NIBP sensor NOT detected\n";
                    state = State::DONE;
                }
                break;

            default:
                break;
            }

            state_ts = time(nullptr);
        }
    }

    // Cleanup
    send_cmd(fd, {0x96, 0xAA, 0xF5, 0x01, 0x00}); // stop NIBP
    send_cmd(fd, {0x96, 0xAA, 0xFB, 0x49, 0x73}); // idle

    std::cout << "\nALL VITALS DONE\n";
    close(fd);
    return 0;
}

