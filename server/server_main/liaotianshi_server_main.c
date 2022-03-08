#include "../server_h/liaotianshi_server.h"

void* firstmenu(void* arg)
{
    printf("进入firstmenu!\n");
    int k;
    int connectfd = *((int*)arg);
    while (1)
    {
        recv(connectfd, &k, sizeof(k),0);
        printf("已经接受到客户端请求%d\n",k);
        if (k == 1)
        {
            register1(connectfd);
        }
        else if (k == 2)
        {
            int ret = login(head, connectfd);
            if (ret == SUCCESS)
            {
                printf("登陆成功!\n");
                recv_send(connectfd);    //版本二！！！！！！！！！！
                // sem_init(&sem[i], 0, 0);
                // i++;
                // send1(connectfd, i - 1); //发送消息         //版本三！！！！！！！！！！！！！！！！！！
            }
            else
            {
                printf("登陆失败!\n");
            }
        }
        else if (k == 3)
        {
            updatepassword(connectfd);
        }
        else if (k == 4)
        {
            close(connectfd);
            break;
        }
    }
    return NULL;
}

int main()
{
    head=NULL;                                 
    int listenfd, connectfd;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t clilen;
    struct threadpool *pool =threadpool_init(10,100);

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0)
    {
        perror("socket error!\n");
        exit(1);
    }
    printf("socket success!\n");
    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SEVERPORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);          //结构体前置工作时为啥服务器和客户端写的不一样？？？？

    if (bind(listenfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
    {
        perror("bind error!\n");
        exit(1);
    }
    printf("bind success!\n");

    if (listen(listenfd, 100) < 0)
    {
        perror("listen error!\n");
        exit(1);
    }
    printf("listen success!\n");

    initlink();
    createtable();
    readdb(head);

    for (;;)
    {
        clilen = sizeof(clientaddr);
        printf("accepting!.......\n");
        connectfd = accept(listenfd, (struct sockaddr*)&clientaddr, &clilen);
        if (connectfd < 0)
        {
            perror("accept error!\n");
            exit(1);
        }
        printf("accept success!");
        printf("client ip = %s,client port = %d \n", inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

        thread_add_job(pool,firstmenu, (void*)&connectfd);
    }
    thread_destroy(pool);
    close(listenfd);
    return 0;
}