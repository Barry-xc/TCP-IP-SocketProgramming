#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
void error_handling(char * message);

int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[30];
	int str_len = 0;
	int idx = 0, read_len = 0;

	if(argc != 3)
	{
		printf("Usage : %s <IP> <port> \n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);	//����TCP�׽��֡���ǰ������������PF_INET��SOCK_STREAM�������ʡ�Ե���������IPPROTO_TCP
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

	while(read_len = read(sock, &message[idx++], 1)) //whileѭ���з�������read������ÿ�ζ�ȡһ���ֽڡ����read����0��ʾ���꣬��ѭ������Ϊ�٣�����whileѭ��
	{
		if(read_len == -1)
			error_handling("read() error!");
		str_len += read_len; // ִ�и����ʱ������read_len��ֵʼ��Ϊ1����Ϊ��37�й涨ÿ�ν���ȡ1���ֽڡ�str_len�д��ж�ȡ�����ֽ�����
	}
	
	printf("Message from server: %s \n", message);
	printf("Function read call count: %d \n", str_len);
	close(sock);
	return 0;
}

void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
