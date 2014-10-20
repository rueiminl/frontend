#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <gmp.h>
#include <stdio.h>
#include <pthread.h>

#define LISTEN_PORT 1025
#define BACKLOG 10000	// max number of pending connection
#define MAX_BUFFER 4096

void error(const char* msg)
{
	perror(msg);
	exit(1); 
}

int main(int argc, char *argv[])
{
	int sockfd, cli;
	struct sockaddr_in addr;
	int ret;
	memset((char*)&addr, 0, sizeof(addr));

	// create a listen socket to accept all clients' requests and response

	// bind to port 80
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("socket failed...");
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(LISTEN_PORT);
	if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
		error("bind failed...");

	// listen
	if (listen(sockfd, BACKLOG) < 0)
		error("listen failed...");

	while (1)
	{
		printf("accepting...\n");
		cli = accept(sockfd, 0, 0);
		if (cli < 0)
			error("accept failed...");
		ret = close(cli);
		if (ret < 0)
			error("close failed...");
		printf("great, the dumb elb comes in, now shut it down...\n");
	}
	return 0;
}
