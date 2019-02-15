/****************************


****************************/
#include <pthread.h>
#include <iostream>
#include <memory>//定义了管理内存的常规实用程序
#include <stdio.h>
#include <unistd.h>
#include "unix/net/netBase.h"

extern int serverInit();
extern int testMapNameAndAddr();

const char* appName[] = {"net"};
const char* netopt = "h:b:s:c:t:";

int main(int argc, char *argv[])
{
	int opt;

	printf("app[%s] option test begin\n",argv[0]);
	while((opt = getopt(argc, argv, netopt)) != -1)
	{
		printf("option %c:%s \n",opt,optarg);
		
		switch(opt)
		{
			case 'h':
				break;
			case 't':
				printf("option %c:%s \n",opt,optarg);
				{
					netBase nb;
					nb.testEndian();
				}
				break;	
			default:
				break;
		}
	}


    return 0;
}






