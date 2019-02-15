#include "netOri.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>



netOri::netOri()
{
	//IPPROTO_ICMP,IPPROTO_IP,IPPROTO_TCP,IPPROTO_UDP
	m_sockfd = socket(AF_INET, SOCK_RAW,IPPROTO_ICMP);
}

netOri::netOri(std::string ip):m_ip(ip)
{
	//IPPROTO_ICMP,IPPROTO_IP,IPPROTO_TCP,IPPROTO_UDP
	m_sockfd = socket(AF_INET, SOCK_RAW,IPPROTO_ICMP);
}



netOri::~netOri()
{
}


/*
*  开启IP_HDRINCL，发送数据要包含IP首部
*  a. IPv4标识字段可设置为0，从而告知内核设置该值
*  b. IPv4首部校验和字段总是由内核计算并存储
*  c. IPv4选项字段总是可选的
*/
int netOri::setHdrincl(int enable)
{
	int opt = enable;

	if(setsockopt(m_sockfd, IPPROTO_IP, IP_HDRINCL, &opt, sizeof(opt)) < 0)
	{
		printf("setsockopt eorror %s \n",strerror(errno));
		return -1;
	}

	return 0;
}

















