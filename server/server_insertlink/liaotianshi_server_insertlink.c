#include "../server_h/liaotianshi_server.h"

void insertlink_tail(user *head,user u)      //插入到用户列表
{
    user*p=head;
    user *new=(user *)malloc(sizeof(user));
    if(new==NULL)
    {
        printf("malloc error!\n");
        return;
    }
    new->next=NULL;
    new->flag=u.flag;
    new->connectfd=u.connectfd;
    strcpy(new->name,u.name);
    strcpy(new->password,u.password);
    new->account=u.account;

    while(p->next!=NULL)        //这里原来把while写成if了怪不得链表就写入两个元素
    {
        p=p->next;
    }
    p->next=new;    
    return;
}