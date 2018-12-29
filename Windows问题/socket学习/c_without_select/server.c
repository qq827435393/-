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
#define LISTNUM 20
  
int main() 
{ 
    int sockfd, newfd; 
    struct sockaddr_in s_addr, c_addr; 
    char buf[BUFLEN]; 
    socklen_t len; 
    unsigned int port, listnum; 
    struct timeval tv; 
    int retval,maxfd; 
      
    /*建立socket*/ 
    if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1){ 
        perror("socket"); 
        exit(errno); 
    }else 
        printf("socket create success!\n"); 
    memset(&s_addr,0,sizeof(s_addr)); 
    s_addr.sin_family = AF_INET; 
    s_addr.sin_port = htons(PORT); 
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    
    /*把地址和端口帮定到套接字上*/ 
    if((bind(sockfd, (struct sockaddr*) &s_addr,sizeof(struct sockaddr))) == -1){ 
        perror("bind"); 
        exit(errno); 
    }else 
        printf("bind success!\n"); 
    /*侦听本地端口*/ 
    if(listen(sockfd,listnum) == -1){ 
        perror("listen"); 
        exit(errno); 
    }else 
        printf("the server is listening!\n"); 
    while(1){ 
        printf("*****************聊天开始***************\n"); 
        len = sizeof(struct sockaddr); 
        if((newfd = accept(sockfd,(struct sockaddr*) &c_addr, &len)) == -1){ 
            perror("accept"); 
            exit(errno); 
        }else 
            printf("正在与您聊天的客户端是：%s: %d\n",inet_ntoa(c_addr.sin_addr),ntohs(c_addr.sin_port)); 
        while(1){  
			/*客户端发来了消息*/ 
			/******接收消息*******/ 
			memset(buf,0,sizeof(buf)); 
			/*fgets函数：从流中读取BUFLEN-1个字符*/ 
			len = recv(newfd,buf,BUFLEN,0); 
			if(len > 0) 
				printf("客户端发来的信息是：%s\n",buf); 
			else{ 
				if(len < 0 ) 
					printf("接受消息失败！\n"); 
				else 
					printf("客户端退出了，聊天终止！\n"); 
				break; 
			}  
        } 
        /*关闭聊天的套接字*/ 
        close(newfd); 
        /*是否退出服务器*/ 
        printf("服务器是否退出程序：y->是；n->否? "); 
        bzero(buf, BUFLEN); 
        fgets(buf,BUFLEN, stdin); 
        if(!strncasecmp(buf,"y",1)){ 
            printf("server 退出!\n"); 
            break; 
        } 
    } 
    /*关闭服务器的套接字*/ 
    close(sockfd); 
    return 0; 
}