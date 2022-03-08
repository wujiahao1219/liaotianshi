#ifndef _LIAOTIANSHI_CLIENT_H_
#define _LIAOTIANSHI_CLIENT_H_
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<pthread.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

#define SEVERPORT 3000   //这个地方换1024-和1024+有什么讲究吗？？？？？？？？？？？？
#define FAILURE  -1
#define SUCCESS   0

typedef struct user_t{  //用户信息链表   //从数据库写进来
    int flag;           //用户状态(在线为1) 
    int connectfd;      //临时套接口
    char name[20];      //用户名        //从数据库写进来  
    char password[20];  //密码          //从数据库写进来
    int account;        //账号          //从数据库写进来
    struct user_t *next;
}user;

typedef struct  msg_t{  //信息结构体  
    int msg_mode;       //协议头？告诉服务器要干什么
    int  to_account;    //好友账号
    char name[20];      //好友用户名   暂时不用
    char msg[100];      //消息内容
    int connectfd;      //发送者的套接口
    int  account;       //发送者的账号
}msg;

void WriteFile(int connectfd,msg m);
void updatepassword(int connectfd);
void ReadFile(int connectfd);
void firstmenu(int connectfd);
int login(int connectfd);
int register1(int connectfd);
void send1(int connectfd);

#endif