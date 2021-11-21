#include<stdio.h>
#include<unistd.h>
#define BUF_SIZE 30

int main(int argc, char * argv[])
{
	int fds[2];
	char str1[] = "Who are you?";
	char str2[] = "Thank you for you message";
	char buf[BUF_SIZE];
	pid_t pid;

	pipe(fds);
	pid = fork();
	if(pid == 0)
	{
		write(fds[1], str1, sizeof(str1));	
		sleep(2);	// ��ע�͵����ӽ��̽�������һ�е�read��ȡ�Լ�д��ܵ������ݣ��ܵ��е����ݱ�ȡ�����Ӷ������̵���read����ʱ��Ϊû�����ݶ�ȡ��������
		read(fds[0], buf, BUF_SIZE);
		printf("Child proc output: %s \n", buf);
	}
	else
	{
		sleep(1);
		read(fds[0], buf, BUF_SIZE);
		printf("Parent proc output: %s \n", buf);
		write(fds[1], str2, sizeof(str2));
		sleep(3);	// ���ӽ��̽���ǰ����������ʾ��
	}
	return 0;
}
