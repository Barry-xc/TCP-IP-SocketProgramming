#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
void error_handling(char * message);

int main(int argc, char *argv[])
{
	int tcp_sock, udp_sock;
	int sock_type;
	socklen_t optlen;
	int state;

	optlen = sizeof(sock_type);
	tcp_sock = socket(PF_INET, SOCK_STREAM, 0);
	udp_sock = socket(PF_INET, SOCK_DGRAM, 0);
	printf("SOCK_STREAM: %d \n", SOCK_STREAM);	//输出创建TCP时传入的SOCK_STREAM，输出结果为1
	printf("SOCK_DGRAM: %d \n", SOCK_DGRAM);	//输出创建UDP时传入的SOCK_DGRAM，输出结果为2

	state = getsockopt(tcp_sock, SOL_SOCKET, SO_TYPE,	//获取TCP套接字类型信息，将获得SOCK_STREAM常数值1
		       	(void*)&sock_type, &optlen);
	if(state)
		error_handling("getsockopt() error!");
	printf("Socket type one: %d \n", sock_type);	//输出SOCK_STREAM常数值，结果为1

	state = getsockopt(udp_sock, SOL_SOCKET, SO_TYPE,	//获取UDP套接字类型信息，将获得SOCK_DGRAM常数值2
			(void*)&sock_type, &optlen);
	if(state)
		error_handling("getsockopt() error!");
	printf("Socket type two: %d \n", sock_type);	//输出SOCK_DGRAM常数值，结果为2
	return 0;
}

void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
