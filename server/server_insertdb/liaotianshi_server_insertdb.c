#include "../server_h/liaotianshi_server.h"

void insertdb(user u)
{
    char sql[500];
    sprintf(sql, "insert into liaotianshi(name ,password,account) values('%s','%s',%d);", u.name, u.password, u.account);
    carryout(sql);
}
