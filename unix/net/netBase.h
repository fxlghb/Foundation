#ifndef __NET_BASE__
#define __NET_BASE__

/*
*�������˵����
*1. �ֽ���ת���������ֽ��� <=> �����ֽ���
*	uint32_t htonl(uint32_t hostlong);
*	uint16_t htons(uint16_t hostshort);
*	uint32_t ntohl(uint32_t netlong);
*	uint16_t ntohs(uint16_t netshort);
*2. ��ַת��   (�ַ��� <=> ���ʮ����)
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
#include <netinet/in.h> //�����׽��ֽṹ��
#include <sys/socket.h> //ͨ���׽��ֽṹ��




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


