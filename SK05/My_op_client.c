#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SIZE 1024
#define JUMP 4
void error_handling(char *message);

int main(int argc, char * argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[BUF_SIZE];
	char choose;
	int op_count;
	int i;
	char oper;
	int recv_result;


	if(argc != 3)
	{
		printf("Usage: %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
	{
		error_handling("socket() error");
	}

	memset(&message, 0 , sizeof(message));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("connect() error");
	else
		printf("Connected.......");

	while(1)
	{
		printf("whether you want to calculate or not? y/n\n");
		choose = getchar();
		while(choose != 'y' &&  choose != 'n')
		{	
			getchar();
			choose = getchar();
			continue;
		}
		getchar();
		if(choose == 'y')
		{
			printf("input operand count:\n");
			do
			{
				scanf("%d",&op_count);
			}	
			while(op_count < 0 && op_count >9);
			fflush(stdin);
			message[0] = (char)op_count;
			i = 0;
			while(i < op_count)
			{
				printf("[%d]: ", i);
				scanf("%d", (int*)&message[i * JUMP + 1]);
				getchar();
				i++;
			}
			do
			{	
				printf("choose your operator: +/-/* \n");
				scanf("%c", &oper);
				getchar();
			}while(oper != '+' &&  oper != '-' && oper != '*');
			message[i * JUMP + 1] = oper;

			write(sock, message, op_count * JUMP + 2);
			printf("---\n");
			read(sock, &recv_result, 4);
			printf("result = %d\n", recv_result);
		}
		else
			break;

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
