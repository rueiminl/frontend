#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

#define HTTP_SERVER "54.164.235.93"	//ELB
			//"54.85.152.35"	//m3.medium
#define HTTP_PORT 80
#define MAX_BUFFER 4096
//#define HTTP_REQUEST_STRING "GET /test.html HTTP/1.1\nDate: Mon, 20 Oct 2014 06:00:00 UDT\nConnection: close\nHost: www.raylin.com\nFrom: rueiminl@andrew.cmu.edu\nAccept: text/html, text/plain\nUser-Agent: Ray/1.0\n\n"
#define HTTP_REQUEST_STRING "GET /q1?key=20630300497055296189489132603428150008912572451445788755351067609550255501160184017902946173672156459 HTTP/1.1\nHost: www.raylin.com\nConnection: close\n\n"
#define HTTP_REQUEST_STRING_LEN ((int)sizeof(HTTP_REQUEST_STRING)-1)
void error(const char* msg)
{
	perror(msg);
	exit(1); 
}

int main(int argc, char *argv[])
{
	int sockfd, cli;
	struct sockaddr_in addr;
	int rc;
	char buf[MAX_BUFFER];
	int len;
	int ret;
	pthread_t th;
	memset((char*)&addr, 0, sizeof(addr));

	// create a listen socket to accept all clients' requests and response

	// bind to port 80
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("socket failed...");
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(HTTP_SERVER);
	addr.sin_port = htons(HTTP_PORT);
	printf("connecting...\n");
	if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
		error("bind failed...");

	printf("writing...\n");
	len = 0;
	while (len < HTTP_REQUEST_STRING_LEN)
	{
		ret = write(sockfd, HTTP_REQUEST_STRING, HTTP_REQUEST_STRING_LEN - len);
		if (ret <= 0)
			break;
		len += ret;
	}
	while (1)
	{
		// accept
		printf("reading...\n");
		ret = read(sockfd, buf, sizeof(buf));
		printf("recv %d bytes: %s\n", ret, buf);
		if (ret <= 0)
			break;
	}
	close(sockfd);
	return 0;
}
