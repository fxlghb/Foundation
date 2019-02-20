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
*3. sys/socket.h
*	int socket(int family, int type, int protocol=0);
*	int accept(int socket, struct sockaddr *address,socklen_t *address_len);
*	int bind(int socket, const struct sockaddr *address,socklen_t address_len);
*	int connect(int socket, const struct sockaddr *address,socklen_t address_len);
*	int listen(int socket, int backlog);
*	int shutdown(int socket, int how);
*	
*	int getsockopt(int socket, int level, int option_name,void *option_value, socklen_t *option_len);
*	int setsockopt(int socket, int level, int option_name,const void *option_value, socklen_t option_len);
*	int getpeername(int socket, struct sockaddr *address,socklen_t *address_len);
*	int getsockname(int socket, struct sockaddr *address,socklen_t *address_len);
*	int socketpair(int domain, int type, int protocol,int socket_vector[2]);
*	
*	ssize_t recv(int socket, void *buffer, size_t length, int flags);
*	ssize_t recvfrom(int socket, void *buffer, size_t length,int flags, struct sockaddr *address, socklen_t *address_len);
*	ssize_t recvmsg(int socket, struct msghdr *message, int flags);
*	ssize_t send(int socket, const void *message, size_t length, int flags);
*	ssize_t sendmsg(int socket, const struct msghdr *message, int flags);
*	ssize_t sendto(int socket, const void *message, size_t length, int flags,const struct sockaddr *dest_addr, socklen_t dest_len);
*	
*/
#include <cstdio>
#include <unistd.h>
#include <string>
#include <cstring>
#include <cerrno>
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


class netSocket
{
public:
	netSocket();
	~netSocket(){};

	int socket(int family, int type, int protocol=0);
	int accept(struct sockaddr *address,socklen_t *address_len);
	int bind(const struct sockaddr *address,socklen_t address_len);
	int connect(const struct sockaddr *address,socklen_t address_len);
	int listen(int backlog);
	int shutDown(int how);


	int getPeerPort(int &port);
	int getPeerIp(std::string &ip);
	int getSockFamily(int &family);
	int getSockPort(int &port);
	int getSockIp(std::string &ip);

private:
	int m_sockfd;
	int m_family;

};








#endif


