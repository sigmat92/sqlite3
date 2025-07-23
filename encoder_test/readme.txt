root@imx93frdm:/home/prakash/encoder_test# ./encoder_debug.sh 
[INFO] Starting encoder debug monitor (Ctrl+C to stop)
 watch Time OUTA  OUTB  SW status
15:59:51     "27"=inactive     "18"=inactive     "17"=active
15:59:52     "27"=inactive     "18"=inactive     "17"=active
15:59:53     "27"=inactive     "18"=inactive     "17"=active
15:59:54     "27"=inactive     "18"=active     "17"=active
15:59:55     "27"=inactive     "18"=active     "17"=active
15:59:56     "27"=inactive     "18"=inactive     "17"=active
15:59:57     "27"=inactive     "18"=active     "17"=active
15:59:58     "27"=inactive     "18"=active     "17"=active
15:59:59     "27"=inactive     "18"=inactive     "17"=active
16:00:00     "27"=inactive     "18"=inactive     "17"=active
^C


root@imx93frdm:/home/prakash/encoder_test# gpioget --chip gpiochip0 27 && gpioget --chip gpiochip0 18
"27"=inactive
"18"=active
root@imx93frdm:/home/prakash/encoder_test# ./encoder_poll.sh 
[INFO] Rotary Encoder with Button started (Ctrl+C to stop)
15:56:15 - CW Position: 1
15:56:21 - Button Pressed at Position: 1
^C

root@imx93frdm:/home/prakash/encoder_test# gpioget --chip gpiochip0 27 && gpioget --chip gpiochip0 18
"27"=inactive
"18"=inactive
root@imx93frdm:/home/prakash/encoder_test# ./encoder_poll.sh 
[INFO] Rotary Encoder with Button started (Ctrl+C to stop)
15:58:34 - CCW Position: -1
15:58:38 - Button Pressed at Position: -1
^C




