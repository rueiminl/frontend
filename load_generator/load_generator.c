#include <curl/curl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_QUESTION 4

void usage(char* arg0)
{
	printf("usage: %s server_location number\n", arg0);
	printf("\teg. %s pretest-1993534053.us-east-1.elb.amazonaws.com 100\n", arg0);
}

int main(int argc, char* argv[])
{
	CURL *curl;
	CURLcode res;
	int i;
	int r;
	int ret;
	int len;
	int num;
	FILE* file[MAX_QUESTION];
	char url[1024];
	int count[MAX_QUESTION] = {0};

	if (argc < 3)
	{
		usage(argv[0]);
		return 0;
	}
	num = atoi(argv[2]);
	if (num <= 0)
	{
		usage(argv[0]);
		return 0;
	}

	for (i = 0; i < MAX_QUESTION; i++)
	{
		sprintf(url, "q%d.txt", i+1);
		file[i] = fopen(url, "r");
	}
	curl = curl_easy_init();
	if (curl)
	{	
		for (i = 0; i < num; i++)
		{
			sprintf(url, "http://%s", argv[1]);
			len = strlen(url);
			r = rand() % MAX_QUESTION;
			fgets(url + len, sizeof(url) - len, file[r]);
			curl_easy_setopt(curl, CURLOPT_URL, url);
			res = curl_easy_perform(curl);
			if (res != CURLE_OK)
				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}
		curl_easy_cleanup(curl);
	}
	for (i = 0; i < MAX_QUESTION; i++)
	{
		if (file[i])
			fclose(file[i]);
	}
	return 0;
}
