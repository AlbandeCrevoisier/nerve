/* Matrix client playground ***************************************************/

#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void)
{
	int sockfd;
	struct sockaddr_in6 homeserver;

	sockfd = socket(AF_INET6, SOCK_STREAM, 0);
	if (socket_desc == -1)
		printf("Error %d : could not create socket.\n", errno);

	homeserver.sin6_port = (in_port_t) 8448;
	homeserver.sin6_addr = (struct in6_addr) { "::1" };

	return 0;
}
