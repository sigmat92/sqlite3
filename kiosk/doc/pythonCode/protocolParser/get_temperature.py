import serial
import time
import sys

PORT = "/dev/ttyACM0"
BAUD = 9600

print("Starting temperature read...", flush=True)

ser = serial.Serial(PORT, BAUD, timeout=0.5)

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


# -------- CLEAN START --------
ser.reset_input_buffer()

# -------- ENTER IDLE --------
ser.write(bytes([0x96, 0xAA, 0xFB, 0x49, 0x73]))
ser.flush()
time.sleep(0.2)

# -------- REQUEST TEMP --------
ser.write(bytes([0x96, 0xAA, 0x54]))
ser.flush()

start = time.time()

while time.time() - start < 3:
    frame = read_frame()
    if not frame:
        continue

    ctrl, payload = frame
    print(f"RX: ctrl=0x{ctrl:02X}, payload={payload.hex()}", flush=True)

    # Temperature response
    if ctrl == 0xFA and len(payload) == 3:
        temp_int, temp_frac, unit = payload

        # Ignore invalid / warm-up frames
        if temp_int == 0 and temp_frac == 0:
            print("Ignoring zero temperature frame", flush=True)
            continue

        temperature_f = temp_int + temp_frac / 10.0

        print(f"\n Temperature = {temperature_f:.1f} °F", flush=True)
        break

print("Done")

# -------- BACK TO IDLE --------
ser.write(bytes([0x96, 0xAA, 0xFB, 0x49, 0x73]))
ser.flush()

ser.close()

