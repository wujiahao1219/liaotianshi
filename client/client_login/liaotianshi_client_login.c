#include "../client_h/liaotianshi_client.h"

int login(int connectfd)   //这里原来加了个循环搞的客户端收回服务器的处理后信息包，一下收的到一下收不到。
{
    printf("准备进行登录!\n");
    user u;
    printf("请输入你的账号\n");
    scanf("%d", &u.account);
    printf("请输入你的密码(显示隐藏):\n");
    system("stty -echo");
    scanf("%s", u.password);
    system("stty echo");
    send(connectfd, &u, sizeof(u),0);

    memset(&u,0,sizeof(user));
    u.account=0;                                //这里请不清空用户信息包是不是没关系？？？？？

    recv(connectfd, &u, sizeof(u),0);           //从服务器那拿处理好的信息包回来看看
    if (strcmp(u.name, "error") == 0 ) 
    {
        printf("登录失败,服务器显示账号未注册!\n");
        return FAILURE;
    }
    else if(strcmp(u.password, "error") == 0)
    {
        printf("登录失败,服务器显示账号密码不匹配!\n");
        return FAILURE;
    }
    else
    {
        printf("登录成功!\n");
        return SUCCESS;
    }
}