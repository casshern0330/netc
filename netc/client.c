#include "unp.h"
#include "error.c"

void str_cli(FILE *fp,int sockfd);

int main(int argc,char *argv[])
{
	int sockfd;
	struct sockaddr_in servaddr;
	
	if(argc != 2)
		err_quit("usage a.out <IP Address>");
	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
		err_sys("socket err");
		
	memset(&servaddr,0,sizeof(servaddr));	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8998);
	inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
	
	if(connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
		err_sys("connect error");
	
	str_cli(stdin,sockfd);
	close(sockfd);
	return 0;
}

