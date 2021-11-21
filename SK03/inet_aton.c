#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
void error_handling(char * message);

int main(int argc, char *argv[])
{
	char * addr = "127.232.124.79";
	struct sockaddr_in addr_inet;

	if(!inet_aton(addr, &addr_inet.sin_addr))//转换后的IP地址信息虚构保存到sockaddr_in的in_addr型变量才有意义。因此inet_aton函数的第二个参数要求得到in_addr型的变量地址值。这就省去了手动保存IP地址信息的过程。
		error_handling("Conversion error");
	else
		printf("Network order integer addr: %#x \n",
				addr_inet.sin_addr.s_addr);
	return 0;
}

void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
