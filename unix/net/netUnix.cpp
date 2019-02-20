#include "netUnix.h"
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>


netUnix::netUnix()
{
	m_sockfd = 0;
}


netUnix::~netUnix()
{

}

int netUnix::net_unlink()
{
	if(m_path.empty())
		return -1;

	return unlink(m_path.c_str());
}

int netUnix::net_socket()
{
	m_sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
	switch(m_sockfd)
	{
		case EACCES://无权限
			printf("The process does not have appropriate privileges. \n");
			break;
		case ENOBUFS://无资源
			printf("Insufficient resources were available in the system to perform the operation \n");
			break;
		case ENOMEM://无内存
			printf("Insufficient memory was available to fulfill the request \n");
			break;
		case ENOSR://STREAMS 资源不足
			printf("There were insufficient STREAMS resources available for the operation to complete \n");
			break;
		case EAFNOSUPPORT://该实现不支持指定的地址族
			printf("The implementation does not support the specified address family \n");
			break;
		case EMFILE://没有更多文件描述符可用于此过程
			printf("No more file descriptors are available for this process \n");
			break;
		case ENFILE://系统没有更多文件描述符可用。
			printf("No more file descriptors are available for the system. \n");
			break;
		case EPROTONOSUPPORT://地址族不支持该协议，或者实现不支持该协议
			printf("The protocol is not supported by the address family, or the protocol is not supported by the implementation \n");
			break;
		case EPROTOTYPE://协议不支持套接字类型。
			printf("The socket type is not supported by the protocol. \n");
			break;
		default:
			break;
	}

	return 0;
}


int netUnix::net_bind()
{
	return 0;
}
















