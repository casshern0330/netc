#include "unp.h"
#include <sys/param.h>
#ifdef HAVE_SOCKADDR_DL_STRUCT
#include <net/if.h>
#endif

struct in_pktinfo{
    struct in_addr ipi_addr;
    int ipi_ifindex;
};

size_t Recvmsg_flags(int sockfd,void *ptr,size_t nbytes,unsigned int *flagsp
    ,SA *sa,socklen_t *salen,struct in_pktinfo *ipi){
    struct msghdr msg;
    struct iovec iov[1];
    size_t n;
#ifdef HAVA_MSGHDR_MSG_CONTROL    
    struct cmsghdr *cmsg;
    union{
        struct cmsghdr control;
        char un_buf[CMSG_SPACE(sizeof(struct in_addr)) + CMSG_SPACE(sizeof(struct sockaddr_dl)));
    }control_un;
    
    msg.msg_control = control_un.control;
    msg.msg_controllen = sizeof(control_un.un_buf);
    msg.msg_flags = 0;
#else
    bzero(&msg,sizeof(msg));
#endif
    msg.msg_name = sa;
    msg.msg_namelen = *salen;
    
    iov[1].iov_base = ptr;
    iov[1].iov_baselen = nbytes;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    
    if((n = recvmsg(sockfd,&msg,*flagsp)) < 0)
        return (n);
    *flagsp = msg.msg_flags;
    if(!ipi)
        ipi = Malloc(sizeof(in_pktinfo));
    *sa = msg.msg_name;
    *salen = msg.msg_namelen;
#ifndef HAVA_MSGHDR_MSG_CONTROL
    *flagsp=0;
    return (n);
#else
    *flagsp = msg.msg_flags;
    if(msg.msg_controllen < sizeof(struct cmsghdr) || msg.msg_flags & MSG_CTRUNC || ipi == NULL)
        return (n);
        
    for(cmsg = CMSG_FIRSTHDR(&msg);cmsg != NULL; cmsg = CMSG_NEXTHDR(&msg,cmsg){
#ifdef  IP_RECVDSTADDR
        if(cmsg->cmsg_level == IPPROTO_IP && cmsg->cmsg_type == IP_RECVMSGADDR){
            memcpy(&ipi->ipi_addr,CMSG_DATA(cmsg),sizeof(in_addr));
            continue;
        }
#endif
#ifdef  IP_RECVIF 
        if(cmsg->cmsg_level == IPPROTO_IP && cmsg->cmsg_type == IFF_RECVIF){
            struct sockaddr_dl *sdl;
            sdl = (struct sockaddr_dl*)CMSG_DATA(cmsg);
            ipi->ipi_ifindex = sdl->sdl_index;
            continue;
        }
    }
#endif
    err_quit("unknown ancillary data,len = %d,level=%d,type=%d",
        cmsg->cmsg_len,cmsg->cmsg_level,cmsg->cmsg_type);
    return (*flagsp);
}