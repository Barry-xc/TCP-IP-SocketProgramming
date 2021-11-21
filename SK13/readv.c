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
	vec[0].iov_len = 5;	//设置第一个数据的保存位置和大小。接受数据的大小已指定为5，因此，无论buf1的大小是多少，最多仅能保存5个字节
	vec[1].iov_base = buf2;	// vec[0]中注册的缓冲中保存为5个字节，剩余数据将保存到vec[1]中注册的缓冲。结构体iovec的成员iov_len中应写入接收的最大字节数。
	vec[1].iov_len = BUF_SIZE;

	str_len = readv(0, vec, 2);	// readv函数的第一个参数为0，因此从标准输入接收数据。
	printf("Read bytes: %d \n", str_len);
	printf("First message: %s \n", buf1);
	printf("Second message; %s \n", buf2);
	return 0;
}
