#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SIZE 1024
#define INT_SIZE 4
void error_handling(char * message);

int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[BUF_SIZE];
	char send[] = {6,'\0','\0','\0', 'H', 'e', 'l', 'l','o', '?'};
	int idx = 0, read_len = 0;
	int i, length, str_len, recv_len;

	if(argc != 3)
	{
		printf("Usage : %s <IP> <port> \n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
	{
		error_handling("socket() error");
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
	{error_handling("connect() error!");}
	
	for(i = 0; i < 3; i++)
	{
		length = 0;
		write(sock, send, sizeof(send));
		read(sock, &length, INT_SIZE);
		str_len = 0;
		while(str_len < length)
		{
			recv_len = read(sock, &message[str_len], 1);
			str_len += recv_len;
		}
		message[str_len] = 0;
		printf("Message from server: %s \n", message);
	}
	close(sock);
	return 0;
}

void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
