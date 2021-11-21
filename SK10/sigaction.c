#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void timeout(int sig)
{
	if(sig == SIGALRM)
		puts("Time out!");
	alarm(2);
}

int main(int argc, char * argv[])
{
	int i;
	struct sigaction act; //Ϊ��ע���źŴ�����������sigaction�ṹ���������sa_handler��Ա�б��溯��ָ��ֵ
	act.sa_handler = timeout;	//��sa_handler��Ա�б��溯��ָ��ֵ
	sigemptyset(&act.sa_mask); //����sigemptyset������sa_mask��Ա������λ��ʼ��Ϊ0��
	act.sa_flags = 0;	//sa_flags��Աͬ����ʼ��Ϊ0��
	sigaction(SIGALRM, &act, 0); //ע��SIGALRM�źŵĴ�������

	alarm(2);	//����alarm����ԤԼ2�����SIGALRM�źš�


	for(i = 0; i < 3; i++)
	{
		puts("wait...");
		sleep(100);
	}
	return 0;
}


