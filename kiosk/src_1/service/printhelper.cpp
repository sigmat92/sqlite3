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

