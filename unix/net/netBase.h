#ifndef __NET_BASE__
#define __NET_BASE__

/*
*网络基础说明：
*1. 字节序转换（主机字节序 <=> 网络字节序）
*	uint32_t htonl(uint32_t hostlong);
*	uint16_t htons(uint16_t hostshort);
*	uint32_t ntohl(uint32_t netlong);
*	uint16_t ntohs(uint16_t netshort);
*2. 地址转换   (字符串 <=> 点分十进制)
*	char *inet_ntoa(struct in_addr in);
*	int  inet_aton(const char *strptr, struct in_addr *addptr);
*	int  inet_pton(int family, const char *src, void *dst);
*	const char *inet_ntop(int family, const void *src, char *dst, socklen_t cnt);
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h> //网际套接字结构体
#include <sys/socket.h> //通用套接字结构体




class netBase
{
public:
	netBase(){}
	~netBase(){}
	int testEndian();

	char *sock_ntop(const struct sockaddr *sockaddr, socklen_t addrlen);

	ssize_t readn(int fd, void* vptr, size_t n);
	ssize_t writen(int fd, const void* vptr, size_t n);
	ssize_t readLine(int fd, void* vptr, size_t maxLen);

};










#endif


