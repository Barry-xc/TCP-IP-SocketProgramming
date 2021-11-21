#include<stdio.h>
#include<unistd.h>
#define BUF_SIZE 30

int main(int argc, char * argv[])
{
	int fds[2];
	char str[] = "Who are you?";
	char buf[BUF_SIZE];
	pid_t pid;

	pipe(fds);	//����pipe���������ܵ���fds�����б�������I/O���ļ�������
	pid = fork();	//����fork�������ӽ��̽�ӵ��ͨ��pipe�������û�ȡ��2���ļ���������ע�⣡���ƵĲ��ǹܵ����������ڹܵ�I/O���ļ������������ˣ����ӽ���ͬʱӵ��I/O�ļ���������
	if(pid == 0)
	{
		write(fds[1], str, sizeof(str));	//�ӽ�����ܵ���ڴ����ַ���
	}
	else
	{
		read(fds[0], buf, BUF_SIZE);	// �����̴ӹܵ����ڽ����ַ���
		puts(buf);
	}
	return 0;
}
