/* Matrix client playground ***************************************************/

#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void)
{
	int sockfd;
	struct sockaddr_in6 addr;

	sockfd = socket(AF_INET6, SOCK_STREAM, 0);
	if (sockfd == -1)
		printf("Error %d : could not create socket.\n", errno);

	addr.sin6_port = (in_port_t) 8448;
	addr.sin6_addr = (struct in6_addr) { "::1" };

	if (connect(sockfd, (struct sockaddr *) &addr, sizeof(addr)) == -1) {
		printf("Error %d : could not connect socket.\n", errno);
		return errno;
	}

	return 0;
}
