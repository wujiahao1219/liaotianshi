#include "../server_h/liaotianshi_server.h"

void updatedb(char* password, int account)   //这里是把表中对应账号的密码改了
{
    char sql[500];
    sprintf(sql, "update liaotianshi set password= '%s' where account =%d; ", password, account);
    carryout(sql);
}
