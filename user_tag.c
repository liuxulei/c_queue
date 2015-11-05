#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE 20
#define MYPORT 8887
#define BUFFER_SIZE 1024

int main(int argc, char* argv[]){
    int server_sockfd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(MYPORT);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(server_sockfd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1){
        perror("bind");
        exit(1);
    }else{
        printf("bind is right.");
    }

    if(listen(server_sockfd,QUEUE) == -1){
        perror("listen");
        exit(1);
    }else{
        printf("listen is right");
    }

    char buffer[BUFFER_SIZE];
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);

    int conn = accept(server_sockfd, (struct sockaddr*)&client_addr, &length);
    if(conn<0){
        perror("connect");
        exit(1);
    }else{
        printf("connect is right.");
    }
    
    while(1){
        memset(buffer,0,sizeof(buffer));
        int len = recv(conn,buffer,sizeof(buffer),0);
        if(strcmp(buffer,"exit\n")==0){
            break;
        }
        fputs(buffer,stdout);
        send(conn,buffer,len,0);
    }
    close(conn);
    close(server_sockfd);
    
    //i//printf("%d", conn);
    //printf("%d",server_sockaddr.sin_family);
}
