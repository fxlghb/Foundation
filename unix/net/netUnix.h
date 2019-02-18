/*
*unixÌ×½Ó×Ö±à³Ì
*/

#ifndef __NET_UNIX_H__
#define __NET_UNIX_H__

#include <stdio.h>
#include <string>

class netUnix
{
public:
	netUnix();
	~netUnix();

private:
	int m_sockfd;
	std::string m_path;
	short m_port;
	std::string m_ip;
};






#endif


