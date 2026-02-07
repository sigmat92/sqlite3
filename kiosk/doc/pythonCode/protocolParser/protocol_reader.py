import serial
import time
from collections import deque

PORT = "/dev/ttyACM0"   # change if needed
BAUD = 9600

# ---------------- UART ----------------

ser = serial.Serial(
    port=PORT,
    baudrate=BAUD,
    bytesize=serial.EIGHTBITS,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    timeout=0.1
)

print("Connected to", PORT)

# ---------------- TX COMMANDS ----------------

def send(cmd):
    ser.write(bytes(cmd))
    ser.flush()

def request_spo2():
    send([0x96, 0xAA, 0xF4])

def request_temperature():
    send([0x96, 0xAA, 0x54])

def request_weight():
    send([0x96, 0xAA, 0xF8])

def request_height():
    send([0x96, 0xAA, 0xF7])

def start_nibp():
    send([0x96, 0xAA, 0xF5, 0x01, 0x01])

def stop_nibp():
    send([0x96, 0xAA, 0xF5, 0x01, 0x00])

# ---------------- RX PARSER ----------------

buffer = deque()
STATE_CTRL, STATE_LEN, STATE_PAYLOAD = 0, 1, 2
state = STATE_CTRL
ctrl = 0
length = 0
payload = []

def parse_frame(ctrl, data):
    if ctrl == 0xF2:  # Pulse rate
        bpm = data[0]
        if 30 <= bpm <= 239:
            print(f"Pulse Rate: {bpm} bpm")

    elif ctrl == 0xF4:  # SPO2
        spo2 = data[0]
        if spo2 <= 100:
            print(f"SPO2: {spo2} %")

    elif ctrl == 0xFA:  # Temperature
        temp = data[0] + data[1] / 10.0
        unit = data[2]
        print(f"Temperature: {temp:.1f} °F")

    elif ctrl == 0xF8:  # Weight
        weight = data[0] + data[1] / 10.0
        print(f"Weight: {weight:.1f}")

    elif ctrl == 0xF7:  # Height
        print(f"Height: {data[0]}")

    elif ctrl == 0xF5:  # NIBP
        status = data[0]
        sys = (data[1] << 8) | data[2]
        dia = data[3]
        mean = data[4] if len(data) == 6 else None
        print(f"NIBP: SYS={sys} DIA={dia} MEAN={mean}")

    elif ctrl == 0xFB:  # DFU version
        if data[0] == 0:
            print(f"DFU Version: {data[1]}.{data[2]}")

    else:
        print("Unknown CTRL:", hex(ctrl), data)

def process_rx():
    global state, ctrl, length, payload

    while buffer:
        byte = buffer.popleft()

        if state == STATE_CTRL:
            ctrl = byte
            state = STATE_LEN

        elif state == STATE_LEN:
            length = byte
            payload = []
            if length == 0 or length > 10:
                state = STATE_CTRL
            else:
                state = STATE_PAYLOAD

        elif state == STATE_PAYLOAD:
            payload.append(byte)
            if len(payload) == length:
                parse_frame(ctrl, payload)
                state = STATE_CTRL

# ---------------- MAIN LOOP ----------------

try:
    start_nibp()
    last_poll = 0

    while True:
        # Read UART
        data = ser.read(64)
        for b in data:
            buffer.append(b)

        process_rx()

        # Poll sensors every 1 sec
        if time.time() - last_poll > 1.0:
            request_spo2()
            request_temperature()
            request_weight()
            request_height()
            last_poll = time.time()

except KeyboardInterrupt:
    print("\nStopping...")
    stop_nibp()
    ser.close()

