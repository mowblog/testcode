/**
https://curl.haxx.se/libcurl/c/getinmemory.html
**/


#include <stdio.h>  
#include <stdlib.h>  
#include <string.h> 
#include "curl/curl.h"

#define EMSURL "http://10.162.8.165:8080/ems/v72" 

#define true 1
#define false 0

struct MemoryStruct {
	char *memory;
	size_t size;
};

static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)userp;

	mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory == NULL) {
		/* out of memory! */
		printf("not enough memory (realloc returned NULL)\n");
		return 0;
	}

	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}

int curl_post(char* url,char* postdata)
{
	CURL *curl;
	CURLcode res;
	struct MemoryStruct chunk;

	chunk.memory = (char*)malloc(1);  /* will be grown as needed by the realloc above */
	chunk.size = 0;    /* no data at this point */

	struct curl_slist header = {"Content-Type: text/plain; charset=UTF-8",NULL};  
	//struct curl_slist header = {"application/x-www-form-urlencoded; charset=UTF-8",NULL};  
	
	curl = curl_easy_init();  
	
	curl_easy_setopt(curl,CURLOPT_URL,url); //urlµÿ÷∑  
	//curl_easy_setopt(curl,CURLOPT_RETURNTRANSFER,true);
	curl_easy_setopt(curl,CURLOPT_POST,true);
	curl_easy_setopt(curl,CURLOPT_HTTPHEADER, &header);
	curl_easy_setopt(curl,CURLOPT_POSTFIELDS, postdata);
	curl_easy_setopt(curl,CURLOPT_COOKIEJAR, "c:\\www\\cookie.txt");
	curl_easy_setopt(curl,CURLOPT_COOKIEFILE, "c:\\www\\cookie.txt");

	/* send all data to this function  */
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

	/* we pass our 'chunk' struct to the callback function */
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

	/* some servers don't like requests that are made without a user-agent
	field, so we provide one */
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
	
	res = curl_easy_perform(curl);  
	
	if (res != CURLE_OK) {
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));
	}
	else {
		long hsize;
		char *header, *body;
		res=curl_easy_getinfo(curl,CURLINFO_HEADER_SIZE,&hsize);
		if (res == CURLE_OK)
		{
			header = (char*)malloc(hsize+1);
			body = (char*)malloc(chunk.size);
			memcpy(header, chunk.memory, hsize);
			if (hsize < chunk.size) {
				memcpy(body, chunk.memory + hsize, chunk.size - hsize);
			}
			else {
				memcpy(body, "null", 4);
			}

			
		}

		fprintf(stdout, "header:\n%s\n", header);
		fprintf(stdout, "body:\n%s\n", body);
	}

	curl_easy_cleanup(curl);

	return 0;
}

int curl_post_login(char* url,char* postdata)
{
	CURL *curl;
	CURLcode res;
	//struct curl_slist header = {"Content-Type: text/plain; charset=UTF-8",NULL};  
	struct curl_slist header = {"application/x-www-form-urlencoded; charset=UTF-8",NULL};  
	
	curl = curl_easy_init();  
	
	curl_easy_setopt(curl,CURLOPT_URL,url); //urlµÿ÷∑  
	//curl_easy_setopt(curl,CURLOPT_RETURNTRANSFER,true);
	curl_easy_setopt(curl,CURLOPT_POST,true);
	curl_easy_setopt(curl,CURLOPT_HTTPHEADER, &header);
	curl_easy_setopt(curl,CURLOPT_POSTFIELDS, postdata);
	curl_easy_setopt(curl,CURLOPT_COOKIEJAR, "c:\\www\\cookie.txt");
	curl_easy_setopt(curl,CURLOPT_COOKIEFILE, "c:\\www\\cookie.txt");
	
	res = curl_easy_perform(curl);  
	
	if(res!=CURLE_OK)
	{
		fprintf(stderr,"err: %d",res);
		return -1;
	}
	curl_easy_cleanup(curl);

	return 0;
}

int curl_put(char* url, char* putdata)
{
	CURL *curl;
	CURLcode res;
	struct curl_slist header ={"Content-Type: text/plain; charset=UTF-8",NULL}; 
	
	curl = curl_easy_init();  
	
	curl_easy_setopt(curl,CURLOPT_URL,url); 
	//curl_easy_setopt(curl,CURLOPT_RETURNTRANSFER,true);
	curl_easy_setopt(curl,CURLOPT_HTTPHEADER, header);
	curl_easy_setopt(curl,CURLOPT_POSTFIELDS, putdata);
	curl_easy_setopt(curl,CURLOPT_CUSTOMREQUEST, 'PUT');
	curl_easy_setopt(curl,CURLOPT_HEADER, true);
	
	res = curl_easy_perform(curl);  
	if(res!=CURLE_OK)
	{
		fprintf(stderr,"err: %d",res);
		return -1;
	}
	return 0;
}

int curl_get(char* url)
{
	CURL *curl;
	CURLcode res;
	struct curl_slist header ={"Content-Type: text/plain; charset=UTF-8",NULL}; 
	
	curl = curl_easy_init();  
	curl_easy_setopt(curl,CURLOPT_URL,url); 
	curl_easy_setopt(curl,CURLOPT_HTTPGET, true);

	res = curl_easy_perform(curl);  
	if(res!=CURLE_OK)
	{
		fprintf(stderr,"err: %d",res);
		return -1;
	}
	return 0;
}

int main(int argc,char *argv[])  
{
	char *postdata = "";
	char *urll = "http://www.baidu.com";
	curl_post(urll, postdata);

	char *post_data="<?xml version=\"1.0\" encoding=\"UTF-8\"?> "
"<authenticationDetail>"
"<userName>admin</userName>"
"<password>admin</password>"
"</authenticationDetail>";	
	char *url="http://10.162.8.165:8080/ems/v72/ws/login.ws" ;

	//curl_post(url,post_data);

	//login
	char *url_login="http://10.162.8.165:8080/ems/v72/ws/loginByProductKey.ws";
	
	/*
	char *post_data_login="<?xml version=\"1.0\" encoding=\"UTF-8\"?> "
		"<productKey>"
		"<productKeyId>"
		"3f192170-8bc5-49c4-bcc8-619b42ea1e72"
		"</productKeyId>"
	"</productKey>";
	*/
	
	char *post_data_login="productKey=3f192170-8bc5-49c4-bcc8-619b42ea1e72";

	curl_post_login(url_login,post_data_login);

	//activation
	char *url_activate="http://10.162.8.165:8080/ems/v72/ws/productKey/3f192170-8bc5-49c4-bcc8-619b42ea1e72/activation.ws" ;
	char *post_data2="<?xml version=\"1.0\" encoding=\"UTF-8\"?> "
					"<activation>"
					"<activationInput>"
					"<activationAttribute>"
					"<attributeValue>"
					"<![CDATA["
					"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
					"<hasp_info>"
					"<host_fingerprint type=\"SL-AdminMode\" crc=\"3070235042\">MXhJSV+wEJRImDAChOBJBRAsaqkiRwNmaQNQ9CKIWnXI1bgUSSwBVFkQVB15ReJSkSo2AKBJGUJesPqHJx6Y4IDc7JIWLApw6FKmZCkAaw74i1p1gBCbawkMgFGRnFUdFcMAypd7AuCgQSBHXoiLRAjBtQJQXmC5</host_fingerprint>"
					"</hasp_info>"
					"]]>"
					"</attributeValue>"
					"<attributeName>C2V</attributeName> "
					"</activationAttribute>"
					"<comments>New Comments Added By Web Services</comments>"
					"</activationInput>"
					"</activation>";
	
	curl_post(url_activate,post_data2);

	getchar();
}