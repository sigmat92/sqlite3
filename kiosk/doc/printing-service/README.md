
Pantum P2618 is a host-based (GDI) printer.

That means:

Printer firmware is minimal

Host must generate proprietary raster stream

Pantum only supports Windows + x86 Linux

This class of printer is not suitable for embedded ARM systems.


System boots
↓
cupsd starts (userspace)
↓
print-helper starts
↓
Qt6 app starts
↓
Qt app talks to print-helper (TCP / UNIX socket)
↓
Printing works reliably

Qt6 MVC App
  └── PrintServiceClient (Model)
        ↓ TCP / UNIX socket
Print Helper (C++)
  ├── Converts image/PDF
  ├── Calls CUPS API or lp
  └── Error handling
        ↓
CUPS daemon (cupsd)
  ├── USB backend
  ├── Pantum filter
  └── Printer
Install everything outside rootfs:

/opt/print/
├── sbin/cupsd
├── bin/
│   ├── lp
│   ├── lpstat
│   └── print-helper
├── lib/
│   └── libcups.so
├── libexec/cups/
│   ├── backend/usb
│   └── filter/pantum-filter
├── etc/cups/
│   ├── cupsd.conf
│   └── printers.conf
└── var/spool/cups


1.No conflict with system
2.No Yocto rebuild
3.Fully portable

HOST PC (x86)
 ├── Yocto SDK
 ├── Cross-compiles:
 │     ├── CUPS
 │     ├── Ghostscript
 │     └── print_helper
 │
TARGET: i.MX93 FRDM
 ├── /opt/print/sbin/cupsd        ← runs here
 ├── /opt/print/bin/lp gs
 ├── /opt/print/lib/
 ├── /opt/print/libexec/cups/
 ├── /opt/print/helper/print_helper ← runs here
 ├── Pantum P2518 (USB)
 └── Qt Kiosk App

STEP 1.Get CUPS source:
wget https://github.com/OpenPrinting/cups/releases/download/v2.4.7/cups-2.4.7-source.tar.gz
tar xf cups-2.4.7-source.tar.gz
cd cups-2.4.7

STEP 2.Configure CUPS for standalone install

./configure \
  --host=aarch64-poky-linux \
  --prefix=/opt/print \
  --sysconfdir=/opt/print/etc \
  --localstatedir=/opt/print/var \
  --disable-systemd \
  --disable-dbus \
  --disable-avahi \
  --disable-gssapi \
  --disable-pam \
  --without-php \
  --without-python \
  --without-java \
  --disable-webif

STEP 3.Build & install (staging)
make -j$(nproc)
make DESTDIR=$PWD/stage install

Cross-compile Ghostscript (required)
STEP 4.Get Ghostscript

wget https://github.com/ArtifexSoftware/ghostpdl-downloads/releases/download/gs10.03.0/ghostscript-10.03.0.tar.gz
tar xf ghostscript-10.03.0.tar.gz
cd ghostscript-10.03.0

STEP 5.Configure (minimal)
./configure \
  --host=aarch64-poky-linux \
  --prefix=/opt/print \
  --disable-cups \
  --disable-dbus \
  --disable-gtk \
  --disable-x \
  --without-libidn
STEP 6.Build & stage
make -j$(nproc)
make DESTDIR=$PWD/stage install

PART 4 — Deploy to i.MX93
STEP 7.Copy to target
scp -r cups-2.4.7/stage/opt/print root@imx93frdm:/opt/
scp -r ghostscript-10.03.0/stage/opt/print/* root@imx93frdm:/opt/print/

STEP 8.Create runtime directories (target)

On i.MX93:

mkdir -p /opt/print/var/{log,spool}/cups

PART 5 — Runtime setup on i.MX93
STEP 9.Environment (IMPORTANT)

Before running anything:

export PATH=/opt/print/bin:/opt/print/sbin:$PATH
export LD_LIBRARY_PATH=/opt/print/lib
STEP 10. Start CUPS manually (first test)
/opt/print/sbin/cupsd -f


New shell:

lpstat -r


Expected:

scheduler is running

PART 6 — Add Pantum printer
STEP 1.Check USB backend
ls /opt/print/libexec/cups/backend/


You must see:

usb


Now:

lpinfo -v


Expected:

usb://Pantum/P2500%20Series

STEP 2.Add printer
lpadmin -p pantum \
  -E \
  -v usb://Pantum/P2500%20Series \
  -m everywhere


Enable:

cupsenable pantum
cupsaccept pantum

STEP 3.FINAL TEST (gate)
echo "Pantum cross-compiled test" | lp -d pantum


If paper comes out → printing stack is DONE

+++++++
source /opt/fsl-imx-xwayland/6.6-scarthgap/environment-setup-armv8a-poky-linux

# CUPS
./configure --host=aarch64-poky-linux ...
make
make DESTDIR=stage install

# Ghostscript
./configure --host=aarch64-poky-linux ...
make
make DESTDIR=stage install

# Print helper
$CC print_helper.cpp \
  -I/opt/print/include \
  -L/opt/print/lib \
  -lcups \
  -o print_helper

+++++++

PART 7 — Build the C++ Print Helper (cross-compiled)

Now the easy part.

$CC print_helper.cpp \
  -I/opt/print/include \
  -L/opt/print/lib \
  -lcups \
  -o print_helper


Deploy:

scp print_helper root@imx93frdm:/opt/print/helper/

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <thread>
#include <chrono>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

#define PORT 9100
#define TMP_DIR "/tmp/print_jobs/"
#define MAX_RETRIES 3

enum class JobState { QUEUED, PRINTING, DONE, ERROR };

struct Job {
    std::string id;
    std::string file;
    JobState state;
    std::string error;
    int retries;
};

std::unordered_map<std::string, Job> jobs;

bool run_lp(const std::string& file)
{
    std::string cmd = "lp " + file + " > /dev/null 2>&1";
    return system(cmd.c_str()) == 0;
}

void process_job(Job& job)
{
    job.state = JobState::PRINTING;

    for (; job.retries < MAX_RETRIES; job.retries++) {
        if (run_lp(job.file)) {
            job.state = JobState::DONE;
            return;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    job.state = JobState::ERROR;
    job.error = "PRINT_FAILED";
}

void handle_client(int client)
{
    char header[256] = {0};
    read(client, header, sizeof(header));

    if (strncmp(header, "HELLO", 5) == 0) {
        write(client, "READY\n", 6);
        close(client);
        return;
    }

    if (strncmp(header, "PRINT", 5) == 0) {
        char jobId[64];
        int bytes;

        sscanf(header, "PRINT %63s %d", jobId, &bytes);

        std::string path = std::string(TMP_DIR) + jobId + ".pbm";
        std::ofstream out(path, std::ios::binary);

        int received = 0;
        char buf[4096];

        while (received < bytes) {
            int n = read(client, buf, sizeof(buf));
            if (n <= 0) break;
            out.write(buf, n);
            received += n;
        }
        out.close();

        Job job{jobId, path, JobState::QUEUED, "", 0};
        jobs[jobId] = job;

        write(client, "ACCEPTED ", 9);
        write(client, jobId, strlen(jobId));
        write(client, "\n", 1);

        std::thread(process_job, std::ref(jobs[jobId])).detach();
        close(client);
        return;
    }

    if (strncmp(header, "STATUS", 6) == 0) {
        char jobId[64];
        sscanf(header, "STATUS %63s", jobId);

        auto it = jobs.find(jobId);
        if (it == jobs.end()) {
            write(client, "ERROR UNKNOWN_JOB\n", 18);
            close(client);
            return;
        }

        Job& job = it->second;
        if (job.state == JobState::DONE)
            write(client, "DONE\n", 5);
        else if (job.state == JobState::PRINTING)
            write(client, "PRINTING\n", 9);
        else if (job.state == JobState::ERROR) {
            std::string err = "ERROR " + job.error + "\n";
            write(client, err.c_str(), err.size());
        } else
            write(client, "QUEUED\n", 7);

        close(client);
        return;
    }

    write(client, "ERROR BAD_COMMAND\n", 18);
    close(client);
}

int main()
{
    mkdir(TMP_DIR, 0777);

    int server = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    bind(server, (sockaddr*)&addr, sizeof(addr));
    listen(server, 10);

    std::cout << "Print helper v2 running on port " << PORT << std::endl;

    while (true) {
        int client = accept(server, nullptr, nullptr);
        std::thread(handle_client, client).detach();
    }
}
Manual testing (before Qt)
nc 127.0.0.1 9100
HELLO

nc 127.0.0.1 9100
STATUS test123

HOST PC (x86)
 ├── Yocto SDK
 ├── Cross-compiles:
 │     ├── CUPS
 │     ├── Ghostscript
 │     └── print_helper
 │
TARGET: i.MX93 FRDM
 ├── /opt/print/sbin/cupsd        ← runs here
 ├── /opt/print/bin/lp gs
 ├── /opt/print/lib/
 ├── /opt/print/libexec/cups/
 ├── /opt/print/helper/print_helper ← runs here
 ├── Pantum P2518 (USB)
 └── Qt Kiosk App

i.MX93
├── Qt6 Kiosk App (UI, Scanner, QR)
│      (NO printer logic)
│
├── Print Helper (C++ daemon)
│      (network API, error handling)
│
└── CUPS + Printer Driver
       (Pantum GDI hell lives here)

Qt App
  |
HTTP POST (127.0.0.1)
  |
Print Helper (C++)
  |
cupsPrintFile()
  |
CUPS
  |
Pantum P2518 (USB)

On the same i.MX93 CPU, without Yocto image rebuild:

/opt/print/
├── sbin/cupsd
├── bin/lp lpadmin lpstat gs
├── lib/          (all required .so)
├── libexec/cups/ (filters, usb backend)
├── etc/cups/
├── var/spool/cups/
└── helper/print_helper

Qt app talks to print_helper.
print_helper talks to CUPS.
CUPS talks to Pantum.

STEP 1.Get CUPS source
wget https://github.com/OpenPrinting/cups/releases/download/v2.4.7/cups-2.4.7-source.tar.gz
tar xf cups-2.4.7-source.tar.gz
cd cups-2.4.7

STEP 2.Configure CUPS for standalone install

This is critical — we do NOT install to /usr.

./configure \
  --host=aarch64-poky-linux \
  --prefix=/opt/print \
  --sysconfdir=/opt/print/etc \
  --localstatedir=/opt/print/var \
  --disable-systemd \
  --disable-dbus \
  --disable-avahi \
  --disable-gssapi \
  --disable-pam \
  --without-php \
  --without-python \
  --without-java \
  --disable-webif


Minimal
No system dependencies
Perfect for embedded

Build & install (staging)
make -j$(nproc)
make DESTDIR=$PWD/stage install


Now you have:

cups-2.4.7/stage/opt/print/...

PART 3 — Cross-compile Ghostscript (required)

Pantum drivers require GS. No exceptions.

STEP 4.Get Ghostscript
wget https://github.com/ArtifexSoftware/ghostpdl-downloads/releases/download/gs10.03.0/ghostscript-10.03.0.tar.gz
tar xf ghostscript-10.03.0.tar.gz
cd ghostscript-10.03.0

STEP 5 Configure (minimal)
./configure \
  --host=aarch64-poky-linux \
  --prefix=/opt/print \
  --disable-cups \
  --disable-dbus \
  --disable-gtk \
  --disable-x \
  --without-libidn

STEP 6 Build & stage
make -j$(nproc)
make DESTDIR=$PWD/stage install

PART 4 — Deploy to i.MX93
STEP 7 Copy to target
scp -r cups-2.4.7/stage/opt/print root@imx93frdm:/opt/
scp -r ghostscript-10.03.0/stage/opt/print/* root@imx93frdm:/opt/print/

STEP 8 Create runtime directories (target)

On i.MX93:

mkdir -p /opt/print/var/{log,spool}/cups

PART 5 — Runtime setup on i.MX93
STEP 9 Environment (IMPORTANT)

Before running anything:

export PATH=/opt/print/bin:/opt/print/sbin:$PATH
export LD_LIBRARY_PATH=/opt/print/lib

STEP 10 Start CUPS manually (first test)
/opt/print/sbin/cupsd -f


New shell:

lpstat -r


Expected:

scheduler is running

PART 6 — Add Pantum printer
STEP 11 Check USB backend
ls /opt/print/libexec/cups/backend/


You must see:

usb


Now:

lpinfo -v


Expected:

usb://Pantum/P2500%20Series

STEP 12 Add printer
lpadmin -p pantum \
  -E \
  -v usb://Pantum/P2500%20Series \
  -m everywhere


Enable:

cupsenable pantum
cupsaccept pantum

STEP 13 FINAL TEST (gate)
echo "Pantum cross-compiled test" | lp -d pantum


--> If paper comes out → printing stack is DONE

Before building the helper, CUPS MUST already work on i.MX93:

lpstat -r
echo "CUPS test" | lp


If that fails → fix CUPS first.

PART 7 — Build the C++ Print Helper (cross-compiled)
#include <cups/cups.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

static const int PORT = 8080;
static const char* TMP_PDF = "/tmp/print_job.pdf";

/* ---------------- HTTP helpers ---------------- */

static int create_server_socket()
{
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("socket");
        return -1;
    }

    int opt = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if (bind(s, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(s);
        return -1;
    }

    if (listen(s, 5) < 0) {
        perror("listen");
        close(s);
        return -1;
    }

    return s;
}

static bool read_http_request(int client, std::string& body)
{
    char buffer[8192];
    std::string request;

    ssize_t n;
    while ((n = recv(client, buffer, sizeof(buffer), 0)) > 0) {
        request.append(buffer, n);
        if (request.find("\r\n\r\n") != std::string::npos)
            break;
    }

    auto pos = request.find("\r\n\r\n");
    if (pos == std::string::npos)
        return false;

    body = request.substr(pos + 4);
    return true;
}

static void send_http_response(int client, int status, const char* msg)
{
    std::string resp =
        "HTTP/1.1 " + std::to_string(status) + " OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: " + std::to_string(strlen(msg)) + "\r\n\r\n" +
        msg;

    send(client, resp.c_str(), resp.size(), 0);
}

/* ---------------- Printing ---------------- */

static bool print_pdf(const char* printer, const char* filename)
{
    int job_id = cupsPrintFile(
        printer,
        filename,
        "QR Print Job",
        0,
        nullptr
    );

    if (job_id == 0) {
        std::cerr << "cupsPrintFile failed: "
                  << cupsLastErrorString() << std::endl;
        return false;
    }

    std::cout << "Print job submitted, ID=" << job_id << std::endl;
    return true;
}

/* ---------------- main ---------------- */

int main()
{
    const char* printer = cupsGetDefault();
    if (!printer) {
        std::cerr << "No default CUPS printer found\n";
        return 1;
    }

    std::cout << "Using printer: " << printer << std::endl;

    int server = create_server_socket();
    if (server < 0)
        return 1;

    std::cout << "Print helper listening on port " << PORT << std::endl;

    while (true) {
        int client = accept(server, nullptr, nullptr);
        if (client < 0)
            continue;

        std::string pdf_data;
        if (!read_http_request(client, pdf_data)) {
            send_http_response(client, 400, "Bad Request");
            close(client);
            continue;
        }

        // Save PDF
        std::ofstream out(TMP_PDF, std::ios::binary);
        out.write(pdf_data.data(), pdf_data.size());
        out.close();

        if (!print_pdf(printer, TMP_PDF)) {
            send_http_response(client, 500, "Print Failed");
        } else {
            send_http_response(client, 200, "OK");
        }

        close(client);
    }

    return 0;
}

Now the easy part.

$CC print_helper.cpp \
  -I/opt/print/include \
  -L/opt/print/lib \
  -lcups \
  -o print_helper


Deploy:

scp print_helper root@imx93frdm:/opt/print/helper/

Why this works (important insight)

1.used Yocto toolchain → ABI correct

2.avoided image rebuild

3.avoided kernel changes

4.avoided Pantum protocol reverse-engineering

5.now have production-grade printing

This is the cleanest possible solution with given constraints.

Cross-compile the helper (HOST PC)
source /opt/fsl-imx-xwayland/6.6-scarthgap/environment-setup-armv8a-poky-linux

$CC print_helper.cpp \
    -I/opt/print/include \
    -L/opt/print/lib \
    -lcups \
    -o print_helper


Deploy:

scp print_helper root@imx93frdm:/opt/print/helper/

 Run on i.MX93
export LD_LIBRARY_PATH=/opt/print/lib
/opt/print/helper/print_helper


Expected:

Using printer: pantum
Print helper listening on port 8080

 Test from command line (same CPU)
curl -X POST \
  --data-binary @test.pdf \
  http://127.0.0.1:8080/print


 Paper prints → SUCCESS

 Notes (important but concise)

No usblp needed

No libusb needed

Pantum protocol handled by CUPS

Qt app never touches printer

Safe to restart helper anytime

Why this helper is correct?
Requirement	  Met
Cross-compiled	  yes
Same CPU	  yes
Pantum compatible yes	
No Yocto rebuild  yes
No fragile hacks  yes
Production-safe	  yes
 

-----------------------------------------------------------

find /lib/modules/$(uname -r) -name "usblp.ko*"
which cupsd
which gs

root@imx93frdm:~# find /lib/modules/$(uname -r) -name "usblp.ko*"
root@imx93frdm:~# which cupsd
which: no cupsd in (/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin)
root@imx93frdm:~# which gs
which: no gs in (/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin)

libusb + a manual renderer is only path forward.

root@imx93frdm:~# cat /sys/kernel/debug/usb/devices

T:  Bus=01 Lev=00 Prnt=00 Port=00 Cnt=00 Dev#=  1 Spd=480  MxCh= 1
B:  Alloc=  0/800 us ( 0%), #Int=  0, #Iso=  0
D:  Ver= 2.00 Cls=09(hub  ) Sub=00 Prot=01 MxPS=64 #Cfgs=  1
P:  Vendor=1d6b ProdID=0002 Rev= 6.06
S:  Manufacturer=Linux 6.6.36-lts-next-g6ea9451bb6d6 ehci_hcd
S:  Product=EHCI Host Controller
S:  SerialNumber=ci_hdrc.1
C:* #Ifs= 1 Cfg#= 1 Atr=e0 MxPwr=  0mA
I:* If#= 0 Alt= 0 #EPs= 1 Cls=09(hub  ) Sub=00 Prot=00 Driver=hub
E:  Ad=81(I) Atr=03(Int.) MxPS=   4 Ivl=256ms

Download the libusb source code (get the .tar.bz2) on a PC and move it to the board via scp or a thumb drive.
Extract and Build:
e.g. libusb-1.0.27.tar.bz2

tar xjvf libusb-1.0.xx.tar.bz2
cd libusb-1.0.xx
./configure --disable-udev # Critical for minimal images
make

#include <stdio.h>
#include "libusb/libusb.h" // Pointing to local source

int main(int argc, char *argv[]) {
    if (argc < 2) { printf("Usage: ./pantum_send <file.prn>\n"); return 1; }

    libusb_device_handle *handle;
    libusb_init(NULL);
    handle = libusb_open_device_with_vid_pid(NULL, 0x232b, 0xa43a);
    
    if(!handle) { printf("Printer not found! Check connection.\n"); return 1; }
    
    libusb_detach_kernel_driver(handle, 0);
    libusb_claim_interface(handle, 0);

    FILE *f = fopen(argv[1], "rb");
    unsigned char buffer[4096];
    int actual, size;

    while ((size = fread(buffer, 1, sizeof(buffer), f)) > 0) {
        // Change 0x01 to your verified Bulk Out endpoint
        libusb_bulk_transfer(handle, 0x01, buffer, size, &actual, 5000);
    }

    fclose(f);
    libusb_release_interface(handle, 0);
    libusb_close(handle);
    libusb_exit(NULL);
    printf("Transfer complete.\n");
    return 0;
}

gcc pantum_send.c -I./libusb -L./libusb/.libs -lusb-1.0 -lpthread -o pantum_send

./pantum_send test.prn

C program to:
claim the raw hardware interface.
Find the device (Vendor ID: 232b, Product ID: a43a).
Claim the interface.
Write data to the Bulk Out endpoint

1. Identify the Endpoint
First, find the Bulk Out endpoint (where data is sent). Run:
bash-->lsusb -v -d 232b:a43a | grep -E "EndpointDescriptor|bEndpointAddress|Transfer Type"

Look for an endpoint with Transfer Type: Bulk and OUT. It is usually 0x01 or 0x02.

//usb_print.c
#include <stdio.h>
#include <libusb-1.0/libusb.h>

int main() {
    libusb_device_handle *handle;
    libusb_init(NULL);
    handle = libusb_open_device_with_vid_pid(NULL, 0x232b, 0xa43a);
    
    if(!handle) { printf("Printer not found!\n"); return 1; }
    
    libusb_detach_kernel_driver(handle, 0);
    libusb_claim_interface(handle, 0);

    unsigned char data[] = {0x1b, 0x40, 'H', 'e', 'l', 'l', 'o', '\n', '\f'}; // Reset + Text
    int actual;
    // Replace 0x01 with your Bulk Out endpoint address
    libusb_bulk_transfer(handle, 0x01, data, sizeof(data), &actual, 1000);

    printf("Sent %d bytes\n", actual);
    libusb_release_interface(handle, 0);
    libusb_close(handle);
    libusb_exit(NULL);
    return 0;
}

gcc usb_print.c -o usb_print -lusb-1.0
./usb_print

lsusb -v -d 232b:a43a | grep -B 3 "Transfer Type: Bulk" | grep -A 5 "OUT"

bEndpointAddress 0x01 EP 1 OUT \(\rightarrow \) Your endpoint is 0x01.bEndpointAddress 0x02 EP 2 OUT \(\rightarrow \) Your endpoint is 0x02. 

# Check if python can see the device
python3 -c "import usb.core; dev = usb.core.find(idVendor=0x232b, idProduct=0xa43a); print(dev)"

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
