#include "socketTest.h"

const char* buildDate = "buildTime: " __TIME__ " "__DATE__ ;

long averageTime(long int input[],int size)
{
	int Max=0,Min=10000;
	long totalTime=0;
	long totalCount=0;
	long averageTime=0;

	for(int i=1;i<size;i++)
	{
		if(input[i]==0)
		{
			continue;
		}

		totalTime += input[i];
		totalCount++;
		
		if(Max<input[i])
		{
			Max = input[i];
		} 
		if(Min>input[i])
		{
			Min = input[i];
		}
		
	}
	averageTime = totalTime/totalCount;
	fprintf(stdout,"Total rx: %d\tMax: %d\tMin: %d\naverage time: %ld(us)\n\n",size, Max, Min, averageTime);
	return averageTime;
}

int 
main(int argc,char* argv[])
{
	int sockfd, n, addr_len;
	struct sockaddr_in srv_addr, cli_addr;
	char rx_data[sizeof(long)]={0};
	char tx_data[2]={'1','1'};
	int rx_len, tx_len;
	int ret;
	int avgTime,waitTime;
	long int time_array[COLLECT_COUNT]={0};
	struct timeval tv_begin,tv_end;
	struct timezone tz;
	long count=0;

	if(argc != 2)
	{
		fprintf(stderr,"%s\n","usage: udps <Server Port>");
		return 0;
	}
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0 )
	{
		fprintf(stderr,"init socket error,please try again\n");
		exit(0);
	}

	memset(&srv_addr, 0 , sizeof(srv_addr));

	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	srv_addr.sin_port = htons(atoi(argv[1]));

	bind(sockfd,(const struct sockaddr_in*)&srv_addr, sizeof(srv_addr));
	//getSocketOpts(sockfd);

	for(int i=0;i<COLLECT_COUNT;i++)
	{
		gettimeofday(&tv_begin,&tz);
		rx_len = recvfrom(sockfd, rx_data, 0, 0, (struct sockaddr *)&cli_addr, &addr_len);
		gettimeofday(&tv_end,&tz);
		//fprintf(stdout,"rx: %s (%d)  \r",rx_data,rx_len);
		time_array[i]=(tv_end.tv_sec-tv_begin.tv_sec)*1000000+(tv_end.tv_usec-tv_begin.tv_usec);
		DEBUG("%5ld", time_array[i]);
		//tx_len = sendto(sockfd, tx_data, 2, 0, (struct sockaddr *)&cli_addr, sizeof(cli_addr));
	};

	avgTime = averageTime(time_array,COLLECT_COUNT);


	fprintf(stdout,"\rpress a key to begin:\n");
	getchar();
	fprintf(stdout,"rx listening:\n");

	while(1)
	{
		gettimeofday(&tv_begin,&tz);
		rx_len = recvfrom(sockfd, rx_data, sizeof(count), 0, (struct sockaddr *)&cli_addr, &addr_len);
		gettimeofday(&tv_end,&tz);
		memcpy(&count,rx_data,sizeof(count));
		waitTime = (tv_end.tv_sec-tv_begin.tv_sec)*1000000+(tv_end.tv_usec-tv_begin.tv_usec);
		fprintf(stdout,"%-10ld:  %d\n",count,waitTime);
		/*
		if(waitTime>avgTime)
		{
			fprintf(stdout,"over avgTime 3 times: %d\n",waitTime);
		}
		*/
	}
	

}
