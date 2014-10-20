#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <gmp.h>
#include <stdio.h>
#include <pthread.h>

#define LISTEN_PORT 123
#define BACKLOG 10000	// max number of pending connection
#define MAX_BUFFER 4096

#define HTTP_HEALTH_STRING "HTTP/1.1 200 OK\nContent-Length: 37\n\n<html><body>hello world</body></html>"
#define HTTP_HEALTH_STRING_LEN ((int)sizeof(HTTP_HEALTH_STRING)-1)

void error(const char* msg)
{
	perror(msg);
	exit(1); 
}

void* response(void* sockfd)
{
	int ret;
	char buf[MAX_BUFFER] = HTTP_HEALTH_STRING;
	char* pch = buf;
	char* pend = pch + HTTP_HEALTH_STRING_LEN;
	//prepare response buffer
	while (pch < pend)
	{
		ret = write(sockfd, buf, pend - pch);
		if (ret < 0)
		{
			perror("write failed...");
			close(sockfd);
			return;
		}
		pch += ret;
	}
	close(sockfd);
}

int main(int argc, char *argv[])
{
	int sockfd, cli;
	struct sockaddr_in addr;
	int rc;
	pthread_t th;
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
		printf("responsing...\n");
		response(cli);
	}
	close(sockfd);
	return 0;
}
