#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

void* read(void* arg);
void* accu(void* arg);
static sem_t sem_one;
static sem_t sem_two;
static int num;

int main(int argc, char* argv[])
{
	pthread_t id_t1, id_t2;
	sem_init(&sem_one, 0, 0);	//生成信号量，初始值为0
	sem_init(&sem_two, 0, 1);	//生成信号量，初始值为1

	pthread_create(&id_t1, NULL, read, NULL);
	pthread_create(&id_t2, NULL, accu, NULL);

	pthread_join(id_t1, NULL);
	pthread_join(id_t2, NULL);

	sem_destroy(&sem_one);
	sem_destroy(&sem_two);
	return 0;
}

void* read(void* arg)
{
	int i;
	for(i = 0; i < 5; i++)
	{
		fputs("Input num: ", stdout);
		sem_wait(&sem_two);	//利用信号量变量sem_two调用wait函数。
		scanf("%d", &num);
		sem_post(&sem_one); //利用信号量变量sem_one调用post函数。
	}
	return NULL;
}

void* accu(void* arg)
{
	int sum = 0, i;
	for(i = 0; i < 5; i++)
	{
		sem_wait(&sem_one);	//利用信号量变量sen_one调用wait函数
		sum += num;
		sem_post(&sem_two);//利用信号量变量sem_two调用post函数。
	}
	printf("Result: %d\n", sum);
	return NULL;
}


