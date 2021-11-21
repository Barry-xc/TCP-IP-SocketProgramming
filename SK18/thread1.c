#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void* thread_main(void* arg);

int main(int argc, char* argv[])
{
	pthread_t t_id;
	int thread_param = 5;

	if(pthread_create(&t_id, NULL, thread_main ,(void*)&thread_param) !=0 )
	{//请求创建一个线程，从thread_main函数调用开始，在单独的执行流中运行。同时在调用thread_main函数时向其传递thread_param变量的地址值。
		puts("pthread_create() error");
		return -1;
	}
	sleep(10);//为了保证下沉正常执行而添加这条语句。
	puts("end of main");
	return 0;
}

void* thread_main(void* arg)//传入arg参数的是pthread_create函数的第四个参数
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
