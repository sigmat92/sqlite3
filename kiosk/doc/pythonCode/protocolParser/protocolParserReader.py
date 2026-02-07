import serial
import time
from collections import deque

PORT = "/dev/ttyACM0"
BAUD = 9600

ser = serial.Serial(PORT, BAUD, timeout=0.2)
print("Connected to", PORT)

# ---------------- TX ----------------

def send(cmd):
    ser.write(bytes(cmd))
    ser.flush()

def enter_idle():
    send([0x96, 0xAA, 0xFB, 0x49, 0x73])
    time.sleep(0.2)

def request_spo2():   send([0x96, 0xAA, 0xF4])
def request_temp():   send([0x96, 0xAA, 0x54])
def request_weight(): send([0x96, 0xAA, 0xF8])
def request_height(): send([0x96, 0xAA, 0xF7])
def start_nibp():     send([0x96, 0xAA, 0xF5, 0x01, 0x01])
def stop_nibp():      send([0x96, 0xAA, 0xF5, 0x01, 0x00])

# ---------------- RX PARSER ----------------

STATE_CTRL, STATE_LEN, STATE_PAYLOAD = 0, 1, 2
state = STATE_CTRL
ctrl = 0
length = 0
payload = []
buffer = deque()

def parse_frame(ctrl, data):
    # Ignore status/busy frames
    if ctrl == 0xFB:
        return

    # Pulse
    if ctrl == 0xF2 and len(data) == 1:
        bpm = data[0]
        if 30 <= bpm <= 239:
            print(f"Pulse: {bpm} bpm")

    # SPO2
    elif ctrl == 0xF4 and len(data) == 1:
        spo2 = data[0]
        if spo2 <= 100:
            print(f"SPO2: {spo2} %")

    # Temperature (ALWAYS Fahrenheit on your board)
    elif ctrl == 0xFA and len(data) == 3:
        ti, tf, _ = data
        if ti == 0 and tf == 0:
            return  # ignore warm-up frame
        temp = ti + tf / 10.0
        print(f"Temperature: {temp:.1f} °F")

    # Weight
    elif ctrl == 0xF8 and len(data) == 3:
        w = data[0] + data[1] / 10.0
        print(f"Weight: {w:.1f}")

    # Height
    elif ctrl == 0xF7 and len(data) == 1:
        print(f" Height: {data[0]}")

    # NIBP
    elif ctrl == 0xF5 and len(data) >= 4:
        sys = (data[1] << 8) | data[2]
        dia = data[3]
        mean = data[4] if len(data) == 6 else None
        print(f"NIBP: SYS={sys} DIA={dia} MEAN={mean}")

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
            if length == 0 or length > 8:
                state = STATE_CTRL
            else:
                state = STATE_PAYLOAD

        elif state == STATE_PAYLOAD:
            payload.append(byte)
            if len(payload) == length:
                parse_frame(ctrl, payload)
                state = STATE_CTRL

# ---------------- MAIN ----------------

try:
    ser.reset_input_buffer()
    enter_idle()
    start_nibp()

    last_poll = 0

    while True:
        data = ser.read(64)
        for b in data:
            buffer.append(b)

        process_rx()

        if time.time() - last_poll > 2:
            request_spo2()
            request_temp()
            request_weight()
            request_height()
            last_poll = time.time()

except KeyboardInterrupt:
    print("\nStopping...")
    stop_nibp()
    enter_idle()
    ser.close()

