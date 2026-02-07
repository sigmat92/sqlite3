We are running:

Yocto minimal image
No CUPS
No ipp-usb
No printer stack at all

This is normal for i.MX93 FRDM images.

option 1: rebuild image with cupsd

recomended for production

option 2:add user service bin manually

not recomended for production 

option 3:use network helper to print

Why this is a GREAT solution ?

1. Zero Yocto changes
2. Zero kernel work
3. Qt app remains simple
4. Printer can change anytime
5. Works over LAN / VLAN
6. Easy to debug with curl

Real-world usage

This exact architecture is used in:

ATMs

Ticket kiosks

Weighing machines

Factory terminals

Self-service POS

Final Architecture (Ethernet-based)
┌────────────────────────┐        Ethernet        ┌──────────────────────────┐
│ i.MX93 (Yocto)         │  HTTP / TCP / JSON     │ Print Helper (Linux PC / │
│ Qt App                 │ ───────────────────▶   │ Raspberry Pi / NUC)      │
│                        │                        │                          │
│ QR Scanner + Generator │                        │ CUPS + Printer Driver    │
│ NO CUPS / NO Yocto     │                        │ Pantum P2518 USB         │
└────────────────────────┘                        └──────────────────────────┘


1. i.MX93 stays clean
2. Printer logic isolated
3. Easy debugging
4. Easy replacement of printer

Components
i.MX93 (Client)

Qt6 app

Sends print job (QR image / PDF / text etc)

Uses Ethernet

No CUPS, no drivers

Print Helper (Server)

Any Linux with CUPS:

Ubuntu PC

Raspberry Pi

Intel NUC

Printer connected via USB

Runs a small HTTP server

Communication Protocol (Simple & Robust)

We use HTTP REST + JSON
Why?

Firewall friendly

Debug with curl

Language independent
