/* Matrix client playground */

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void)
{
	int sockfd;
	struct sockaddr_in6 addr;
	char in[1024], out[1024];
	int r, rcv, rest;
	const char* msg = "GET / HTTP/1.1\r\n\r\n";

	sockfd = socket(AF_INET6, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("Error %d: could not create socket.\n", errno);
		return errno;
	}

	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(8008);
	addr.sin6_flowinfo = 0;
	addr.sin6_addr = in6addr_loopback;
	addr.sin6_scope_id = 0;

	if (connect(sockfd, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
		printf("Error %d: could not connect socket.\n", errno);
		return errno;
	}

	strncpy(out, msg, strlen(msg)+1);

	if (write(sockfd, out, strlen(out)+1) == -1) {
		printf("Error %d: could not write message.\n", errno);
		return errno;
	}

	rcv = 0;
	rest = sizeof(in)-1;
	do {
		if((r = read(sockfd, in+rcv, rest)) == -1 ) {
			printf("Error %d: could not read message.\n", errno);
			return errno;
		}
		rcv += r;
		rest -= r;
		if (rest < 1) {
			printf("Error: server message longer than buffer.\n");
			return -1;
		}
	} while (r != 0);

	printf("%d\n", rcv);
	strncpy(in, in, strlen(in)+1);
	printf("%s\n", in);

	close(sockfd);

	return 0;
}
