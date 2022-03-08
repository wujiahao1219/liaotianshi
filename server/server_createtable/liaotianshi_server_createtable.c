#include "../server_h/liaotianshi_server.h"

void createtable()
{
    sqlite3* db;
	printf("正在进入数据库\n");
	int ret = sqlite3_open("test.db", &db);
	if (ret != SQLITE_OK)
	{
		printf("%s\n", sqlite3_errmsg(db));
	}
	else
	{
		printf("sqlite3 open db successfull\n");
	}
	char* errmsg;
	char sql[1024];
	strcpy(sql, "create table IF NOT EXISTS liaotianshi(name text ,password text,account integer)");
	ret = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
	if (ret != SQLITE_OK)
	{
		printf("%s\n", sqlite3_errmsg(db));
	}
	else
	{
		printf("sqlite3 creat table liaotianshi successfull\n");
	}

    ret=sqlite3_close(db);
    if (ret != SQLITE_OK)
	{
		perror("sqlite close error!\n");
	}
	else
	{
		printf("sqlite3 close successfull!\n");
	}
    return;
}