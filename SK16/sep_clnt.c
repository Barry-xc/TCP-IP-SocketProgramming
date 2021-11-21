#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SIZE 1024

int main(int argc, char * argv[])
{
	int sock;
	char buf[BUF_SIZE];
	struct sockaddr_in serv_addr;

	FILE* readfp;
	FILE* writefp;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	readfp = fdopen(sock, "r");
	writefp = fdopen(sock, "w");

	while(1)
	{
		if(fgets(buf, sizeof(buf), readfp) == NULL)	//收到EOF时，fgets函数将返回NULL指针。因此，添加if语句使收到NULL时退出循环
			break;
		fputs(buf, stdout);
		fflush(stdout);
	}
	fputs("FROM CLIENT: Thank you! \n", writefp);	//通过该语句向服务器端发送最后的字符串
	fflush(writefp);
	fclose(writefp);
	fclose(readfp);
	return 0;
}
