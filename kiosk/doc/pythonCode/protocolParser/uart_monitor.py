import serial
import time

PORT = "/dev/ttyACM0"   # change if needed
BAUD = 9600

ser = serial.Serial(
    port=PORT,
    baudrate=BAUD,
    bytesize=serial.EIGHTBITS,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    timeout=1
)

print("Opened", PORT)

# ---------------- RX STATE MACHINE ----------------

WAIT_CTRL = 0
WAIT_LEN  = 1
WAIT_DATA = 2

state = WAIT_CTRL
ctrl = 0
length = 0
payload = bytearray()

def parse_frame(ctrl, data):
    print(f"RAW: {bytes([ctrl, len(data)]) .hex()} {data.hex()}")

    if ctrl == 0xF2:  # Pulse rate
        bpm = data[0]
        if 30 <= bpm <= 239:
            print("PULSE RATE:", bpm, "bpm")
        else:
            print("PULSE ERROR")

    elif ctrl == 0xF4:  # SPO2
        spo2 = data[0]
        if spo2 <= 100:
            print("SPO2:", spo2, "%")
        else:
            print("SPO2 ERROR")

    elif ctrl == 0xFA:  # Temperature
        dec = data[0]
        frac = data[1]
        unit = data[2]
        temp = dec + frac / 10.0
        print("TEMPERATURE:", temp, "°F")

    elif ctrl == 0xF8:  # Weight
        dec = data[0]
        frac = data[1]
        unit = data[2]
        weight = dec + frac / 10.0
        print("WEIGHT:", weight)

    elif ctrl == 0xF7:  # Height
        print("HEIGHT:", data[0])

    elif ctrl == 0xF5:  # NIBP
        status = data[0]
        sys = (data[1] << 8) | data[2]
        dia = data[3]
        mean = data[4] if len(data) == 6 else None
        print("NIBP:",
              "SYS:", sys,
              "DIA:", dia,
              "MEAN:", mean)

    elif ctrl == 0xFB:  # DFU
        status = data[0]
        if status == 0:
            major = data[1]
            minor = data[2]
            print("DFU VERSION:", major, ".", minor)
        else:
            print("DFU ERROR")

    else:
        print("UNKNOWN CTRL:", hex(ctrl))


print("Listening...\n")

# ---------------- MAIN LOOP ----------------

while True:
    byte = ser.read(1)
    if not byte:
        continue

    b = byte[0]

    if state == WAIT_CTRL:
        ctrl = b
        state = WAIT_LEN

    elif state == WAIT_LEN:
        length = b
        if length == 0 or length > 10:
            state = WAIT_CTRL
            continue
        payload.clear()
        state = WAIT_DATA

    elif state == WAIT_DATA:
        payload.append(b)
        if len(payload) == length:
            parse_frame(ctrl, payload)
            print("-" * 40)
            state = WAIT_CTRL

