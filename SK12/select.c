#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/select.h>
#define BUF_SIZE 30

int main(int argc, char * argv[])
{
	fd_set reads, temps;	// tempsΪ�����ṩ��ʼ�����ã������ظ���ʼ��readsע����ļ����
	int result, str_len;
	char buf[BUF_SIZE];
	struct timeval timeout;

	FD_ZERO(&reads);	// ��ʼ��fd_set����
	FD_SET(0, &reads);  // 0�Ǳ�׼������ļ�������	//���ļ�������0��Ӧ��λ����Ϊ1������֮����Ҫ���ӱ�׼����ı仯��

	/*
	 timeout.tv_sec = 5;		
	 timeout.tv_usec = 5000;
	*/	//����Ϊ������select�����ĳ�ʱ����ӵġ��������ڴ�ʱ���ó�ʱ��
		//��Ϊÿ�ε���select�����󣬽ṹ��timeval�ĳ�Աtv_sec��tv_usec��ֵ�����滻Ϊ��ʱǰʣ��ʱ�䡣
		//��ˣ�����select����ǰ��ÿ�ζ���Ҫ��ʼ��timeval�ṹ�������

	while(1)
	{
		temps = reads;	//Ϊ�˱�����һ��ѭ������Ӱ�죬ÿ��ѭ���Ŀ�ʼ��Ҫ��fd_set����������λ��գ���ע���׼������ļ�������0��Ϊ�˼�ס��ʼֵ�����ã����뾭�����ָ��ƹ��̡�����ʹ��select������ͨ�÷�����
		timeout.tv_sec = 5;		// ����ʼ��timeval�ṹ��Ĵ������ѭ����ÿ�ε���select����ǰ�����ʼ����ֵ��
		timeout.tv_usec = 0;
		result = select(1, &temps, 0, 0, &timeout); //����select����������п���̨�������ݣ��򷵻ش���0�����������û���������ݶ�������ʱ���򷵻�0��
		if(result == -1)
		{
			puts("select() error!");
			break;
		}
		else if(result == 0)
		{
			puts("Time-out!");
		}
		else
		{
			if(FD_ISSET(0, &temps))		//select�������ش���0��ֵʱ���е�������֤�����仯���ļ��������Ƿ�Ϊ��׼���롣���ǣ���ӱ�׼�����ȡ���ݲ������̨�����
			{
				str_len = read(0, buf, BUF_SIZE);
				buf[str_len] = 0;
				printf("message from console: %s", buf);
			}
		}
	}
	return 0;
}
