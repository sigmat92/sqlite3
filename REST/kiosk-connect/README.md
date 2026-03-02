

network config json from uart:
{
"SSID":"MetslT1",
"Security_Key":"bac23dac23",
"Security_Type":"WPA/WPA2",
"URL":"https://tnhmis.uat.dcservices.in",
"Server IP":"192.168.45.78",
"Port No":9800
}
vitals json from uart:
{
        "mId": "0011",
        "pId": "4321",
        "entry_date": "01-03-2026:17:40",
	"hospital_code":"123456",
	"hmis_code":"12345689",
        "mobile_no": "9820856498",
        "name": "Prakash Dhrutaraj",
        "age": "56",
        "sex": "Male",
        "height": "175",
        "weight": "75",
        "bmi": "24.5",
        "bmr": "1500",
        "bsa": "1.9",
        "temp": "98.6",
        "systolic_bp": "120",
        "diastolic_bp": "80",
        "map": "93",
        "spo2": "98",
        "pr": "72",
	"gnum_isvalid":"yes",
	"seatId":"123"
      }
local sever:

LOGIN_URL "https://coddleonline.com/example/user/login"
POST_URL "https://coddleonline.com/HISIntegrationMachine/api/v1/vital-details"

cdac server:

LOGIN_URL "https://tnhmis.uat.dcservices.in/HISIntegrationMachine/authenticate/UserId/Password"
POST_URL "https://tnhmis.uat.dcservices.in/HISIntegrationMachine/api/v1/vital-details"

wifi credentials: 

WIFI_SSID "MetslT1"
WIFI_PASS "bac23dac23"

WIFI_SSID "Airtel_prak_6498"
WIFI_PASS "air63889"

On boot -> send ESP_[version] via UART0.

Wait for network JSON if WiFi not connected: send NO_WIFI every 5 s.

On receiving network JSON -> connect to WiFi -> send CONNECTING.

After connection: send WIFI_SUCCESS / WIFI_FAIL.

Continuously wait for vitals JSON on UART0.

On receiving vitals JSON -> parse -> post to server -> send DATA_SUCCESS / DATA_FAIL.

No NVS storage, no JWT caching - each POST request will log in to get JWT.

Periodically send WIFI_UP / WIFI_DN.

actual log:

RX: NO_WIFI

RX: NO_WIFI

TX: {
"SSID":"Airtel_prak_6498",
"Security Key":"air63889",
"Security Type":"WPA/WPA2",
"URL":"https://tnhmis.uat.dcservices.in",
"Server IP":"192.168.45.78",
"Port No":9800
}

RX: I (43858) pp: pp rom version: e7ae62f
I (43858) net80211: net80211 rom version: e7ae62f
I (43868) wifi:wifi driver task: 3fcaf
RX: 6b0, prio:23, stack:6656, core=0
I (43878) wifi:wifi firmware version: 14da9b7
I (43878) wifi:wifi certification version: v7.0
I (43878) wifi:config NVS flash: enabled
I (43878) wifi:config nano formatting: disabled
I (43878) wifi:Init data frame dynamic rx buffer num: 32
I (43888) wifi:Init static rx mgmt buffer num: 5
I (43888) wifi:Init management short buffer num: 32
I (43898) wifi:Init dynamic tx buffer num: 32
I (43898) wifi:Init static tx FG buffer num: 2
I (43898) wifi:Init static rx buffer size: 1600
I (43908) wifi:Init static rx buffer num: 10
I (43908) wifi:Init dynamic rx buffer num: 32
I (43918) wifi_init: rx ba win: 6
I (43918) wifi_init: accept mbox: 6
I (43918) wifi_init: tcpip mbox: 32
I (43928) wifi_init: udp mbox: 6
I (43928) wifi_init: tcp mbox: 6
I (43928) wifi_init: tcp tx win: 5760
I (43938) wifi_init: tcp rx win: 5760
I (43938) wifi_init: tcp mss: 1440
I (43938) wifi_init: WiFi IRAM OP enabled
I (43948) wifi_init: WiFi RX IRAM OP enabled
W (43948) wifi:Password length matches WPA2 standards, authmode threshold changes from OPEN to WPA2
I (43958) phy_init: phy_version 701,f4f1da3a,Mar  3 2025,15:50:10

RX: I (44008) wifi:mode : sta (a0:85:e3:f0:74:08)
I (44008) wifi:enable tsf
CONNECTING

I (44018) wifi:new:<11,0>, old:<1,0>, ap:<255,255>, sta:<11,0>, prof:1, snd_ch_cfg:0x0
I (44018) wifi:state: init -> auth (0xb0)
I (44018) wifi:state: auth -> assoc (0x0)
I (44028) wifi:state: assoc -> run (0x10)
I (44038) wifi:<ba-add>idx:0 (ifx:0, 30:bd:13:38:5a:66), tid:0, ssn:1, winSize:64
I (44058) wifi:connected with Airtel_prak_6498, aid = 1, channel 11, BW20, bssid = 30:bd:13:38:5a:66
I (44058) wifi:security: WPA2-PSK, phy: bgn, rssi: -23
I (44058) wifi:pm start, type: 1

I (44058) wifi:dp: 1, bi: 102400, li: 3, scale listen interval from 307200 us to 307200 us
I (44068) wifi:set rx beacon pti, rx_bcn_pti: 0, bcn_timeout: 25000, mt_pti: 0, mt_time: 10000
I (44128) wifi:AP's beacon interval = 102400 us, DTIM period = 1

RX: I (45408) esp_netif_handlers: sta ip: 192.168.1.5, mask: 255.255.255.0, gw: 192.168.1.1
WIFI_UP


RX: I (45458) wifi:<ba-add>idx:1 (ifx:0, 30:bd:13:38:5a:66), tid:6, ssn:2, winSize:64
I (45608) esp-x509-crt-bundle: Certificate validated

RX: AUTH_SUCCESS


RX: WIFI_UP


RX: WIFI_UP


TX: {
        "mId": "0006",
        "pId": "4321",
        "entry_date": "01-03-2026:9:48",
	"hospital_code":"123456",
	"hmis_code":"12345689",
        "mobile_no": "9820856498",
        "name": "Prakash Dhrutaraj",
        "age": "56",
        "sex": "Male",
        "height": "175",
        "weight": "75",
        "bmi": "24.5",
        "bmr": "1500",
        "bsa": "1.9",
        "temp": "98.6",
        "systolic_bp": "120",
        "diastolic_bp": "80",
        "map": "93",
        "spo2": "98",
        "pr": "72",
	"gnum_isvalid":"yes",
	"seatId":"123"
      }
RX: I (83288) esp-x509-crt-bundle: Certificate validated

RX: DATA_SUCCESS


RX: WIFI_UP


RX: WIFI_UP

verification by curl:

prakash@prakash-HP-ProBook-640-G2:~/REST$ ./get_token_call_api_local_get.sh 
eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJodHRwOi8vc2NoZW1hcy54bWxzb2FwLm9yZy93cy8yMDA1LzA1L2lkZW50aXR5L2NsYWltcy9uYW1lIjoiVG5obWlzX1ZpdGFsTWFjaGluZSIsImV4cCI6MTc3MjM4MTY0MSwiaXNzIjoiTXlBcGkiLCJhdWQiOiJNeUFwaVVzZXJzIn0.J0IyHcfvp1dmE_uMSrRUa06k7KAG7TQoQnQJ1ajeSVc
{"message":"Protected data accessed","receivedData":{"mId":"0006","pId":"4321","entry_date":"01-03-2026:9:48","hospital_code":"123456","hmis_code":"12345689","mobile_no":"9820856498","name":"Prakash Dhrutaraj","age":"56","sex":"Male","height":"175","weight":"75","bmi":"24.5","bmr":"1500","bsa":"1.9","temp":"98.6","systolic_bp":"120","diastolic_bp":"80","map":"93","spo2":"98","pr":"72","gnum_isvalid":"yes","seatId":"123"}}prakash@prakash-HP-ProBook-640-G2:~/REST$ 


