#include <iostream>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <ctime>
#include <cstdint> 

// ================= UART =================

int open_uart(const char* dev)
{
    int fd = open(dev, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) { perror("open"); return -1; }

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

int main()
{
    int fd = open_uart("/dev/ttyACM0");
    if (fd < 0) return 1;

    State state = State::IDLE;
    time_t state_ts = time(nullptr);

    int spo2 = -1;
    float temp = 0;
    float weight = 0;
    int height = 0;
    int sys = 0, dia = 0, mean = 0;

    std::cout << "Starting Vitals FSM...\n";

    while (state != State::DONE) {

        uint8_t ctrl;
        std::vector<uint8_t> p;

        // ---------- RX ----------
        if (read_frame(fd, ctrl, p)) {

            switch (ctrl) {

            case 0xF4: // SPO2
                if (p.size() == 1 && p[0] <= 100) {
                    spo2 = p[0];
                    std::cout << "SPO2 = " << spo2 << " %\n";
                    state = State::TEMP;
                }
                break;

            case 0xFA: // TEMP
                if (p.size() == 3 && !(p[0] == 0 && p[1] == 0)) {
                    temp = p[0] + p[1] / 10.0f;
                    std::cout << "Temp = " << temp << " F\n";
                    state = State::WEIGHT;
                }
                break;

            case 0xF8: // WEIGHT
                if (p.size() == 3) {
                    weight = p[0] + p[1] / 10.0f;
                    std::cout << "Weight = " << weight << "\n";
                    state = State::HEIGHT;
                }
                break;

            case 0xF7: // HEIGHT
                if (p.size() == 1) {
                    height = p[0];
                    std::cout << "Height = " << height << "\n";
                    state = State::NIBP_START;
                }
                break;

            case 0xF5: // NIBP
                if (p.size() >= 4) {
                    sys = (p[1] << 8) | p[2];
                    dia = p[3];
                    mean = (p.size() >= 5) ? p[4] : 0;
                    std::cout << "NIBP SYS=" << sys
                              << " DIA=" << dia
                              << " MEAN=" << mean << "\n";
                    state = State::DONE;
                }
                break;
            }
        }

        // ---------- TX / STATE ACTION ----------
        if (time(nullptr) - state_ts > 1) {

            switch (state) {

            case State::IDLE:
                send_cmd(fd, {0x96, 0xAA, 0xFB, 0x49, 0x73});
                state = State::SPO2;
                break;

            case State::SPO2:
                send_cmd(fd, {0x96, 0xAA, 0xF4});
                break;

            case State::TEMP:
                send_cmd(fd, {0x96, 0xAA, 0x54});
                break;

            case State::WEIGHT:
                send_cmd(fd, {0x96, 0xAA, 0xF8});
                break;

            case State::HEIGHT:
                send_cmd(fd, {0x96, 0xAA, 0xF7});
                break;

            case State::NIBP_START:
                send_cmd(fd, {0x96, 0xAA, 0xF5, 0x01, 0x01});
                state = State::NIBP_WAIT;
                break;

            case State::NIBP_WAIT:
                break;

            default:
                break;
            }

            state_ts = time(nullptr);
        }
    }

    // Stop NIBP + idle
    send_cmd(fd, {0x96, 0xAA, 0xF5, 0x01, 0x00});
    send_cmd(fd, {0x96, 0xAA, 0xFB, 0x49, 0x73});

    std::cout << "\nALL VITALS DONE\n";
    close(fd);
}

