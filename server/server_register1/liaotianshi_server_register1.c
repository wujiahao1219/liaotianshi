#include "../server_h/liaotianshi_server.h"
int search_account(int account);
void insertdb(user u);
void insertlink_tail(user* head, user u);


int register1(int connectfd)     //注册生成账号
{
    printf("开始执行注册!\n");
    printf("正在等待接收客户端用户结构体包!\n");
    user u;
    u.flag=0;
    recv(connectfd, &u, sizeof(u), 0);
    while (1)
    {
        srand(time(NULL));
        u.account = rand() % 100000;                 //放个检测函数
        printf("生成用户账号成  功! 账户为%d\n",u.account);
        if (search_account(u.account) == 0)         //查账户重复
        {
            printf("注册阶段返回该账号不重复!\n");
            break;
        }
    }
    printf("检测账号重复操作结束,准备写入链表和数据库,准备发送给客户端用户信息包！\n");
    send(connectfd, &u, sizeof(u), 0);
    insertdb(u);                //写到数据库里   
    insertlink_tail(head, u);    //写到链表里        

    return SUCCESS;
}