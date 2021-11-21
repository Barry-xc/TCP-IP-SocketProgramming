#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char * argv[])
{
	int status;
	pid_t pid = fork();	//�����Ľ��̽��ڵ�13��ͨ��main�����е�return�����ֹ��

	if(pid == 0)
	{
		return 3;
	}
	else
	{
		printf("Child PID: %d \n", pid);
		pid = fork();	//�������ӽ��̽��ڵ�21��ͨ������exit������ֹ��
		if(pid == 0)
		{
			exit(7);
		}
		else
		{
			printf("Child PID: %d \n", pid);
			wait(&status);	//����wait������֮ǰ��ֹ���ӽ��������Ϣ�����浽status������ͬʱ����ӽ��̱���ȫ���١�
			if(WIFEXITED(status))
				printf("Chiled send one: %d \n", WEXITSTATUS(status));

			wait(&status);	// ��Ϊ֮ǰ������2�����̣������ٴε���wait�����ͺꡣ
			if(WIFEXITED(status))
				printf("Child send two: %d \n", WEXITSTATUS(status));
			sleep(30); //Ϊ��ͣ��������ֹ������Ĵ��롣��ʱ���Բ鿴�ӽ��̵�״̬��
		}
	}
	return 0;
}
