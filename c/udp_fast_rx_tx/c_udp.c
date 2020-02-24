#include "socketTest.h"

const char* buildDate = __FILE__ " "  __TIME__ " "__DATE__ ;


int 
main(int argc,char* argv[])
{
	int sockfd,n;
	char rx_data[2]={'0','0'};
	char *tx_data;
	struct sockaddr_in srv_addr;
	int addr_len;
	float t=0;
	long count=0;

	if(argc != 3)
	{
		printf("%s\n","usage: udpc <Server IP> <Server Port>");
		return 0;
	}

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	srv_addr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &srv_addr.sin_addr);
	srv_addr.sin_port = htons(atoi(argv[2])); 

	int len = sizeof(count);
	tx_data=(char *) malloc(len);
	memset(tx_data,0,len);
	for(int i=0;i<COLLECT_COUNT;i++)
	{
		sendto(sockfd, tx_data, 0 , 0, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
		//rx_len=recvfrom(sockfd, rx_data, 2 , 0, (struct sockaddr *)&srv_addr, &addr_len);
		//fprintf(stdout,"rx: %s(%d)", rx_data,rx_len);
	};

	fprintf(stdout,"press any key to go on if the server is ready\n");
	getchar();

	
	while(1)
	{
		memset(tx_data,0,len);
		memcpy(tx_data,&count,len);
		sendto(sockfd, tx_data, len , 0, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
		//sleep(10.0*rand()/(RAND_MAX+1.0));
		//t += 0.5;
		//getchar();
		count++;
	}





}
