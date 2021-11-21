#include<stdio.h>
#include<arpa/inet.h>

int main(int argc, char * argv[])
{
	unsigned short host_port = 0x1234;
	unsigned short net_port;
	unsigned long host_addr=0x12345678;
	unsigned long net_addr;
按改变之后的字节序保存。

// 第12、13行：变量host_port和host_addr中的数据转化为网络字节序。若运行环境为小端序CPU，则	net_port = htons(host_port);
	net_addr = htonl(host_addr);

	printf("Host ordered port: %#x \n", host_port);
	printf("Network order port: %#x \n", net_port);
	printf("Host order address: %#lx \n", host_addr);
	printf("Network order address %#lx \n", net_addr);
	return 0;
}
