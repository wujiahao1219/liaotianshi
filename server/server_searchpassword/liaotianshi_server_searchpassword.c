#include "../server_h/liaotianshi_server.h"

user search_password(user* head, user u)    //查找密码，登录时查输入的账户密码和表中对应吗,不匹配返回FAILURE
{
    user* p = head;
    while (p->next != NULL)
    {
        if (p->next->account == u.account)
        {
            if (strcmp(p->next->password, u.password) == 0)
            {
                printf("匹配成功！账号密码正确！\n");
                strcpy(u.name, p->next->name);
                return u;
            }
            printf("密码错误!\n");
            strcpy(u.password, "error");
            return u;
        }
        p = p->next;
    }
    printf("输入账号不存在于用户链表,未进行注册!\n");
    strcpy(u.name, "error");
    return u;
}
