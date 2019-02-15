#ifndef __NETORI__
#define __NETORI__
#include <string>
/* 原始套接字（只有超级用户才能创建原始套接字）
* 1. 读写ICMPv4,IGMPv4,ICMPv6等分组
* 2. 读写内核不处理的其协议字段的IPv4数据报
* 3. 自行构造IPv4首部
*/


class netOri
{
public:
	netOri();
	netOri(std::string ip);//原始套接字没有端口
	~netOri();

	int setHdrincl(int enable);

private:
	int m_sockfd;
	std::string m_ip;

};



#endif








