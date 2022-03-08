#ifndef _LIAOTIANSHI_SERVER_H_
#define _LIAOTIANSHI_SERVER_H_
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<ctype.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sqlite3.h>

#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

#define SEVERPORT 3000 
#define FAILURE  -1
#define SUCCESS  0

struct sockaddr_in serveraddr,clientaddr;
socklen_t clilen;   
pthread_t id;                                     //这些全局变量解决一下别放在这里？？？？？？？

typedef struct user_t{  //用户信息链表   //从数据库写进来
    int flag;           //用户状态(在线为1) 
    int connectfd;      //临时套接口
    char name[20];      //用户名        //从数据库写进来  
    char password[20];  //密码          //从数据库写进来
    int account;        //账号          //从数据库写进来
    struct user_t *next;
}user;

user * head;         //在头文件定义,在主函数里赋值！就可以解决问题！！！！不能在头文件重复赋值

typedef struct  msg_t{  //信息结构体  
    int msg_mode;       //协议头？告诉服务器要干什么
    int  to_account;    //好友账号
    char name[20];      //好友用户名   暂时不用
    char msg[100];      //消息内容
    int connectfd;      //发送者的套接口
    int  account;       //发送者的账号
}msg;

struct job
{
    void* (*func)(void* arg);
    void* (arg);
    struct job* next;
};

struct threadpool
{
    int thread_num;             //已开启线程的数量
    pthread_t* pthread_ids;     //保存线程池中线程的ID
    struct job* head;           //任务队列的头
    struct job* tail;           //任务队列的尾
    int queue_max_num;          //任务队列的最大个数
    int queue_cur_num;          //任务队列已有多少个任务

    pthread_mutex_t mutex;
    pthread_cond_t queue_empty;       //任务队里为空的条件
    pthread_cond_t queue_not_empty;   //任务队里不为空的条件
    pthread_cond_t queue_not_full;    //任务队里不为满的条件
};

void carryout(char* sql);
int login(user* head, int connectfd);
int register1(int connectfd);
int recv_send(int connectfd);
void updatepassword(int connectfd);
void updatedb(char* password, int account);
void initlink();
void createtable();
void readdb(user* head);
void insertdb(user u);
void insertlink_tail(user *head,user u);
int search_account(int account);
int searchaccount_byconnectfd(int connectfd);
int searchconnectfd_byto_account(int to_account);
user search_password(user* head, user u);
void thread_add_job(struct threadpool* pool, void* (*func)(void*), void* arg);
void thread_destroy(struct threadpool* pool);
struct threadpool* threadpool_init(int thread_num, int queue_max_num);


#endif