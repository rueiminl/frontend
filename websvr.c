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
#define HTTP_HEALTH_STRING "HTTP/1.1 200 OK\nContent-Length: 37\n\n<html><body>hello world</body></html>"
#define HTTP_HEALTH_STRING_LEN ((int)sizeof(HTTP_HEALTH_STRING)-1)
#define HTTP_RESPONSE_STRING1 "HTTP/1.1 200 OK\nDate: Mon, 20 Oct 2014 07:06:25 GMT\nServer: Apache/2.4.7 (Ubuntu)\nLast-Modified: Tue, 18 May 2004 10:14:49 GMT\nETag: \"24-505d4efaddd76\"\nAccept-Ranges: bytes\nContent-Length: "
#define DATE_OFFSET ((int)sizeof("HTTP/1.1 200 OK\nDate: ")-1)
#define DATEEND_OFFSET (DATE_OFFSET+(sizeof("Mon, 20 Oct 2014 07:06:25 GMT")-1))
#define HTTP_RESPONSE_STRING2 "\nConnection: close\nContent-Type: text/plain\n\n"
#define HTTP_RESPONSE_STRING1_LEN ((int)sizeof(HTTP_RESPONSE_STRING1)-1)
#define HTTP_RESPONSE_STRING2_LEN ((int)sizeof(HTTP_RESPONSE_STRING2)-1)
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
	const char http1[] = HTTP_RESPONSE_STRING1;
	const char http2[] = HTTP_RESPONSE_STRING2;
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
#ifdef _DEBUG
		printf("reading...\n");
#endif
		ret = read(sockfd, pch, pend - pch);
		if (ret < 0)
		{
			perror("read failed...");
			close(sockfd);
			return;
		}
		if (ret == 0)
			break;
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
			close(sockfd);
			return;
		}
	}
	if (strncmp(buf, Q1_STRING, Q1_STRING_LEN) != 0)
	{
#ifdef _DEBUG
		printf("unknown message...");
#endif
		write(sockfd, HTTP_HEALTH_STRING, HTTP_HEALTH_STRING_LEN);
		close(sockfd);
		return;
	}

	//prepare response buffer
	*pcheck = '\0';
#ifdef _DEBUG
	printf("request: %s\n", buf);
#endif

	mpz_set_str(xy, buf + Q1_STRING_LEN, 10);
	mpz_set_str(x, public_key, 10);
	mpz_cdiv_q(y, xy, x);
	mpz_get_str(private_key, 10, y);
	
	time(&tnow);
	now = localtime(&tnow);
	strftime(buf + DATE_OFFSET, sizeof(buf)-DATE_OFFSET, "%a, %d %b %Y %H:%M:%S %z", now);
	buf[DATEEND_OFFSET] = '\n';
	strftime(timestamp, sizeof(timestamp), "%Y:%m:%d %H:%M:%S", now);
	
	len = strlen(private_key) + 1 + ID_STRING_LEN + 1 + strlen(timestamp) + 1;
	sprintf(buf, "%s%d%s%s\n%s\n%s\n", http1, len, http2, private_key, id, timestamp);
#ifdef _DEBUG
	printf("response: %s\n", buf);
#endif
	
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
#ifdef _DEBUG
		printf("accepting...\n");
#endif
		cli = accept(sockfd, 0, 0);
		
		// read request
		// write response
		// close
		//rc = pthread_create(&th, 0, response, (void*)(long)cli);
		//if (rc != 0)
		//	error("pthread_create failed...");
#ifdef _DEBUG
		printf("responsing...\n");
#endif
		response((void*)(long)cli);
	}
	close(sockfd);
	return 0;
}
