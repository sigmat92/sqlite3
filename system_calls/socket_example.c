/**
 *
 *4. Simple TCP Client using socket() (System Call)
 *Run nc -l 12345 to act as a TCP server.
 **/
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
