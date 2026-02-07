g++ -std=c++17 vitals_fsm_autodetect.cpp -o vitals_fsm
./vitals_fsm

add #include <cstdint> on imx93frdm

Communication Protocol

Parameters
Control Bytes

No. of  bytes(NOB)
Data Parsing Method

0XF4
1
You’ve to send request [96,aa,f4] on serial port

NIBP start
0XF5
1
To start NIBP, send request [0x96, 0xaa, 0xF5,0x01,0x01]  on serial port
NIBP stop
0xf5
1
To stop NIBP, command is [0x96, 0xaa, 0xF5,0x01,0x00]
HEIGHT
0XF7
1
You’ve to send request [0x96, 0xaa, 0xF7] on serial port

WEIGHT
0XF8
3
You’ve to send request [0x96, 0xaa, 0xF8] on serial port

TEMPERATURE
0XFA
3
You’ve to send request [0x96, 0xaa, 0x54] on serial port


Idle Mode
---
---
For idle mode command is  [0x96, 0xaa, 0xfb, 0x49, 0x73]

Printer Mode
0XF6
---
For printer mode commands are
list1 = [0x96, 0xaa, 0xf6, print_len_lsb, print_len_msb]
list2 = list (“printer slip”)
list3 = [0xff, 0xaa, 0x0a, 0x1b, 0x0d, 0x1b, 0x76]
list4 = [0x96, 0xaa, 0xfb, 0x49]

where, 
           print_len          =  len(“printer slip”)+ 7
           print_len_lsb   =  int(print_len % 256), 
           print_len_msb = int(print_len / 256)




Parameters
Control Byte
No. of bytes(NOB)
Data Parsing Method
PULSERATE
0XF2
1
check for 0xf2 control byte followed by NOB and then data byte pulserate in bpm.

Range is from 30 – 239. Value less than 30 would be treated as error
Byte 1 is heart rate derived from SPO.

SPO2
0XF4
1
check for 0xf4 control byte followed by NOB and then data byte

Rang 0 – 100  (Any value greater than 100 would indicate error)
NIBP
0XF5
4/6
check for 0xf5 control byte followed by NOB and then data byte.

<status>,<systolic  msb>,<systolic lsb>,<diastolic value>, <mean pressure>, <Error Code>.
If NOB == 4 , then <status>,<systolic  msb>,<systolic lsb>,<diastolic value>
Else all 6
HEIGHT
0XF7
1
check for 0xf7 control byte followed by NOB and then data byte
WEIGHT
0XF8
3
check for 0xf8 control byte followed by NOB and then data byte
<weight_decimal> , <weight_floating_part>,<weight_unit>

TEMPERATURE
0XFA
3
check for 0xFA control byte followed by NOB and then data byte
<temperature_decimal><temperature_floating_part>
<unit>
DFU MAJOR
0xFB
1
If   status_code = 0, then next byte is  DFU MAJOR
DFU MINOR
0xFB
1
If  status_code = 0, then next byte is  DFU MINOR
