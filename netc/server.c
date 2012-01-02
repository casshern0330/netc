#include "unp.h"

int main(int argc,char *argv[])
{
	int listenfd,connfd;
	int socklen = 0;
	pid_t pid;
	struct sockaddr_in servaddr,cliaddr;
	
	if((listenfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
		err_sys("socked error");
	
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	socklen = sizeof(servaddr);
	if(bind(listenfd,(struct sockaddr *)&servaddr,socklen) < 0)
		err_sys("bind error");
	
	if(listen(listenfd,LISTENQ) < 0)
		err_sys("listen error");
	
	signal(SIGCHLD,sig_chld);
	while(true)
	{
		socklen = sizeof(cliaddr);
		if((connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&socklen)) < 0) 
		{
			if(errno == EINTR)
			{
				continue;
			} else {
				err_sys();
			}
			err_sys("accept error");
		}
		if((pid = fork(void)) == 0) {
			close(listenfd);
			str_echo(connfd);
			close(connfd);
			exit(0);	//退出进程
		}
		close(connfd);
	}
}

void str_echo(int sockfd)
{
	ssize_t n;
	char line[MAXLINE];
	
	for(;;)
	{
		if((n = Readline(sockfd,line,MAXLINE)) == 0)
			return;								/*connection closed by other end*/
		Writen(sockfd,line,n);
	}
}

//typedef void (*SigFunc)(int)
/**
SigFunc* signal(int signo,SigFunc* func)
{
	struct sigaction act,oact;
	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	
	if(signo == SIGALRM)
	{
		#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;
		#endif
	} else {
		#ifdef SA_RESTART
		act.sa_flags |= SA_RESTART;
		#endif
	}
	
	if(sigaction(signo,&act,&oact) < 0)
		return (SIG_ERR);
	return (oact.sa_handler);
}
**/

/**
* @wait调用一次，只能杀死一个zombie进程，并且不会死锁，在执行过程中，中断是关闭的
void sig_chld(int signo)
{
	pid_t pid;
	int stat;
	pid = wait(&stat);
	printf("child %d terminated\n",pid);
}
*/

//调用多次
void sig_chld(int signo)
{
	pid_t pid;
	int stat;
	while((pid = waitpid(-1,&stat,WNOHANG)) > 0)
		printf("child %d has terminated",pid);
	return;
}
=======
#include "unp.h"
#include "error.c"

void sig_chld(int signo);

int main(int argc,char *argv[])
{
	int listenfd,connfd;
	socklen_t socklen = 0;
	pid_t pid;
	struct sockaddr_in servaddr,cliaddr;
	
	if((listenfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
		err_sys("socked error");
	
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8998);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	socklen = sizeof(servaddr);
	if(bind(listenfd,(struct sockaddr *)&servaddr,socklen) < 0)
		err_sys("bind error");
	
	if(listen(listenfd,LISTENQ) < 0)
		err_sys("listen error");
	
	Signal(SIGCHLD,sig_chld);
	while(1)
	{
		socklen = sizeof(cliaddr);
		if((connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&socklen)) < 0) 
		{
			if(errno == EINTR)
			{
				continue;
			}
			err_sys("accept error");
		}
		if((pid = fork()) == 0) {
			close(listenfd);
			str_echo(connfd);
			close(connfd);
			exit(0);	//退出进程
		}
		close(connfd);
	}
}

/*
void str_echo(int sockfd)
{
	ssize_t n;
	char line[MAXLINE];
	
	for(;;)
	{
		if((n = Readline(sockfd,line,MAXLINE)) == 0)
			return;							
		Writen(sockfd,line,n);
	}
}

//typedef void (*SigFunc)(int)
SigFunc* signal(int signo,SigFunc* func)
{
	struct sigaction act,oact;
	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	
	if(signo == SIGALRM)
	{
		#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;
		#endif
	} else {
		#ifdef SA_RESTART
		act.sa_flags |= SA_RESTART;
		#endif
	}
	
	if(sigaction(signo,&act,&oact) < 0)
		return (SIG_ERR);
	return (oact.sa_handler);
}
void sig_chld(int signo)
{
	pid_t pid;
	int stat;
	pid = wait(&stat);
	printf("child %d terminated\n",pid);
}

void sig_chld(int signo)
{
	pid_t pid;
	int stat;
	while((pid = waitpid(-1,&stat,WNOHANG)) > 0)
		printf("child %d has terminated",pid);
	return;
}
*/

