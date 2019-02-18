#include "netBase.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>


#define CPU_VENDOR_OS    "FUXL"

int netBase::testEndian()
{
	union{
		short s;
		char c[sizeof(short)];
	}un;
	
	un.s = 0x0102;
	printf("%s:",CPU_VENDOR_OS);
	if(sizeof(short) == 2)
	{
		if(un.c[0] == 0x01 && un.c[1] == 0x02)
			printf("BIg-Endian\n");
		else if(un.c[0] == 0x02 && un.c[1] == 0x01)
			printf("Little-Endian\n");
		else
			printf("Unknow\n");
	}
	else
	{
		printf("sizeof(short)=%lu\n",sizeof(short));
	}

	return 0;
}

char *netBase::sock_ntop(const struct sockaddr *sockaddr, socklen_t addrlen)
{
	char portstr[8];
	static char str[128];     //unix domain is largst

	switch(sockaddr->sa_family)
	{
		case AF_INET:
		{
			struct sockaddr_in *sin = (struct sockaddr_in*)sockaddr;
			if(inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL)
				return NULL;

			if(ntohs(sin->sin_port) != 0){
				snprintf(portstr, sizeof(portstr),":%d",ntohs(sin->sin_port));
				strcat(str, portstr);
			}

			return str;
		}
		case AF_INET6:
			break;
		default:
			break;
	}
	return NULL;
}


ssize_t netBase::readn(int fd, void* vptr, size_t n)
{
	size_t nleft;
	ssize_t nread;
	char *ptr;
	ptr = (char *)vptr;
	nleft = n;

	while(nleft > 0)
	{
		if((nread = read(fd, ptr, nleft))<0)
		{
			if(errno == EINTR)
				nread = 0;
			else
				return -1;
		}
		else if(nread == 0)
		{
			break;
		}

		nleft -= nread;
		ptr += nread;
	}

	return (n-nleft);
}

ssize_t netBase::writen(int fd, const void* vptr, size_t n)
{
	size_t nleft;
	ssize_t nwritten;
	const char *ptr;
	ptr = (char *)vptr;
	nleft = n;

	while(nleft > 0)
	{
		if((nwritten = write(fd, ptr, nleft))<=0)
		{
			if(nwritten<0 && errno == EINTR)
				nwritten = 0;
			else
				return -1;
		}

		nleft -= nwritten;
		ptr += nwritten;
	}

	return n;
}

ssize_t netBase::readLine(int fd, void* vptr, size_t maxLen)
{
	ssize_t n,rc;
	char c,*ptr;
	ptr = (char *)vptr;

	for(n=1; n<maxLen; n++)
	{
		again:
			if((rc = read(fd,&c,1)) == 1){
				*ptr++ = c;
				if(c == '\n')
					break;
			}
			else if(rc == 0){
				*ptr = 0;
				return n-1;
			}
			else{
				if(errno == EINTR)
					goto again;
				return -1;
			}
	}
	*ptr = 0;

	return n;
}





netSocket::netSocket():m_sockfd(-1),m_family(-1)
{
}

/*
* 	family2?¨ºy:
*				AF_INET   
*				AF_INET6  
*				AF_LOCAL  
*				AF_ROUTE  
*				AF_KEY    
*  	type
*				SOCK_STREAM		
*				SOCK_DGRAM		
*				SOCK_SEQPACKET	
*				SOCK_RAW		
*	protocol
*				IPPROTO_CP		
*				IPPROTO_UDP		
*				IPPROTO_SCTP	
*/
int netSocket::socket(int family, int type, int protocol)
{
	m_sockfd = socket(family, type, protocol);
	if(m_sockfd < 0)
	{
		printf("[DEBUG]%s %s %d errno[%d]:%s\n",__file__,__func__,__LINE__,errno,strerror(errno));
		return -1;
	}

	m_family = family;
	return m_sockfd;
}

int netSocket::accept(int socket, struct sockaddr *address,socklen_t *address_len)
{

}

/*
struct sockaddr_in{
	sa_family_t     sin_family;
	in_port_t       sin_port;
	struct in_addr  sin_addr;
	unsigned char   sin_zero[8];
};
*/
int netSocket::bind(const struct sockaddr *address,socklen_t address_len)
{
	if(m_sockfd < 0)
	{
		printf("[DEBUG]%s %s %d m_sockfd=%d\n",__file__,__func__,__LINE__,m_sockfd);
		return -1;
	}

	int ret = bind(m_sockfd, address, address_len);
	if(ret < 0)
	{
		printf("[DEBUG]%s %s %d errno[%d]:%s\n",__file__,__func__,__LINE__,errno,strerror(errno));
		return -1;
	}
	return 0;
}


int netSocket::connect(const struct sockaddr *address,socklen_t address_len)
{
	if(m_sockfd < 0)
	{
		printf("[DEBUG]%s %s %d m_sockfd=%d\n",__file__,__func__,__LINE__,m_sockfd);
		return -1;
	}

	int ret = connect(m_sockfd, address, address_len);
	if(ret < 0)
	{
		printf("[DEBUG]%s %s %d errno[%d]:%s\n",__file__,__func__,__LINE__,errno,strerror(errno));
		return -1;
	}
	return 0;
}

int netSocket::listen(int backlog)
{
	if(m_sockfd < 0)
	{
		printf("[DEBUG]%s %s %d m_sockfd=%d\n",__file__,__func__,__LINE__,m_sockfd);
		return -1;
	}

	int ret = listen(m_sockfd, backlog);
	if(ret < 0)
	{
		printf("[DEBUG]%s %s %d errno[%d]:%s\n",__file__,__func__,__LINE__,errno,strerror(errno));
		return -1;
	}
	return 0;
}

/
* how
*			SHUT_RD		 
*			SHUT_WR
*			SHUT_RDWR
*/
int netSocket::shutdown(int how)
{
	if(m_sockfd < 0)
	{
		printf("[DEBUG]%s %s %d m_sockfd=%d\n",__file__,__func__,__LINE__,m_sockfd);
		return -1;
	}

	int ret = shutdown(m_sockfd, how);
	if(ret < 0)
	{
		printf("[DEBUG]%s %s %d errno[%d]:%s\n",__file__,__func__,__LINE__,errno,strerror(errno));
		return -1;
	}
	return 0;

}


int netSocket::getSockIp(std::string &ip)
{
	if(m_sockfd < 0)
	{
		printf("[DEBUG]%s %s %d m_sockfd=%d\n",__file__,__func__,__LINE__,m_sockfd);
		return -1;
	}

	struct sockaddr_in addr; 
	socklen_t len = sizeof(struct sockaddr_in);
	int ret = getsockname(m_sockfd, (struct sockaddr*)addr, &len);
	if(ret < 0)
	{
		printf("[DEBUG]%s %s %d errno[%d]:%s\n",__file__,__func__,__LINE__,errno,strerror(errno));
		return -1;
	}

	/char *inet_ntoa(struct in_addr in);
	ip = inet_ntoa(addr.sin_addr);
}

int netSocket::getSockPort(int &port)
{

}







