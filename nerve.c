/* Matrix client playground */

#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	int sockfd;
	struct sockaddr_in6 addr;
	const char *msg = "Hello, world\n";

	sockfd = socket(AF_INET6, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("Error %d: could not create socket.\n", errno);
		return errno;
	}

	addr.sin6_family = AF_INET6;
	addr.sin6_port = htons(9999);
	addr.sin6_flowinfo = 0;
	addr.sin6_addr = in6addr_loopback;
	addr.sin6_scope_id = 0;

	if (connect(sockfd, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
		printf("Error %d: could not connect socket.\n", errno);
		return errno;
	}

	if (send(sockfd, msg, strlen(msg)+1, 0) == -1) {
		printf("Error %d: could not send message.\n", errno);
		return errno;
	}

	close(sockfd);

	return 0;
}
