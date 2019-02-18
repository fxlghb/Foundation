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

int netApp(int argc, char *argv[])
{
	int opt;

	while((opt = getopt(argc, argv, netopt)) != -1)
	{
		switch(opt)
		{
			case 't':
				if(strcmp(optarg, "net"))
				{
					netBase nb;
					nb.testEndian();	
				}
				else
				{
					printf("option %c:%s \n",opt,optarg);
				}
				break;	
			default:
				printf("unkonw option:%s\n",optarg);
				break;
		}
	}

	return 0;
}


int main(int argc, char *argv[])
{
	int opt;

	while((opt = getopt(argc, argv, "a:")) != -1)
	{
		switch(opt)
		{
			case 'h':
				printf("option -a appName\n");
				break;
			case 'a':
				if(strcmp(optarg, "net") == 0)
				{
					netApp(argc, argv);
				}
				else
				{
					printf("unkonw app:%s\n",optarg);
				}
				return 0;	
			default:
				printf("please Specified function\n");
				break;
		}
	}


    return 0;
}






