System Calls
System calls are the interface between user space and the Linux kernel. User programs use them to request services from the OS, like:
•	Process control (fork(), exec(), wait())
•	File operations (open(), read(), write(), close())
•	Memory management (mmap(), brk())
•	IPC and networking (pipe(), socket())
Types of Common System Calls
Category	Examples
Process Control	fork(), exec(), wait(), exit()
File Operations	open(), read(), write(), close()
Device Control	ioctl()
Info Management	getpid(), getuid(), gettimeofday()
Communication	pipe(), socket(), shmget()
Signals	signal(), kill()

1. Process Control Example: fork(), exec(), wait()

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        /* Child process */
        printf("Child PID: %d\n", getpid());
        execlp("ls", "ls", "-l", NULL);  /* replace process image */
    } else {
        /* Parent process */
        wait(NULL);  /* wait for child */
        printf("Parent PID: %d\n", getpid());
    }
    return 0;
}

2.File Operations Example: open(), read(), write(), close()

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("file.txt", O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    write(fd, "Hello, system call!\n", 21);
    close(fd);

    char buffer[100];
    fd = open("file.txt", O_RDONLY);
    read(fd, buffer, sizeof(buffer));
    write(STDOUT_FILENO, buffer, 21);
    close(fd);

    return 0;
}

3.Pipe (IPC) with System Calls

#include <stdio.h>
#include <unistd.h>

int main() {
    int pipefd[2];
    char buffer[30];

    pipe(pipefd);  /* create pipe */

    if (fork() == 0) {
        /* Child writes to pipe */
        close(pipefd[0]);
        write(pipefd[1], "Hi Parent!", 10);
        close(pipefd[1]);
    } else {
        /* Parent reads from pipe */
        close(pipefd[1]);
        read(pipefd[0], buffer, 10);
        buffer[10] = '\0';
        printf("Received: %s\n", buffer);
        close(pipefd[0]);
    }

    return 0;
}

4. Simple TCP Client using socket() (System Call)

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server = {
        .sin_family = AF_INET,
        .sin_port = htons(12345),
        .sin_addr.s_addr = inet_addr("127.0.0.1")
    };

    connect(sock, (struct sockaddr *)&server, sizeof(server));
    char *msg = "Hello from client!";
    send(sock, msg, strlen(msg), 0);
    close(sock);
    return 0;
}

Run nc -l 12345 to act as a TCP server.

Inspecting System Calls
You can use strace to trace system calls:
strace ./a.out

