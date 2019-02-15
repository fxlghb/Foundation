#include "netBase.h"

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













