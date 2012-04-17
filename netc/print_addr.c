#include "unp.h"

int main(int argc,char *argv[])
{
	struct addrinfo hints,*ai,*resai;
	struct sockaddr sa;
	char *servicename,*hostname;
	if(argc == 2){
		hostname = argv[1];
	}else if(argc == 3){
		servicename = argv[2];
		hostname = argv[1];
	}else 
		err_quit("usgae:print_addr [<Hostname>] servicename");

	bzero(&hints,sizeof(struct addrinfo));
	hints.ai_flags = AI_CANONNAME;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if((n = getaddrinfo(hostname,servicename,&hints,&ai)) < 0)
		err_sys("error getaddrinfo for %s %s:%s\n",hostname,servicename,gai_errorstr(n));

	resai = ai;
	do{
		printf("server addr is %s\n",inet_ntop(ai->ai_family,ai->ai_addr,ai->ai_addrlen));
	}while((ai = ai->ai_next) != NULL)

	freeaddrinfo(resai);
	exit(0);
}
