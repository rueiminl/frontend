#include <curl/curl.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char* argv[])
{
	CURL *curl;
	CURLcode res;
	int i;
	int ret;
	int len;
	FILE* file;
	char url[1024];

	file = fopen("q1.txt", "r");
	if (file)
	{
		curl = curl_easy_init();
		if (curl)
		{	
			sprintf(url, "http://localhost:8080");
			len = strlen(url);
			fgets(url + len, sizeof(url) - len, file);
			curl_easy_setopt(curl, CURLOPT_URL, url);
			//printf("url=%s\n", url);
			for (i = 0; i < 1000; i++)
			{
				res = curl_easy_perform(curl);
				if (res != CURLE_OK)
					fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
			}
			curl_easy_cleanup(curl);
		}
		fclose(file);
	}
	return 0;
}
