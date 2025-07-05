/**
 *
 *File Operations Example: open(), read(), write(), close()
 *
 * */
 
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
