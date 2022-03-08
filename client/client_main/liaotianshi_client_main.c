#include "../client_h/liaotianshi_client.h"

int main(int argc,char *argv[])
{
    int sockfd;
    struct sockaddr_in serveraddr,cliaddr;
    int n;
    pthread_t tid_send,tid_recv;

    if(argc != 2)
    {
        printf("need server IP!\n");
        exit (0);
    }

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0)
    {
        perror("socket error!\n");
        exit(1);
    }
    printf("socket success!\n");

    bzero(&serveraddr,sizeof(serveraddr));
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(SEVERPORT);
    serveraddr.sin_addr.s_addr=inet_addr(argv[1]);   //这里笔记写的不清晰，

    if(connect(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr))<0)
    {
        perror("connect error!\n");
        exit(1);
    }
    printf("connect success! | 连接成功！\n");
    
    firstmenu(sockfd);

    // pthread_detach(tid_send);
    // pthread_join(tid_recv,NULL);
    close(sockfd);
    return 0;
}