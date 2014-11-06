#include <curl/curl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX_QUESTION 4

void usage(char* arg0)
{
	printf("usage: %s server_location number [type]\n", arg0);
	printf("\teg. %s pretest-1993534053.us-east-1.elb.amazonaws.com 100 2\n", arg0);
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
	int type = 0;
	FILE* file[MAX_QUESTION];
	char url[1024];
	int count[MAX_QUESTION] = {0};
	clock_t start, end;

	if (argc < 3)
	{
		usage(argv[0]);
		return 0;
	}
	num = atoi(argv[2]);
	if (num < 0)
		num = 0x8fffffff;
	if (argc >= 4)
	{
		type = atoi(argv[3]);
	}

	for (i = 0; i < MAX_QUESTION; i++)
	{
		sprintf(url, "q%d.txt", i+1);
		file[i] = fopen(url, "r");
	}
	curl = curl_easy_init();
	if (curl)
	{	
		start = clock();
		for (i = 0; i < num; i++)
		{
			sprintf(url, "http://%s", argv[1]);
			len = strlen(url);
			if (type != 0)
				r = type - 1;
			else
				r = rand() % MAX_QUESTION;
			count[r]++;
			fgets(url + len, sizeof(url) - len, file[r]);
			curl_easy_setopt(curl, CURLOPT_URL, url);
			res = curl_easy_perform(curl);
			if (res != CURLE_OK)
				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}
		end = clock();
		curl_easy_cleanup(curl);
	}
	for (i = 0; i < MAX_QUESTION; i++)
	{
		if (file[i])
			fclose(file[i]);
	}
	
	for (i = 0; i < MAX_QUESTION; i++)
	{
		if (count[i])
			fprintf(stderr, "q%d = %d (ts = %d, rps = %d); ", i+1, count[i], (int)(end-start), (int)(count[i]*CLOCKS_PER_SEC/(end-start)));
	}
	fprintf(stderr, "\n");
	return 0;
}
