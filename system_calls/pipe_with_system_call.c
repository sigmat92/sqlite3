/**
 *
 *pipe (IPC) with System Calls
 *
 **/

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
	printf("child writes to pipe succesfully...\n");
    } else {
        /* Parent reads from pipe */
        close(pipefd[1]);
        read(pipefd[0], buffer, 10);
        buffer[10] = '\0';
	printf("parent receves succesfully...\n");
        printf("Received: %s\n", buffer);
        close(pipefd[0]);
    }

    return 0;
}



