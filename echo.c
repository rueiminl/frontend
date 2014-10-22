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
	char buf[MAX_BUFFER];
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

		while (1)
		{
			ret = read(cli, buf, sizeof(buf));
			if (ret < 0)
				error("read failed...");
			if (ret == 0)
			{
				printf("ret == 0\n");
				break;
			}
			buf[ret] = 0;
			printf("read %d bytes = %s\n", ret, buf);
			ret = write(cli, buf, ret);
			if (ret < 0)
				error("write failed...");
			printf("write %d bytes back\n", ret);
		}
		close(cli);
	}
	return 0;
}
