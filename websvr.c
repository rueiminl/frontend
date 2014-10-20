#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <gmp.h>
#include <stdio.h>
#include <pthread.h>

#define HTTP_PORT 80
#define BACKLOG 10000	// max number of pending connection
#define MAX_BUFFER 4096
#define Q1_STRING "GET /q1?key="
#define Q1_STRING_LEN ((int)sizeof(Q1_STRING)-1)
#define HTTP_RESPONSE_STRING "HTTP/1.1 200 OK\nContent-Length: "
#define HTTP_RESPONSE_STRING_LEN ((int)sizeof(HTTP_RESPONSE_STRING)-1)
#define HTTP_HEALTH_STRING "HTTP/1.1 200 OK\nContent-Length: 37\n\n<html><body>hello world</body></html>"
#define HTTP_HEALTH_STRING_LEN ((int)sizeof(HTTP_HEALTH_STRING)-1)
#define ID_STRING "Wolken\n5534-0848-5100,0299-6830-9164,4569-9487-7416"
#define ID_STRING_LEN ((int)sizeof(ID_STRING)-1)
#define KEY_STRING "6876766832351765396496377534476050002970857483815262918450355869850085167053394672634315391224052153"
#define TIMESTAMP "0"
#define TIMESTAMP_LEN 1
void error(const char* msg)
{
	perror(msg);
	exit(1); 
}

void* response(void* sockfd)
{
	int ret;
	const char public_key[] = KEY_STRING;
	const char id[] = ID_STRING;
	const char http[] = HTTP_RESPONSE_STRING;
	char timestamp[36] = TIMESTAMP;
	char private_key[MAX_BUFFER];
	char buf[MAX_BUFFER];
	int len = MAX_BUFFER;
	char* pch = buf;
	char* pend = pch + MAX_BUFFER;
	char* pcheck = pch + Q1_STRING_LEN - 1;
	int found = 0;
	time_t tnow;
	struct tm* now;
	mpz_t x, xy, y;
	mpz_inits(x, y, xy, 0);
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
		if (ret == 0)
		{
			printf("read ret 0...");
			//might be health check
			write(sockfd, HTTP_RESPONSE_STRING "0\n\n", HTTP_RESPONSE_STRING_LEN+3);
			close(sockfd);
			return;
		}
	}
	if (strncmp(buf, Q1_STRING, Q1_STRING_LEN) != 0)
	{
		//buf[30] = 0;
		printf("unknown message...");
		write(sockfd, HTTP_HEALTH_STRING, HTTP_HEALTH_STRING_LEN);
		close(sockfd);
		return;
	}

	//prepare response buffer
	*pcheck = '\0';
	printf("request = \n%s\n", buf);
	mpz_set_str(xy, buf + Q1_STRING_LEN, 10);
	mpz_set_str(x, public_key, 10);
	mpz_cdiv_q(y, xy, x);
	mpz_get_str(private_key, 10, y);
	//printf("divident = %s, len = %d\n", buf + Q1_STRING_LEN, (int)(pcheck-buf)-Q1_STRING_LEN);
	//printf("divisor = %s, len = %d\n", key, (int)sizeof(key)-1);
	//len = bignum_div(buf + Q1_STRING_LEN, pcheck - buf - Q1_STRING_LEN, key, (int)sizeof(key)-1, buf);
	//printf("len = %d\n", len);
	time(&tnow);
	now = localtime(&tnow);
	strftime(timestamp, sizeof(timestamp), "%Y:%m:%d %H:%M:%S", now);
	len = strlen(private_key) + 1 + ID_STRING_LEN + 1 + strlen(timestamp) + 1;
	sprintf(buf, "%s%d\n\n%s\n%s\n%s\n", http, len, private_key, id, timestamp);
	//write
	pend = buf + strlen(buf);
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
	addr.sin_port = htons(HTTP_PORT);
	if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
		error("bind failed...");

	// listen
	if (listen(sockfd, BACKLOG) < 0)
		error("listen failed...");

	while (1)
	{
		// accept
		printf("accepting...\n");
		cli = accept(sockfd, 0, 0);
		
		// read request
		// write response
		// close
		// rc = pthread_create(th, 0, response, (void*)cli);
		// if (rc != 0)
		//	error("pthread_create failed...");
		printf("responsing...\n");
		response(cli);
	}
	close(sockfd);
	printf("test");
	return 0;
}
