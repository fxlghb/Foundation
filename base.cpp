/****************************


****************************/
#include <pthread.h>
#include <iostream>
#include <memory>//定义了管理内存的常规实用程序
#include <stdio.h>


extern int serverInit();
extern int testMapNameAndAddr();

int main(int argc, char *argv[])
{

	
	testMapNameAndAddr();
    return 0;
}






