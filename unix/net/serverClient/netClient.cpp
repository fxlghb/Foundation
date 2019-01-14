

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>



#define SERVER_TEST_PORT 		(9527)
#define SERVER_TEST_IP			("127.0.0.1")


static ssize_t readn(int fd, void* vptr, size_t n)
{
	size_t nleft;
	ssize_t nread;
	char *ptr;
	ptr = (char *)vptr;
	nleft = n;

	while(nleft > 0)
	{
		if((nread = read(fd, ptr, nleft))<0)
		{
			if(errno == EINTR)
				nread = 0;
			else
				return -1;
		}
		else if(nread == 0)
		{
			break;
		}

		nleft -= nread;
		ptr += nread;
	}

	return (n-nleft);
}

static ssize_t writen(int fd, const void* vptr, size_t n)
{
	size_t nleft;
	ssize_t nwritten;
	const char *ptr;
	ptr = (char *)vptr;
	nleft = n;

	while(nleft > 0)
	{
		if((nwritten = write(fd, ptr, nleft))<=0)
		{
			if(nwritten<0 && errno == EINTR)
				nwritten = 0;
			else
				return -1;
		}

		nleft -= nwritten;
		ptr += nwritten;
	}

	return n;
}

static ssize_t readLine(int fd, void* vptr, size_t maxLen)
{
	ssize_t n,rc;
	char c,*ptr;
	ptr = (char *)vptr;

	for(n=1; n<maxLen; n++)
	{
		again:
			if((rc = read(fd,&c,1)) == 1){
				*ptr++ = c;
				if(c == '\n')
					break;
			}
			else if(rc == 0){
				*ptr = 0;
				return n-1;
			}
			else{
				if(errno == EINTR)
					goto again;
				return -1;
			}
	}
	*ptr = 0;

	return n;
}




static void str_cli(int socketfd){
	const char *sendMsg = "HELLO FUXL\n";
	char buf[1024];

	while(1)
	{
		writen(socketfd, sendMsg, strlen(sendMsg)+1);
		if(readLine(socketfd, buf, sizeof(buf)) == 0)
			printf("readLine ereor \n");

		fputs(buf, stdout);
		sleep(1);
	}
}


int clientInit()
{
	int socketfd;
	int sockLen = sizeof(struct sockaddr_in);
	struct sockaddr_in clientAddr;
	

	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&clientAddr, 0, sockLen);
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_port = htons(SERVER_TEST_PORT);
	inet_aton(SERVER_TEST_IP, &clientAddr.sin_addr);

	connect(socketfd, (struct sockaddr*)&clientAddr, sockLen);
	str_cli(socketfd);
	_exit(0);

}


















