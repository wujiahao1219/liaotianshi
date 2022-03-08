#include "../server_h/liaotianshi_server.h"

void insertlink_tail(user *head,user u);

void readdb(user* head) //把已经注册的用户插入用户链表
{
    printf("开始数据库中用户插入用户链表\n");
    sqlite3* db = NULL;
    int ret = sqlite3_open("test.db", &db); //打开数据库
    //printf("打开数据库\n");
    if (SQLITE_OK != ret)
    {
        perror("sqlite3_open:");
        exit(1);
    }

    const char* sql = "select *from liaotianshi;";
    char* errmsg;
    char** result;
    int row = 0, column = 0;
    ret = sqlite3_get_table(db, sql, &result, &row, &column, &errmsg); //分别为文件描述符，数据库命令，查询结果，行，列，错误信息
    if (SQLITE_OK != ret)
    {
        perror("sqlite3_exec:");
        printf("errmsg:%s\n", errmsg);
        exit(1);
    }
    printf("row(行数=用户数)=%d    column=%d\n", row, column);    //看一下数据库里有几行几列，没内容的话不要导出了,这里是?行3列
    if (row == 0)
    {
        return;
    }
    int i, j;
    int num;
    user u;

    for (i = 1; i <= row; i++)
    {
        for (j = 0; j < column; j++)
        {
            num = i * column + j;          //第一个就是1*3+0 = 3   
            //查询到的信息按一维数组的方式储存，0到2分别为name,password,account,3到5为第一行数据，6到8为第二行数据
            if (j == 0)
            {
                strcpy(u.name, result[num]);
                printf("%s\n", u.name);
            }
            else if (j == 1)
            {
                strcpy(u.password, result[num]);
                printf("%s\n", u.password);

            }
            else if (j == 2)
            {
                // u.account=result[num];
                u.account = atoi(result[num]);    //我之前数据库表 account这一列就是integer，为啥不转换编译报错？？？？？？？？
                printf("%d\n", u.account);
                printf("---------------\n");
            }
        }
        insertlink_tail(head, u);
    }

    while (head->next != NULL)    //遍历一下用户信息链表
    {
        printf("%s %s %d\n", head->next->name, head->next->password, head->next->account);
        head = head->next;
    }

    sqlite3_free_table(result); //释放内存
    ret = sqlite3_close(db); //关闭数据库
    if (SQLITE_OK != ret)
    {
        perror("sqlite3_close:");
        exit(1);
    }
    printf("数据库中用户插入用户链表成功\n");
    return;
}