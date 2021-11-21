#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SIZE 30
void error_handling(char * message);

int main(int argc, char * argv[])
{
	int recv_sock;
	int str_len;
	char buf[BUF_SIZE];
	struct sockaddr_in adr;
	struct ip_mreq join_adr;
	if(argc != 3){
		printf("Usage: %s <GroupIP><PORT>\n", argv[0]);
		exit(1);
	}

	recv_sock = socket(PF_INET, SOCK_DGRAM, 0);
	memset(&adr, 0, sizeof(adr));
	adr.sin_family = AF_INET;
	adr.sin_addr.s_addr = htonl(INADDR_ANY);
	adr.sin_port = htons(atoi(argv[2]));

	if(bind(recv_sock, (struct sockaddr*)&adr, sizeof(adr)) == -1)
		error_handling("bind() error");

	// 初始化结构体ip_mreg变量
	join_adr.imr_multiaddr.s_addr = inet_addr(argv[1]);	//初始化多播地址。
	join_adr.imr_interface.s_addr = htonl(INADDR_ANY);	//初始化待加入主机的IP地址。

	setsockopt(recv_sock, IPPROTO_IP,	//利用套接字选项IP_ADD_MEMBERSHIP加入多播组。
		       	IP_ADD_MEMBERSHIP, (void*)&join_adr, sizeof(join_adr));
	while(1)
	{
		str_len = recvfrom(recv_sock, buf, BUF_SIZE - 1, 0, NULL, 0);//通过调用recvfrom函数接收多播数据。如果不需要知道传输数据的主机地址信息，可以向recvfrom函数的第五个和第六个参数分别传递NULL和0。
		if(str_len < 0)
			break;
		buf[str_len] = 0;
		fputs(buf, stdout);
	}
	close(recv_sock);
	return 0;
}

void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}


