#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void* thread_main(void* arg);

int main(int argc, char* argv[])
{
	pthread_t t_id;
	int thread_param = 5;

	if(pthread_create(&t_id, NULL, thread_main ,(void*)&thread_param) !=0 )
	{//���󴴽�һ���̣߳���thread_main�������ÿ�ʼ���ڵ�����ִ���������С�ͬʱ�ڵ���thread_main����ʱ���䴫��thread_param�����ĵ�ֵַ��
		puts("pthread_create() error");
		return -1;
	}
	sleep(10);//Ϊ�˱�֤�³�����ִ�ж����������䡣
	puts("end of main");
	return 0;
}

void* thread_main(void* arg)//����arg��������pthread_create�����ĵ��ĸ�����
{
	int i;
	int cnt = *((int*)arg);
	for(i = 0; i < cnt; i++)
	{
		sleep(1);
		puts("running thread");
	}
	return NULL;
}
