#include "../server_h/liaotianshi_server.h"

int searchconnectfd_byto_account(int to_account)       //给服务器用：通过发送对象账号查找connectfd 私聊发给谁    
{
    user* p = head;
    while (p->next != NULL)
    {
        if (p->next->account == to_account)
        {
            return p->next->connectfd;
        }
        p = p->next;
    }
    return 0;
}

