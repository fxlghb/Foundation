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
		case EACCES://��Ȩ��
			printf("The process does not have appropriate privileges. \n");
			break;
		case ENOBUFS://����Դ
			printf("Insufficient resources were available in the system to perform the operation \n");
			break;
		case ENOMEM://���ڴ�
			printf("Insufficient memory was available to fulfill the request \n");
			break;
		case ENOSR://STREAMS ��Դ����
			printf("There were insufficient STREAMS resources available for the operation to complete \n");
			break;
		case EAFNOSUPPORT://��ʵ�ֲ�֧��ָ���ĵ�ַ��
			printf("The implementation does not support the specified address family \n");
			break;
		case EMFILE://û�и����ļ������������ڴ˹���
			printf("No more file descriptors are available for this process \n");
			break;
		case ENFILE://ϵͳû�и����ļ����������á�
			printf("No more file descriptors are available for the system. \n");
			break;
		case EPROTONOSUPPORT://��ַ�岻֧�ָ�Э�飬����ʵ�ֲ�֧�ָ�Э��
			printf("The protocol is not supported by the address family, or the protocol is not supported by the implementation \n");
			break;
		case EPROTOTYPE://Э�鲻֧���׽������͡�
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
















