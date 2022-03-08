#include "../server_h/liaotianshi_server.h"

void carryout(char* sql)                             //除了创建db和searchtable，后面的都是和carryout一起用
{
    sqlite3* db = NULL;
    int ret = sqlite3_open("test.db", &db);
    if (ret != SQLITE_OK)
    {
        printf("sqlite_open:%s\n", sqlite3_errmsg(db));
        return;
    }
    printf("sqlite_open success!\n");

    char* errmsg;
    ret = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
    if (ret != SQLITE_OK)
    {
        // printf("sqlite_exec:%s\n",sqlite3_errmsg(db));  //换个错误显示写法
        perror("sqlite_exec error!\n");
        return;
    }
    printf("sqlite_exec success!\n");

    ret = sqlite3_close(db);
    if (ret != SQLITE_OK)
    {
        // printf("sqlite_exec:%s\n",sqlite3_errmsg(db));  //换个错误显示写法
        perror("sqlite_close error!\n");
        return;
    }
    printf("sqlite_close success!\n");
}