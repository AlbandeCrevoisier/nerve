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
	char in[1024], out[1024], s[1025];
	int r;
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

	r = 0;
	while (r == 0) {
		if((r = read(sockfd, in, strlen(in))) == -1 ) {
			printf("Error %d: could not read message.\n", errno);
			return errno;
		}
	}
	printf("Read %d bytes:\n", r);
	strncpy(s, in, r+1);
	printf("%s\n", s);


	close(sockfd);

	return 0;
}
