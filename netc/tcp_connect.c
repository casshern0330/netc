#include "unp.h"

int tcp_connect(const char *hostname,const char *service)
{
	int sockfd,n;
	struct addrinfo hints,*res,*ressave;

	bzero(&addrinfo,sizeof(struct addrinfo));
	addrinfo.ai_flags = AI_CANONNAME;
	addrinfo.ai_family = AF_UNSPEC;
	addrinfo.ai_socktype = SOCK_STREAM;

	if((n = getaddrinfo(hostname,service,&hints,&res)) != 0)
		err_quit("tcp_connect error for %s,%s:%s",hostname,service,gai_strerror(n));
	ressave = res;
	do{
		if((sockfd = socket(res->ai_family,res->ai_socktype,res->ai_protocol)) < 0)
			continue;
		if(connect(sockfd,res->ai_addr,res->ai_addrlen) == 0)
			break;
		Close(sockfd);
	} while((res = res->ai_next) != NULL);

	/* 这个地方使用while并不容易,因为res已经可以进行循环了，这样就不能把res地址的移动放入到循环里面处理
	while(res != NULL){
		if(sockfd = socket(res->ai_family,res->ai_socktype,res->ai_protocol) < 0)
			continue;
		if(connect(sockfd,res->ai_addr,res->ai_addrlen) == 0)
			break;
		Close(sockfd);
	}
	*/

	if(res == NULL)
		err_sys("tcp_connect error for %s ,%s",hostname,service);
	
	freeaddrinfo(ressave);
	return sockfd;
}
/*
void setup_irq(int irq,struct irqaction *new)
{
	struct irqaction *old,**p;
	struct irq_desc_t *desc;

	desc = irq_desc + irq;
	p = &desc->action;

	spin_lock_irqsave(&desc->lock,flags);

	if(*p != NULL) 
	{
		do{
			old = *p;
		}while((p = &old->next) != NULL);
	}

	*p = new;
}
*/
