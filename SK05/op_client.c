#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024
#define RLT_SIZE 4 //整型数据的的字节大小，用来表示运算操作数的大小。
#define OPSZ 4      // 同上
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int sock;
    char opmsg[BUF_SIZE];
    int result, opnd_cnt, i;
    struct sockaddr_in serv_adr;
    if (argc != 3)
    {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("connect() error!");
    else
        puts("Connected...........");

    fputs("Operand count: ", stdout);
    scanf("%d", &opnd_cnt);     //输入操作数个数
    opmsg[0] = (char)opnd_cnt;  //将运算操作数个数强制转换成char，保存至数组opmsg，因为协议规定运算操作数个数应通过1字节整数型传递，因此不能超过1字节整数型能够表示的范围（0~255 或 -128~127），因为个数不能是负数，所以使用无符号整数型更合理，范围应该为 0~255。

    for (i = 0; i < opnd_cnt; i++)
    {
        printf("Operand %d: ", i + 1);
        scanf("%d", (int *)&opmsg[i * OPSZ + 1]); // 输入整型操作数并保存到数组opmsg。4字节int型要保存到char数组，因而将当前字符数组的一个字节空间转换成4个字节空间，这里也就是将char*转换成int*。
    }
    fgetc(stdin);   //调用fgetc删除缓冲区中的字符\n
    fputs("Operator: ", stdout);
    scanf("%c", &opmsg[opnd_cnt * OPSZ + 1]); //输入运算符
    write(sock, opmsg, opnd_cnt * OPSZ + 2); //调用一次write函数进行传输，也可以分成多次。这是因为TCP中不存在数据边界。
    read(sock, &result, RLT_SIZE);   //保存服务器端传输的运算结果。待接收的数据长度为4字节，调用1次read函数即可接收完毕。

    printf("Operation result: %d \n", result);
    close(sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
