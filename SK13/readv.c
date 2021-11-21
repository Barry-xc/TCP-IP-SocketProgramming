#include<stdio.h>
#include<sys/uio.h>
#define BUF_SIZE 100

int main(int argc, char * argv[])
{
	struct iovec vec[2];
	char buf1[BUF_SIZE] = {0, };
	char buf2[BUF_SIZE] = {0, };
	int str_len;

	vec[0].iov_base = buf1;
	vec[0].iov_len = 5;	//���õ�һ�����ݵı���λ�úʹ�С���������ݵĴ�С��ָ��Ϊ5����ˣ�����buf1�Ĵ�С�Ƕ��٣������ܱ���5���ֽ�
	vec[1].iov_base = buf2;	// vec[0]��ע��Ļ����б���Ϊ5���ֽڣ�ʣ�����ݽ����浽vec[1]��ע��Ļ��塣�ṹ��iovec�ĳ�Աiov_len��Ӧд����յ�����ֽ�����
	vec[1].iov_len = BUF_SIZE;

	str_len = readv(0, vec, 2);	// readv�����ĵ�һ������Ϊ0����˴ӱ�׼����������ݡ�
	printf("Read bytes: %d \n", str_len);
	printf("First message: %s \n", buf1);
	printf("Second message; %s \n", buf2);
	return 0;
}
