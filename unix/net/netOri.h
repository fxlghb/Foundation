#ifndef __NETORI__
#define __NETORI__
#include <string>
/* ԭʼ�׽��֣�ֻ�г����û����ܴ���ԭʼ�׽��֣�
* 1. ��дICMPv4,IGMPv4,ICMPv6�ȷ���
* 2. ��д�ں˲��������Э���ֶε�IPv4���ݱ�
* 3. ���й���IPv4�ײ�
*/


class netOri
{
public:
	netOri();
	netOri(std::string ip);//ԭʼ�׽���û�ж˿�
	~netOri();

	int setHdrincl(int enable);

private:
	int m_sockfd;
	std::string m_ip;

};



#endif








