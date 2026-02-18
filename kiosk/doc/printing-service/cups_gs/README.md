If cross-compiled CUPS + Ghostscript build completed successfully.

This means:

/home/prakash/sqlite3/kiosk/doc/printing-service/cups_gs/build_print_stack/install


now contains ARM64 binaries for:

cupsd

cups libraries

gs (ghostscript)

filters

backend tools

possible deployment models:

1. OPTION A (Recommended)
Copy Entire Install Folder to i.MX93

On host:

cd build_print_stack
tar czf print_stack_arm64.tar.gz install


Copy to board:

scp print_stack_arm64.tar.gz root@imx93frdm:/root/


On board:

cd /opt
tar xzf /root/print_stack_arm64.tar.gz
mv install print_stack


Now you have:

/opt/print_stack/bin/cupsd
/opt/print_stack/bin/gs
/opt/print_stack/sbin/cupsd
/opt/print_stack/lib/

OPTION 2 (More Professional)

Install into /usr/local on target.

But for embedded systems, keeping everything in:

/opt/print_stack


is cleaner and safer.

Next Step — Test on i.MX93

On board:

cd /opt/print_stack/sbin
./cupsd -f

root@imx93frdm:/opt# export LD_LIBRARY_PATH=/opt/print_stack/lib64
root@imx93frdm:/opt# /opt/print_stack/sbin/cupsd -f
root@imx93frdm:/opt# 

root@imx93frdm:/opt# export LD_LIBRARY_PATH=/opt/print_stack/lib64
root@imx93frdm:/opt# /opt/print_stack/sbin/cupsd -f
root@imx93frdm:/opt# mv /root/print_helper .
root@imx93frdm:/opt# ls
g2d_samples  gopoint-apps  ltp	print_helper  print_stack
root@imx93frdm:/opt# ./print_helper 
Print helper v2 running on port 9100

other terminal:

root@imx93frdm:~# export LD_LIBRARY_PATH=/opt/print_stack/lib64
root@imx93frdm:~# /opt/print_stack/bin/lpstat -r
scheduler is not running


root@imx93frdm:~# export LD_LIBRARY_PATH=/opt/print_stack/lib64
root@imx93frdm:~# /opt/print_stack/bin/lpstat -r
scheduler is not running

If no errors → CUPS daemon started successfully.

Open another terminal and check:

ps | grep cupsd

Next: Add Pantum Printer

Now we must:

Check if USB backend exists:

ls /opt/print_stack/lib/cups/backend/


You should see usb.

If yes → good.

Important

Your kernel earlier showed:

usblp not present
cups not installed


CUPS USB backend does NOT require usblp.
It uses libusb directly.

So this setup is correct.

Final Architecture Now

Qt App
↓
PrintServiceClient (TCP)
↓
Print Helper
↓
CUPS (cross compiled)
↓
Ghostscript
↓
Pantum P2518

Before Continuing

On i.MX93 run:

Start manually:

export PATH=/opt/printstack/bin:/opt/printstack/sbin:$PATH
export LD_LIBRARY_PATH=/opt/printstack/lib:$LD_LIBRARY_PATH

cupsd -f


Test:

lpinfo -v

/opt/print_stack/bin/gs -v


If it prints version → Ghostscript works.

Then run:

/opt/print_stack/sbin/cupsd -v


If both run, we proceed to:

✔ Add printer
✔ Test raw print
✔ Integrate helper
✔ Auto-start service

Tell me:

Does gs -v work on board?

Does cupsd -f start without error?

Then we continue to printer setup.


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

