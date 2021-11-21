#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void timeout(int sig)	//�����źŴ��������������͵ĺ�����Ϊ�źŴ�������Handler��
{
	if(sig == SIGALRM)
		puts("Time out!");
	alarm(2);
}

void keycontrol(int sig)	//�����źŴ��������������͵ĺ�����Ϊ�źŴ�������Handler��
{
	if(sig == SIGINT)
		puts("CTRL+C pressed");
}

int main(int argc, char * argv[])
{
	int i;
	signal(SIGALRM, timeout);	//ע��SIGALRM�źż��䴦����
	signal(SIGINT, keycontrol); //ע��SIGINT�źţ����䴦����
	alarm(2);	//ԤԼ2�����SIGALRM�źš�

	for(i = 0; i < 3; i++)
	{
		puts("wait...");
		sleep(100); 
	}
	return 0;

}

