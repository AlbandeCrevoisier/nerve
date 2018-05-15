/* Matrix client playground ***************************************************/

#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>

int main(void)
{
	int socket_desc;

	socket_desc = socket(AF_INET6, SOCK_STREAM, 0);
	if (socket_desc == -1)
		printf("Error %d : could not create socket.\n", errno);

	return 0;
}
