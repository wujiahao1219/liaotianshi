#include "../server_h/liaotianshi_server.h"

int searchaccount_byconnectfd(int connectfd)       //给服务器用：通过connectfd查发送者账号 告诉客户端是谁给你的私聊    
{
    user* p = head;
    while (p->next != NULL)
    {
        if (p->next->connectfd == connectfd)
        {
            return p->next->account;
        }
        p = p->next;
    }
    return 0;
}

