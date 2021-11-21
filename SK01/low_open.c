#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
void error_handling(char * message);

int main(void)
{
	int fd;
	char buf[] = "Let's go!\n";
	fd = open("data.txt", O_CREAT| O_WRONLY| O_TRUNC);	//�ļ���ģʽΪO_CREAT�� O_WRONLY�� O_TRUNC����ϣ����
														//���������ļ�����ֻ��д��������data.txt�ļ���������ļ���ȫ�����ݡ�
	if(fd == -1)
		error_handling("open() error!");
	printf("file descriptor: %d \n", fd);
	
	if(write(fd, buf, sizeof(buf)) == -1)	// ���Ӧ��fd�б�����ļ����������ļ�����buf�б�������ݡ�
		error_handling("write() error!");
	close(fd);
	return 0;
}
void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
