#!/bin/bash

# Set your GPIO chip and pin numbers
CHIP="gpiochip0"
PIN_OUTA=27
PIN_OUTB=18
PIN_SW=17

echo "[INFO] Starting encoder debug monitor (Ctrl+C to stop)"
echo "Watch Time OUTA  OUTB  SW status"

while true; do
    TIME=$(date +"%H:%M:%S")
    A=$(gpioget --chip "$CHIP" "$PIN_OUTA" 2>/dev/null)
    B=$(gpioget --chip "$CHIP" "$PIN_OUTB" 2>/dev/null)
    SW=$(gpioget --chip "$CHIP" "$PIN_SW" 2>/dev/null)
    printf "%s     %s     %s     %s\n" "$TIME" "$A" "$B" "$SW"
    sleep 1 
done

