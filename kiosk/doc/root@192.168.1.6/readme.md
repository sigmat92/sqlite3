single, self-contained C++ (Linux) test program that:

Talks to /dev/ttyACM0

Sends exact commands you specified

Parses each parameter independently

Can be compiled & run without Qt

Mirrors the behavior validated in Python

This is ideal for:

bring-up testing

protocol validation

later porting into Qt / MVC

What this test program covers

Idle mode
SPO2
NIBP (start / stop + read)
Height
Weight
Temperature
Robust RX frame parsing

Protocol assumptions (based on thhe board)

RX frame format (validated from your logs):

[CTRL][LEN][PAYLOAD...]


Examples:

FA 03 61 06 46   -> Temperature = 97.6 °F
F8 03 03 00 01   -> Weight
F7 01 AC         -> Height
F4 01 62         -> SPO2
F5 06 00 00 76 4E 5A -> NIBP

Build & Run
g++ -std=c++17 uart_test.cpp -o uart_test
sudo ./uart_test

Full Testable C++ Code (uart_test.cpp)

//uart_test.cpp

#include <iostream>
#include <vector>
#include <deque>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <cstring>

// ---------------- UART ----------------

int openUart(const char* dev, int baud)
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

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
    tty.c_cflag |= CREAD | CLOCAL;
    tty.c_cflag &= ~(PARENB | PARODD);
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    tty.c_lflag = 0;
    tty.c_iflag = 0;
    tty.c_oflag = 0;

    tty.c_cc[VMIN]  = 0;
    tty.c_cc[VTIME] = 2;

    tcsetattr(fd, TCSANOW, &tty);
    return fd;
}

void sendCmd(int fd, std::initializer_list<uint8_t> cmd)
{
    write(fd, cmd.begin(), cmd.size());
    tcdrain(fd);
}

// ---------------- RX PARSER ----------------

enum { WAIT_CTRL, WAIT_LEN, WAIT_PAYLOAD };
int state = WAIT_CTRL;
uint8_t ctrl = 0, len = 0;
std::vector<uint8_t> payload;
std::deque<uint8_t> rxbuf;

void parseFrame(uint8_t ctrl, const std::vector<uint8_t>& d)
{
    switch (ctrl) {

    case 0xF4: // SPO2
        if (d.size() == 1 && d[0] <= 100)
            std::cout << "SPO2: " << int(d[0]) << " %\n";
        break;

    case 0xFA: // Temperature
        if (d.size() == 3) {
            int ti = d[0], tf = d[1];
            if (ti == 0 && tf == 0) break; // ignore warm-up
            float temp = ti + tf / 10.0f;
            std::cout << "🌡 Temperature: " << temp << " °F\n";
        }
        break;

    case 0xF8: // Weight
        if (d.size() == 3) {
            float w = d[0] + d[1] / 10.0f;
            if (w >= 5.0)
                std::cout << "eight: " << w << "\n";
        }
        break;

    case 0xF7: // Height
        if (d.size() == 1)
            std::cout << "Height: " << int(d[0]) << "\n";
        break;

    case 0xF5: // NIBP
        if (d.size() >= 4) {
            int sys = (d[1] << 8) | d[2];
            int dia = d[3];
            int mean = (d.size() == 6) ? d[4] : -1;
            std::cout << "NIBP SYS=" << sys
                      << " DIA=" << dia;
            if (mean >= 0) std::cout << " MEAN=" << mean;
            std::cout << "\n";
        }
        break;

    default:
        // ignore 0xFB status frames
        break;
    }
}

void processRx()
{
    while (!rxbuf.empty()) {
        uint8_t b = rxbuf.front();
        rxbuf.pop_front();

        if (state == WAIT_CTRL) {
            ctrl = b;
            state = WAIT_LEN;
        }
        else if (state == WAIT_LEN) {
            len = b;
            payload.clear();
            if (len == 0 || len > 8)
                state = WAIT_CTRL;
            else
                state = WAIT_PAYLOAD;
        }
        else if (state == WAIT_PAYLOAD) {
            payload.push_back(b);
            if (payload.size() == len) {
                parseFrame(ctrl, payload);
                state = WAIT_CTRL;
            }
        }
    }
}

// ---------------- MAIN ----------------

int main()
{
    int fd = openUart("/dev/ttyACM0", 9600);
    if (fd < 0) return 1;

    std::cout << "UART connected\n";

    // Idle mode
    sendCmd(fd, {0x96,0xAA,0xFB,0x49,0x73});
    usleep(200000);

    // Start NIBP
    sendCmd(fd, {0x96,0xAA,0xF5,0x01,0x01});

    while (true) {
        uint8_t buf[64];
        int n = read(fd, buf, sizeof(buf));
        for (int i = 0; i < n; ++i)
            rxbuf.push_back(buf[i]);

        processRx();

        static int tick = 0;
        if (++tick % 20 == 0) {
            sendCmd(fd, {0x96,0xAA,0xF4}); // SPO2
            sendCmd(fd, {0x96,0xAA,0x54}); // Temp
            sendCmd(fd, {0x96,0xAA,0xF8}); // Weight
            sendCmd(fd, {0x96,0xAA,0xF7}); // Height
        }

        usleep(100000);
    }

    close(fd);
    return 0;
}

modular:

protocolParser/
├── uart/
│   ├── Uart.cpp
│   └── Uart.h
├── parser/
│   ├── FrameParser.cpp
│   └── FrameParser.h
├── params/
│   ├── SpO2.cpp
│   ├── SpO2.h
│   ├── Temperature.cpp
│   ├── Temperature.h
│   ├── Weight.cpp
│   ├── Weight.h
│   ├── Height.cpp
│   ├── Height.h
│   ├── NIBP.cpp
│   └── NIBP.h
└── main.cpp

