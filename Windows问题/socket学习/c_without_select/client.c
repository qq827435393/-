#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>

#define BUFLEN 1024
#define PORT 6666

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in s_addr;
    socklen_t len;
    unsigned int port;
    char buf[BUFLEN];
    struct timeval tv;
    int retval, maxfd; 
    
    /*建立socket*/
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(errno);
    }else
        printf("socket create success!\n");

    
    /*设置服务器ip*/
    memset(&s_addr,0,sizeof(s_addr));
    s_addr.sin_family = AF_INET;
     s_addr.sin_port = htons(PORT);
    if (inet_aton(argv[1], (struct in_addr *)&s_addr.sin_addr.s_addr) == 0) {
        perror(argv[1]);
        exit(errno);
    }
    /*开始连接服务器*/ 
    if(connect(sockfd,(struct sockaddr*)&s_addr,sizeof(struct sockaddr)) == -1){
        perror("connect");
        exit(errno);
    }else
        printf("conncet success!\n");
    
    while(1){
		printf("准备发送消息!\n");
		/******发送消息*******/ 
		bzero(buf,BUFLEN);
		fgets(buf,BUFLEN,stdin);
	   
		if(!strncasecmp(buf,"quit",4)){
			printf("client 请求终止聊天!\n");
			break;
		}
		len = send(sockfd,buf,strlen(buf),0);
		if(len > 0)
			printf("\t消息发送成功：%s\n",buf); 
		else{
			printf("消息发送失败!\n");
			break; 
		} 
    }
    /*关闭连接*/
    close(sockfd);

    return 0;
}