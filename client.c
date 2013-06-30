#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define BUFSIZE				1024

int main(int argc, char * args[]){
	int i;
	int ret;
	int conn_fd;
	char originator[30], terminal[30];
	int serv_port;
	struct sockaddr_in serv_addr;
	char recv_buf[BUFSIZE],send_buf[BUFSIZE], ch[3];
	

	memset(&serv_addr, 0 , sizeof(struct sockaddr_in));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(5510);
	inet_aton("127.0.0.1", &serv_addr.sin_addr);
    

	//创建一个TCP套接字
	conn_fd = socket(AF_INET, SOCK_STREAM, 0);
	//向服务器端发送连接请求
loop:	connect(conn_fd, (struct sockaddr *)&serv_addr,sizeof(struct sockaddr));

	recv(conn_fd, ch, 2, 0);
	if(ch[0] == 'y')
	{
		printf("链接服务端成功！\n");
	}
	else
		goto loop;

	while(1){
	printf("please input originator:");
	scanf("%s",originator);
	printf("please input  terminal :");
	scanf("%s",terminal);
	printf("Please wait...\n");
	strcpy(send_buf,"@");
	strcat(send_buf,originator);
	strcat(send_buf,"#");
	strcat(send_buf,terminal);

	if((send(conn_fd,send_buf,strlen(send_buf)+1,0)) < 0)
		break;
	printf("send =%s\n",send_buf);
	memset(send_buf,0,sizeof(send_buf));
	if((recv(conn_fd, recv_buf, sizeof(recv_buf), 0)) < 0)
	{
		printf("对不起！信息接收失败！\n");

	}
	else
	{
		printf("%s\n",recv_buf);
		memset(recv_buf, 0, sizeof(recv_buf));
	}
	}
	close (conn_fd);

	return 0;
}
