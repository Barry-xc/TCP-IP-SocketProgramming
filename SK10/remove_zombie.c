#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>

void read_childproc(int sig)
{
	int status;
	pid_t id = waitpid(-1, &status, WNOHANG);
	if(WIFEXITED(status))
	{
		printf("Removed proc id: %d \n", id);
		printf("Child send: %d \n", WEXITSTATUS(status));
	}
}

int main(int argc, char * argv[])
{
	pid_t pid;
	struct sigaction act;
	act.sa_handler = read_childproc; //Ϊ��ע���źŴ�����������sigaction�ṹ���������sa_handler��Ա�溯��ָ��ֵ��
	sigemptyset(&act.sa_mask); // ����sigemtpyset������sa_mask��Ա������λ��ʼ��Ϊ0.
	act.sa_flags = 0;	//sa_flags��Աͬ����ʼ��Ϊ0��
	sigaction(SIGCHLD, &act, 0);	//ע��SIGCHILD�źŶ�Ӧ�Ĵ����������ӽ�����ֹ������õ����ж���ĺ������������е�����waitpid�����������ӽ��̽�������ֹ�������Ϊ��ʬ���̡�

	pid = fork();
	if(pid == 0)
	{
		puts("Hi! I'm child process");
		sleep(10);
		return 12;
	}
	else
	{
		printf("Child proc id: %d \n", pid);
		pid = fork();
		if(pid == 0)
		{
			puts("Hi! I'm child process");
			sleep(10);
			exit(24);
		}
		else
		{
			int i;
			printf("Child proc id: %d \n", pid);
			for(i = 0; i < 5; i++)	//Ϊ�˵ȴ�����SIGCHLD�źţ��Ǹ����̹���ͣ5�Σ�ÿ�μ��5�롣�����ź�ʱ�������̽������ѣ����ʵ����ͣʱ�䲻��25�롣
			{
				puts("wait...");
				sleep(5);
			}
		}
	}
	return 0;
}
