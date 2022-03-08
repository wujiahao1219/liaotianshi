#include "../client_h/liaotianshi_client.h"

int register1(int connectfd)
{
    user u;
    printf("请输入您的用户名\n");
    scanf("%s", u.name);
    printf("请输入您的密码(显示隐藏):\n");
    system("stty -echo");
    scanf("%s", u.password);
    system("stty echo");
    printf("正在为您生成用户账号....请耐心等待\n");
    sleep(2);
    send(connectfd, &u, sizeof(u),0);   
    recv(connectfd, &u, sizeof(u),0);
    printf("注册成功!\n");
    printf("这是您的账号:%d,用户名为:%s\n", u.account, u.name);
    printf("温馨提示:请记好密码:%s\n",u.password);
    return 0;
}