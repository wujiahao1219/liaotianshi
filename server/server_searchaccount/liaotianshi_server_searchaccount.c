#include "../server_h/liaotianshi_server.h"

int search_account(int account)     //注册时查账户有没有重复的功能,查到重复返回SUCCESS
{
    printf("进入账户重复检测！\n");
    user* p = head;
    while (p->next != NULL)
    {
        if (p->next->account == account)
        {
            printf("用户链表中查到重复账户\n");
            return FAILURE;
        }
        p = p->next;
    }
    printf("用户链表中没有查到重复账户\n");
    return SUCCESS;
}