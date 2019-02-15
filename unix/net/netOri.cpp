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
*  ����IP_HDRINCL����������Ҫ����IP�ײ�
*  a. IPv4��ʶ�ֶο�����Ϊ0���Ӷ���֪�ں����ø�ֵ
*  b. IPv4�ײ�У����ֶ��������ں˼��㲢�洢
*  c. IPv4ѡ���ֶ����ǿ�ѡ��
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

















