#include "../client_h/liaotianshi_client.h"

void updatepassword(int connectfd)     
{
    msg *a=(msg*)malloc(sizeof(msg));        //这里我也不知道为什么要开空间，不开空间段错误
    int account;          //账号
    char password[20] ;   //旧密码
    char newpw[20] ;      //以及新密码
    char newpw1[20] ;     //第二次确认密码
    printf("请输入你要修改密码的账号:\n");
    scanf("%d",&account);
    printf("请输入旧密码:\n");
    scanf(" %s",password);
    printf("请输入新密码:\n");
    scanf(" %s",newpw);
    printf("请二次输入新密码:\n");
    scanf(" %s",newpw1);
    if(strcmp(newpw,newpw1)==0)
    {
        printf("两次输入密码一致,密码可用\n");
    }
    else
    {
        printf("两次输入密码不一致,密码不可用!\n");           //两次新密码不一样就把name改error发服务器
        strcpy(a->name,"error"); 
        int ret=send(connectfd, a, sizeof(msg),0); 
        if(ret<0)
        {
            perror("recvfrom error111!\n");
            exit(1);
        }  
        return ;    
    }

    a->account=account;
    strcpy(a->msg,password); 
    strcpy(a->name,newpw);
    int ret=send(connectfd, a, sizeof(msg),0); 
    if(ret<0)
    {
        perror("send error!\n");
        exit(1);
    }  

    ret=recv(connectfd, a, sizeof(msg),0); 
    if(ret<0)
    {
        perror("recv error!\n");
        exit(1);
    }  

    if(strcmp(a->msg,"right")==0)
    {
        printf("密码修改成功!\n");                              
        printf("温馨提示:请记好你的账号 %d 的新密码:%s\n",a->account,a->name); 
    }
    else if(strcmp(a->msg,"error")==0)
    {
        printf("旧密码输入不正确,修改密码失败!\n"); 
    }
    return ;
}