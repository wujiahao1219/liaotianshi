#include "../server_h/liaotianshi_server.h"
void updatedb(char* password, int account);

void updatepassword(int connectfd)
{
    printf("进入修改密码工作!\n");
    msg * a=(msg *)malloc(sizeof(msg));
    recv(connectfd, a, sizeof(msg), 0);   //客户端发过来信息包，account是账号，msg是旧密码,name里是新密码  这里没用用户包而是信息包不过用就用了吧
    if (strcmp(a->name, "error") == 0)
    {
        printf("两次新密码不一样,修改密码失败!\n");
        return;
    }

    user* p = head;
    while (p->next != NULL)
    {
        if (p->next->account == a->account)
        {
            if (strcmp(p->next->password, a->msg) == 0)
            {
                printf("账号和旧密码匹配成功,修改密码成功!\n");
                strcpy(p->next->password, a->name);        //把新密码写进链表对应位置
                updatedb(a->name, a->account);             //写到数据库里 

                strcpy(a->msg, "right");
                send(connectfd, a, sizeof(msg), 0);          //告诉客户端结果如何
                return;
            }
            strcpy(a->msg, "error");
            send(connectfd, a, sizeof(msg), 0);          //告诉客户端结果旧密码对不上
        }
        p = p->next;
    }
    return;
}