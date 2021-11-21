#include<stdio.h>
#include<arpa/inet.h>

int main(int argc, char * args[])
{
	char *addr1 = "1.2.3.4";
	char *addr2 = "1.2.3.256";	// 1个字节能表示的最大整数为255，也就是说，它是错误的IP地址。利用该错误地址验证inet_addr哈桑农户的错误检测能力。

	unsigned long conv_addr = inet_addr(addr1);	//正常调用
	if(conv_addr == INADDR_NONE)
		printf("Error occured!\n");
	else
		printf("Network ordered integer addr: %#lx \n", conv_addr);

	conv_addr = inet_addr(addr2);	// 调用出现异常。
	if(conv_addr == INADDR_NONE)
		printf("Error occureded \n");
	else
		printf("Network ordered integer addr: %#lx \n\n", conv_addr);
	return 0;
}
