#include "../server_h/liaotianshi_server.h"

int recv_send(int connectfd)   
{
    int n;          //登录上把flag=1加到链表里
    msg *m=(msg*)malloc(sizeof(msg));         //这里在正式版本必须开空间不然编译运行之后登录段错误？？？？？？？？？？？
    while(1)   
    {
        memset(m,0,sizeof(msg));
        n=recv(connectfd,m,sizeof(msg),0);
        if(n==0)
        {
            printf("client is off! client connectfd:%d\n",connectfd);
            pthread_exit(NULL);               //这里只需要让服务器对应客户端的那个线程回收就行，并不需要退出服务器exit
        }
        else if(n<0)
        {
            perror("recvfrom error!\n");
            break;
        }
        printf("------------------------------\n");
        printf("请求服务器操作:%d\n",m->msg_mode);        //客户端写入发来
        printf("发送对象账号:%d\n",m->to_account);       //客户端写入发来
        printf("发送对象姓名:%s\n",m->name);            //客户端写入发来但暂时不用
        printf("发送的话:%s\n",m->msg);               //客户端写入发来
        printf("发送者套接字:%d\n",m->connectfd);     //套接口服务器这边自己有
        printf("发送者账号:%d\n",m->account);         //这个是在服务器加上的,如果是私聊还要查发送对象的connectfd
        printf("------------------------------\n");

        while(1)
        {
            if(m->msg_mode==1)         
            {
                m->account=searchaccount_byconnectfd(connectfd);         //7禁言对象不许用该功能
                user *p=head;
                while(p->next->account!=m->account)
                {
                    p=p->next;
                }   
                if(p->next->flag==2)
                {
                    printf("账号:%d已被禁言!\n",m->account);
                    strcpy(m->msg,"error");
                    send(connectfd,m,sizeof(msg),0);
                    break;
                } 

                p=head;
                while(p->next!=NULL)
                {
                    if(p->next->connectfd!=0 && p->next->connectfd!=connectfd)   //看用户链表里，在线的人会有套接口,这里以后改一下不要看谁有套接口而是看谁flag=1！！！！！！！！！！！！！！！！！！！！！！！！！
                    {
                        int to_cfd=p->next->connectfd; 
                        m->to_account=p->next->account;
                        send(to_cfd,m,sizeof(msg),0);
                        printf("账号:%d   向to_cfd:%d账号:%d 发送了群聊信息\n",m->account,to_cfd,m->to_account);
                    }
                    p=p->next;
                }
                break;
            }
            else if(m->msg_mode==2)
            {
                m->account=searchaccount_byconnectfd(connectfd);             //7禁言对象不许用该功能
                user *p=head;
                while(p->next->account!=m->account)
                {
                    p=p->next;
                }   
                if(p->next->flag==2)
                {
                    printf("账号:%d已被禁言!\n",m->account);
                    strcpy(m->msg,"error");
                    send(connectfd,m,sizeof(msg),0);
                    break;
                } 

                int to_cfd=searchconnectfd_byto_account(m->to_account); 
                m->account=searchaccount_byconnectfd(connectfd);
                printf("账号:%d   向to_cfd:%d账号:%d 发送了私聊信息\n",m->account,to_cfd,m->to_account);
                if(send(to_cfd,m,n,0)<0)
                {
                    perror("send error!\n");
                    break;
                }
                break;
            }
            else if(m->msg_mode==3)             ///////////////
            {
                user*p=head;
                while(p->next!=NULL)
                {
                    if(p->next->account==m->account)
                    {
                        printf("%d\n",p->next->flag);
                        if(p->next->flag==10)
                        {
                            printf("账号%d已经是VIP管理员,无需开通!\n",p->next->account);
                            m->msg_mode=3;
                            send(connectfd,m,sizeof(msg),0);
                            break;
                        }
                        else
                        {
                            p->next->flag=10;
                            printf("正在为账号%d开通VIP管理员!\n",p->next->account);
                            m->msg_mode=3;
                            strcpy(m->name,"new");
                            send(connectfd,m,sizeof(msg),0);
                            break;
                        }
                    }
                    p=p->next;
                }
                break;
            }
            else if(m->msg_mode==4)   
            {  
                updatepassword(connectfd);
                return 0;
            }
            else if(m->msg_mode==5)   
            {  
                int to_cfd=searchconnectfd_byto_account(m->to_account) ;
                // recv_sendfile(connectfd,to_cfd,m); 
                if(send(to_cfd,m,n,0)<0)
                {
                    perror("send error!\n");
                    break;
                }                                   //这里的循环所有选项都一样，加return0会回firstmenu，加break还在第二菜单,不加不行首先动了客户端也会动其次会死循环
                break;
            }
            else if(m->msg_mode==6)     //查找在线好友
            {  
                user*p=head;
                while(p->next!=NULL)
                {
                    if(p->next->connectfd!=0)          //这里的判断条件不确定是不是这个
                    {
                        m->account=p->next->account;
                        strcpy(m->name,p->next->name);
                        if(send(connectfd,m,n,0)<0)
                        {
                            perror("send error!\n");
                            break;
                        }
                    }
                    p=p->next;
                }
                break;
            }
            else if(m->msg_mode==71 ||m->msg_mode==72 ||m->msg_mode==73)   ///////////////
            {
                user*p=head;
                while(p->next!=NULL)
                {
                    if(p->next->connectfd==connectfd)       //判断发送者是不是管理员
                    {
                        if(p->next->flag==10)
                        {
                            printf("账号%d是VIP管理员,允许操作\n",p->next->account);
                            strcpy(m->name,"vip");
                        }
                        else
                        {
                            printf("账号%d不是VIP管理员,禁止操作\n",p->next->account);
                            strcpy(m->name,"notvip");
                        }
                    }
                    p=p->next;
                }
                p=head;
                while(p->next!=NULL)
                {
                    if(p->next->account==m->to_account)     //判断被操作者是不是管理员
                    {
                        if(p->next->flag==10)
                        {
                            printf("账号%d是VIP管理员,不允许被操作\n",p->next->account);
                            if(strcmp(m->name,"notvip")!=0)
                            {
                                strcpy(m->name,"twovip");
                            }
                        }
                        else
                        {
                            printf("账号%d不是VIP管理员,可以被操作\n",p->next->account);
                        }
                    }
                    p=p->next;
                }

                if(strcmp(m->name,"notvip")==0 || strcmp(m->name,"twovip")==0 )
                {
                    m->msg_mode=7;
                    send(connectfd,m,sizeof(msg),0);                   //告知操作者能不能进行
                    break;                      //不确定????????????????????这里是想不能进行服务器就可以退出服务了
                }
                
                int to_cfd=searchconnectfd_byto_account(m->to_account);

                if(m->msg_mode==71)
                {
                    p=head;
                    while(p->next!=NULL)
                    {
                        if(p->next->account==m->to_account)
                        {
                            p->next->flag=2;                         //0不在线 1在线 2禁言
                            printf("已经把%d禁言",p->next->account);
                        }
                        p=p->next;
                    }
                }
                else if(m->msg_mode==72)
                {
                    printf("踢人操作完成\n");
                }
                else if(m->msg_mode==73)
                {
                    p=head;
                    while(p->next!=NULL)
                    {
                        if(p->next->account==m->to_account)
                        {
                            p->next->flag=1;                         //0不在线 1在线 2禁言
                            printf("已经把%d解除禁言\n",p->next->account);
                        }
                        p=p->next;
                    }
                }
                send(to_cfd,m,sizeof(msg),0);     //告知被操作者
                if(strcmp(m->name,"vip")==0)
                {
                    m->msg_mode=7;
                    send(connectfd,m,sizeof(msg),0);                //告知操作者进行成功并结束
                }
                break;
            }
            else if(m->msg_mode==8)     //退出
            {  
                return 0;
            }
            else
            {
                printf("服务器没有该功能选项！\n");
                break;
            }
        }
    }
    return 0;
}