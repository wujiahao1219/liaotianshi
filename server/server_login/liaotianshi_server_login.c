#include "../server_h/liaotianshi_server.h"

int login(user* head, int connectfd)    //把输入的账号密码和用户链表中对比，无误后写入在线链表
{
    printf("准备进行登录操作!\n");
    user u;
    recv(connectfd, &u, sizeof(u), 0);  //收到发过来的用户结构体（只有账号密码）
    u = search_password(head, u);       //放到检测函数里去              
    if (strcmp(u.name, "error") == 0 || strcmp(u.password, "error") == 0)     //不是没有这个账号就是账号密码不匹配
    {
        send(connectfd, &u, sizeof(u), 0);  //函数里拿回来发回去,在客户端告诉结构体name password有没有被改过，改过就是在密码匹配那里不通过
        return FAILURE;
    }

    user* p = head;                                     //登录上把套接字加到链表里
    int a;
    while (p->next != NULL)
    {
        if (p->next->account == u.account)
        {
            p->next->connectfd = connectfd;
            a = p->next->connectfd; 
            p->next->flag=1;                            //登录上把flag=1加到链表里
            printf("flag= %d\n",p->next->flag); 
        }
        p = p->next;
    }
    //防止有人重复登录让p卡住在最后了
    printf("connectfd=%d   p->next->connectfd=%d\n", connectfd, a);
    send(connectfd, &u, sizeof(u), 0);
    return SUCCESS;
}