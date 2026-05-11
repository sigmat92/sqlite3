
network print working on okmx(working print file generated on ubuntu host with cups support):

root@ok-mx93:~/network_printing# ../start_wifi.sh 
[  138.893247] imx-dwmac 428a0000.ethernet eth1: FPE workqueue stop
[  138.938275] imx-dwmac 428a0000.ethernet eth1: PHY [stmmac-1:01] driver [RTL8211F Gigabit Ethernet] (irq=POLL)
[  138.948327] imx-dwmac 428a0000.ethernet eth1: configuring for phy/rgmii-id link mode
wifi wlan0
ssid MetslT1
pasw bac23dac23
waiting...
[  143.586175] IPv6: ADDRCONF(NETDEV_CHANGE): wlan0: link becomes ready
udhcpc: started, v1.36.1
Dropped protocol specifier '.udhcpc' from 'wlan0.udhcpc'. Using 'wlan0' (ifindex=4).
udhcpc: broadcasting discover
udhcpc: broadcasting select for 192.168.45.22, server 192.168.45.1
udhcpc: lease of 192.168.45.22 obtained from 192.168.45.1, lease time 172800
/etc/udhcpc.d/50default: Adding DNS 192.168.45.1
/etc/udhcpc.d/50default: Adding DNS 8.8.8.8
Dropped protocol specifier '.udhcpc' from 'wlan0.udhcpc'. Using 'wlan0' (ifindex=4).
connect ok
root@ok-mx93:~/network_printing# ./ipp_print_2 working.pwg 192.168.45.167
Detected format: image/pwg-raster
Loaded file size: 1013755 bytes
Connecting to printer...
Connected
IPP request sent

========== PRINTER RESPONSE ==========
HTTP/1.1 200 OK
Content-Type: application/ipp
Content-Length: 201

Gattributes-charsetutf-8Httributes-natural-languageenEjob-uri#ipp://192.168.45.167/ipp/print/0113!job-idq#      job-stateDjob-state-reasonsnoneAjob-state-message
======================================

IPP request accepted

printing works
