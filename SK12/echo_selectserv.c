#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/time.h>
#include<sys/select.h>



#define BUF_SIZE 100
void error_handling(char *buf);

int main(int argc, char * argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	struct timeval timeout;
	fd_set reads, cpy_reads;

	socklen_t adr_sz;
	int fd_max, str_len, fd_num, i;
	char buf[BUF_SIZE];
	if(argc != 2)
	{
		printf("Usage: %s <port> \n", argv[0]);
		exit(1);
	}
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("listen() error");
	if(listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	FD_ZERO(&reads);
	FD_SET(serv_sock, &reads);	//向要传到select函数第二个参数的fd_set变量reads注册服务器端套接字。
								//这样，接收数据情况的监视对象就包含了服务器端套接字。
								//客户端的连接请求同样通过传输数据完成。
								//因此，服务器端套接字中有接受的数据，就意味着有新的连接请求。
	fd_max = serv_sock;

	while(1)
	{
		cpy_reads = reads;
		timeout.tv_sec = 5;
		timeout.tv_usec = 5000;

		if((fd_num = select(fd_max + 1, &cpy_reads, 0, 0, &timeout)) == -1)	//在while无限循环中调用select函数。select函数的第三和第四个参数为空。只需根据监视目的传递必要的参数。
			break;
		if(fd_num == 0)
			continue;

		for(i = 0; i < fd_max + 1; i++)	
		{
			if(FD_ISSET(i, &cpy_reads))	// 查找发生状态变化的文件描述符
			{
				if(i == serv_sock)	//验证服务器端套接字是否有变化，如果是服务器端套接字的变化，将受理连接请求。
				{
					adr_sz = sizeof(clnt_adr);
					clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
					FD_SET(clnt_sock, &reads);	// 在fd_set变量reads中注册了与客户端连接的套接字文件描述符。
					if(fd_max < clnt_sock)
						fd_max = clnt_sock;
					printf("Connected client: %d \n", clnt_sock);
				}
				else	//发生变化的套接字并非服务器端套接字时，即有要接收的数据时执行else语句。
				{
					str_len = read(i, buf, BUF_SIZE);
					if(str_len == 0)	//接收的数据为EOF时需要关闭套接字，并从reads中删除相应信息。
					{
						FD_CLR(i, &reads);
						close(i);
						printf("closed client: %d \n", i);
					}
					else	//接收的数据为字符串时，执行回声服务。
					{
						write(i, buf, str_len);
					}
				}
			}
		}
	}
	close(serv_sock);
	return 0;
}

void error_handling(char * buf)
{
	fputs(buf, stderr);
	fputc('\n', stderr);
	exit(1);
}


