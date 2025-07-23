#!/bin/bash

CHIP=gpiochip0
#OUTA=27
#OUTB=18
OUTA=18
OUTB=27
SW=17

last_A=0
position=0

function get_val() {
  local pin=$1
  gpioget --chip $CHIP $pin | awk -F= '{print ($2=="inactive") ? 1 : 0}'
}

echo "[INFO] Rotary Encoder with Button started (Ctrl+C to stop)"

while true; do
  A=$(get_val $OUTA)
  B=$(get_val $OUTB)
  SW_VAL=$(get_val $SW)

  if [[ $A -ne $last_A ]]; then
    if [[ $A -eq 1 ]]; then
      # On rising edge of A, check B
      if [[ $B -eq 0 ]]; then
        ((position++))
        echo "$(date +%T) - CW žœ Position: $position"
      else
        ((position--))
        echo "$(date +%T) - CCW œ Position: $position"
      fi
    fi
  fi

  last_A=$A

  if [[ $SW_VAL -eq 1 ]]; then
    echo "$(date +%T) - Button Pressed at Position: $position"
    sleep 0.2
    while [[ $(get_val $SW) -eq 1 ]]; do sleep 0.05; done
  fi

  sleep 0.005
done

