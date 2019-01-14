
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>


#define SERVER_TEST_PORT 		(9527)
#define SERVER_BUF_LEN			(1024)

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


void str_echo(int socketfd)
{
	ssize_t n;
	char buf[SERVER_BUF_LEN];

	again:
		while(n = read(socketfd, buf, SERVER_BUF_LEN))
		{
			writen(socketfd,buf,n);
			printf("read:%s \n",buf);
		}

		if(n<0 && errno == EINTR)
			goto again;

		printf("read error socket[%d] \n",socketfd);
}


int serverInit()
{
	int listenfd, acceptfd;
	struct sockaddr_in serverAddr,clientAddr;
	int sockLen = sizeof(struct sockaddr);

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&serverAddr, 0, sizeof(struct sockaddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(SERVER_TEST_PORT);
	bind(listenfd, (struct sockaddr*)&serverAddr, sockLen);
	listen(listenfd,5);

	for(;;)
	{
		memset(&clientAddr, 0, sockLen);
		acceptfd = accept(listenfd, (struct sockaddr*)&clientAddr, (socklen_t*)&sockLen);
		int pid = fork();
		if(pid == 0)
		{
			close(listenfd);
			str_echo(acceptfd);
			_exit(0);
		}
		close(acceptfd);
	}

}










