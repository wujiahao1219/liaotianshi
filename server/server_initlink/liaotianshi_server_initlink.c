#include "../server_h/liaotianshi_server.h"

void initlink()                 //用户链表       先全局定义再赋值
{
    user* new = (user*)malloc(sizeof(user));
    new->next = NULL;
    memset(new->name, 0, 20);
    memset(new->password, 0, 20);
    new->account = 0;
    new->flag = 0;
    head = new;
}
