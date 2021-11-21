#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
void error_handling(char *message);

int main(int argc, char * argv[])
{
	int sock;
	int snd_buf = 1024 * 3, rcv_buf = 1024 * 3;
	int state;
	socklen_t len;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	state = setsockopt(sock, SOL_SOCKET, SO_RCVBUF,		//更改输入缓冲为3M字节
		       	(void *)&rcv_buf, sizeof(rcv_buf));
	if(state)
		error_handling("setsockeopt() error!");

	state = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, 	//更改输出缓冲为3M字节
			(void *)&snd_buf, sizeof(snd_buf));
	if(state)
		error_handling("setsockopt() error!");

	len = sizeof(snd_buf);
	state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF,		//为了验证，读取输出缓冲大小
			(void *)&snd_buf, &len);
	if(state)
		error_handling("getsockopt() error!");

	len = sizeof(rcv_buf);
	state = getsockopt(sock, SOL_SOCKET, SO_RCVBUF,		//为了验证，读取输入缓冲大小
			(void*)&rcv_buf, &len);
	
	printf("Input buffer size: %d \n", rcv_buf);	
	printf("Output buffer size: %d \n", snd_buf);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
