import serial
import time

ser = serial.Serial(
    port="/dev/ttyACM0",
    baudrate=9600,
    timeout=1
)

def read_frame():
    ctrl = ser.read(1)
    if not ctrl:
        return None

    ctrl = ctrl[0]

    nob = ser.read(1)
    if not nob:
        return None

    nob = nob[0]
    payload = ser.read(nob)

    if len(payload) != nob:
        return None

    return ctrl, payload


# -------- SEND COMMANDS --------

ser.write(bytes([0x96, 0xAA, 0xFB, 0x49, 0x73]))  # idle
time.sleep(0.1)
ser.write(bytes([0x96, 0xAA, 0xFB, 0x56]))        # version request

# -------- READ VERSION --------

dfu_major = None
dfu_minor = None

start_time = time.time()

while time.time() - start_time < 5:
    frame = read_frame()
    if not frame:
        continue

    ctrl, payload = frame
    status = payload[0]
    value  = payload[1] if len(payload) > 1 else None

    print(f"RX: ctrl=0x{ctrl:02X}, status={status}, value={value}")

    if ctrl != 0xFB:
        continue

    # DFU MAJOR
    if status == 0 and dfu_major is None:
        dfu_major = value
        print("DFU MAJOR:", dfu_major)
        continue

    # DFU MINOR (special case on this firmware)
    if status == 31 and dfu_minor is None:
        dfu_minor = value
        print( "DFU MINOR:", dfu_minor)
        break

if dfu_major is not None and dfu_minor is not None:
    print(f"\n DFU VERSION: {dfu_major}.{dfu_minor}")
else:
    print("\n Failed to read DFU version")

ser.close()

