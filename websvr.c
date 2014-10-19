#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "bignum.h"
#include <stdio.h>

#define HTTP_PORT 80
#define BACKLOG 10000	// max number of pending connection
#define MAX_BUFFER 4096
#define Q1_STRING "GET /q1?key="
#define Q1_STRING_LEN ((int)sizeof(Q1_STRING)-1)

void error(const char* msg)
{
	perror(msg);
	exit(1); 
}

void response(int sockfd)
{
	int ret;
	const char key[] = "6876766832351765396496377534476050002970857483815262918450355869850085167053394672634315391224052153";
	const char id[] = "Wolken\n5534-0848-5100,0299-6830-9164,4569-9487-7416\n";
	char buf[MAX_BUFFER];
	int len = MAX_BUFFER;
	char* pch = buf;
	char* pend = pch + MAX_BUFFER;
	char* pcheck = pch + Q1_STRING_LEN - 1;
	int found = 0;
	//read
	while (!found)
	{
		ret = read(sockfd, pch, pend - pch);
		if (ret < 0)
		{
			perror("read failed...");
			close(sockfd);
			return;
		}
		pch += ret;
		while (pch > pcheck)
		{
			if (*pcheck == ' ')
			{
				found = 1;
				break;
			}
			pcheck++;
		}
	}
	//prepare response buffer
	*pcheck = '\0';
	printf("divident = %s, len = %d\n", buf + Q1_STRING_LEN, (int)(pcheck-buf)-Q1_STRING_LEN);
	printf("divisor = %s, len = %d\n", key, (int)sizeof(key)-1);
	len = bignum_div(buf + Q1_STRING_LEN, pcheck - buf - Q1_STRING_LEN, key, (int)sizeof(key)-1, buf);
	printf("len = %d\n", len);
	buf[len++] = '\n';
	strncpy(buf + len, id, sizeof(id) - 1);
	len += sizeof(id)-1;
	buf[len++] = '\n';
	buf[len++] = '0';	// timestamp
	buf[len++] = '\n';
	//write
	pend = buf + len;
	pch = buf;
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
	memset((char*)&addr, 0, sizeof(addr));

	// create a listen socket to accept all clients' requests and response

	// bind to port 80
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("socket failed...");
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(HTTP_PORT);
	if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
		error("bind failed...");

	// listen
	if (listen(sockfd, BACKLOG) < 0)
		error("listen failed...");

	while (1)
	{
		// accept
		cli = accept(sockfd, 0, 0);
		
		// read request
		// write response
		// close
		response(cli);
	}
	close(sockfd);
	return 0;
}
