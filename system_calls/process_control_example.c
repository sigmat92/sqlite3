/*
 *process control example fork(), exec(), wait()
 */


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

