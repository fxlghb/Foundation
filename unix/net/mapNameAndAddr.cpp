
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>

/*
h_name      正式主机名称
h_aliases   别名
h_addrtype  AF_INET
h_length    4
h_addr_list IP地址
*/
static int dumpHostent(struct hostent *ht)
{
	if(ht)
	{
		printf("hostent::h_name=%s\n",ht->h_name);
		int i=0;
		while(ht->h_aliases[i] != NULL)
		{
			printf("hostent::h_aliases[%d]=%s\n",i,ht->h_aliases[i]);
			i++;
		}
		printf("hostent::h_addrtype=%d\n",ht->h_addrtype);
		printf("hostent::h_length  =%d\n",ht->h_length);
		
        i = 0;
        while(ht->h_addr_list[i] != NULL)
        {
        	printf("hostent::h_addr_list[%d]: %s\n",i,inet_ntoa(*(struct in_addr*)ht->h_addr_list[i]));
            i++;
        }

	}
	return 0;
}


static int testHostent()
{
	char host[100] = {0};
	if(gethostname(host,sizeof(host)) < 0){
		_exit(-1);
	}
	printf("gethostname hostName=%s\n",host);

	//只查IPV4地址
	struct hostent *ht = gethostbyname(host);
	if(ht)
		dumpHostent(ht);
	else
		printf("gethostbyname h_errno=%d[%s]\n", h_errno,hstrerror(h_errno));

	struct in_addr addr;
	addr.s_addr = inet_addr("127.0.0.1");
	ht = gethostbyaddr((char*)&addr, 4, AF_INET);
	if(ht)
		dumpHostent(ht);
	else
		printf("gethostbyname h_errno=%d[%s]\n", h_errno,hstrerror(h_errno));
	return 0;
}

/*
s_name      正式主机名称
s_aliases   别名
s_port  
s_proto    
*/
static int dumpServer(struct servent *st)
{
	if(st)
	{
		printf("servent::s_name=%s\n",st->s_name);
		int i=0;
		while(st->s_aliases[i] != NULL)
		{
			printf("servent::s_aliases[%d]=%s\n",i,st->s_aliases[i]);
			i++;
		}
		printf("servent::s_port=%d\n",st->s_port);
		printf("servent::s_proto=%s\n",st->s_proto);

		printf("*****************************\n\n");
	}
	return 0;
}


static int testServer()
{
	struct servent *st = getservbyname("domain","udp");
	if(st)
		dumpServer(st);
	else
		printf("getservbyname h_errno=%d[%s]\n", h_errno,hstrerror(h_errno));


	st = getservbyport(htons(53), "udp");
	if(st)
		dumpServer(st);
	else
		printf("getservbyport h_errno=%d[%s]\n", h_errno,hstrerror(h_errno));

}



int testMapNameAndAddr()
{

	testServer();

	testHostent();

	return 0;
}



















