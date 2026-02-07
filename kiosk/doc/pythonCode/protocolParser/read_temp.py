import serial
import time

START_END = 0xFB
TEMP_PARAM = 0xFA

def open_serial():
    for port in ('/dev/ttyACM1', '/dev/ttyACM0'):
        try:
            ser = serial.Serial(
                port=port,
                baudrate=9600,
                bytesize=serial.EIGHTBITS,
                parity=serial.PARITY_NONE,
                stopbits=serial.STOPBITS_ONE,
                timeout=0.2,
                write_timeout=1
            )
            print(f"Opened {port}")
            return ser
        except serial.SerialException:
            pass
    raise RuntimeError("Unable to open serial port")

ser = open_serial()
rx_buffer = bytearray()

# ---- Send temperature request ----
tx = bytes([0x96, 0xAA, 0x54])
print("[TX HEX]", tx.hex(' '))
ser.write(tx)
ser.flush()

# ---- Read & parse stream ----
end_time = time.time() + 1.0

while time.time() < end_time:
    rx_buffer += ser.read(64)

    while True:
        # Look for frame start
        if START_END not in rx_buffer:
            break

        start = rx_buffer.index(START_END)

        # Look for frame end
        try:
            end = rx_buffer.index(START_END, start + 1)
        except ValueError:
            break

        frame = rx_buffer[start:end + 1]
        del rx_buffer[:end + 1]

        print("[FRAME HEX]", frame.hex(' '))

        # ---- Decode temperature frame ----
        if len(frame) >= 10 and frame[4] == TEMP_PARAM:
            temp_int = frame[6]
            temp_frac = frame[7]
            unit = chr(frame[8])

            temperature = temp_int + (temp_frac / 10.0)

            if unit == 'F':
                print(f"Temperature: {temperature:.1f} °F")
            elif unit == 'C':
                print(f"Temperature: {temperature:.1f} °C")
            else:
                print(f"Temperature: {temperature:.1f} (Unknown unit {frame[8]:02X})")

ser.close()

