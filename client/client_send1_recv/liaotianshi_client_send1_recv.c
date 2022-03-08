#include "../client_h/liaotianshi_client.h"

void *recv_thread(void *arg)
{
    int connectfd= *((int *)arg);
    int ret;
    msg m;
    int i=0;
    while(1)
    {
        // ret=recvfrom(connectfd,&m,sizeof(msg),0,NULL,NULL);     
        ret=recv(connectfd,&m,sizeof(msg),0);     
        if(ret<0)
        {
            perror("recvfrom error!\n");
            exit(1);
        }  

        if (m.msg_mode==1 )         
        {
            if(strcmp(m.msg,"error")==0)
            {
                printf("您已被禁言,不许说话\n");
            }
            else 
            {
                printf("账号为%d对你说: ",m.account);  
                fputs(m.msg,stdout);
                putchar(10);
            // printf("%s",m.msg);
            }  
        }
        else if( m.msg_mode==2)
        {
            if(strcmp(m.msg,"error")==0)
            {
                printf("您已被禁言,不许说话\n");
            }
            else 
            {
                printf("账号%d 悄悄对你说: ",m.account);  
                fputs(m.msg,stdout);
                putchar(10);
                // printf("%s",m.msg);  
            }   
        }
        else if(m.msg_mode==3)
        {
            printf("VIP功能内测中,支付手段暂不支持,赠送您一个月\n");
            if( strcmp(m.name,"new")==0 )
            {
                printf("VIP开通成功!账号%d已经成为尊贵的VIP ❤ !\n",m.account);
            }
            else 
            {
                printf("开通失败❤账号%d早已经是尊贵的VIP了!\n",m.account);
            }
        }
        else if(m.msg_mode==5)
        {
            WriteFile(connectfd,m);        //传的这个m其实是文件的第一行，在这里被截获了
        }                                  //结束别加break;加了接收(读)线程就没了
        else if(m.msg_mode==6)
        {
            i++;
            printf("❤ ❤ ❤ ❤ ❤ 在线好友 %d  ❤ ❤ ❤ ❤ ❤ \n",i);
            printf("好友%s   (账号%d)在线!\n",m.name,m.account);
        }
        else if(m.msg_mode==7)
        {
            if(strcmp(m.name,"notvip")==0)
            {
                printf("不是VIP的你被丢出了管理员小窝!\n");
            }
            else if(strcmp(m.name,"twovip")==0)
            {
                printf("对方也是VIP,和气生财!\n");
            }
            else if(strcmp(m.name,"vip")==0)
            {
                printf("尊敬的VIP您的指令已经下达下去了!\n");
            }
        }
        else if(m.msg_mode==71 ||m.msg_mode==72 ||m.msg_mode==73)
        {
            if(m.msg_mode==71)
            {
                printf("您已被管理员禁言!\n");
            }
            else if(m.msg_mode==72)
            {
                printf("您已经被管理员踢出即时通讯软件!!!\n");
                exit(1);
            }
            else if(m.msg_mode==73)
            {
                printf("您已被管理员禁言解除!\n");
            }
        }   
    }
    pthread_exit(NULL);
}

void send1(int connectfd)  //登录后界面
{   
    char chioce;
    msg msg_text;
    pthread_t tid_send,tid_recv;    
    if(pthread_create(&tid_recv,NULL,recv_thread,(void*)&connectfd)<0)
    {
        perror("pthread_create_recv error!\n");
        exit(1);
    }
    while(1)
    {
        printf("——————————————————————————————————————————————————\n");
        printf("| please make your chioce |请选择要使用的功能    | \n");
        printf("| 1.say to all | 群聊                            |\n");
        printf("| 2.say to one | 私聊                            |\n");
        printf("| 3.become ❤ VIP ❤ | ❤ 成为尊贵的VIP ❤           |\n");
        printf("| 4.change password |修改密码                    |\n");
        printf("| 5.send_recv FILE |发送文件                     |\n");
        printf("| 6.search friends |查找在线好友目录             | \n");
        printf("| 7.VIP's home | ❤ VIP&管理员小窝 ❤              |\n");
        printf("| 8.exit | 退出                                  | \n");
        printf("——————————————————————————————————————————————————\n");

        printf("请输入您想要的功能:\n");
        scanf(" %c",&chioce);           
        if(chioce=='1')
        {
            while(1)
            {
                bzero(&msg_text,sizeof(msg));
                msg_text.msg_mode=1;
                msg_text.connectfd=connectfd;
                printf("please input text! | 请输入发送的消息,88退出群聊\n");
                scanf(" %s",msg_text.msg);     
                // fgets(msg_text.msg,100,stdin);        //咋不能用呢？？？？？？？？？？？？？？？？？？、
                if(send(connectfd,&msg_text,sizeof(msg_text),0)<0)
                {
                    perror("send error!\n");
                    break;
                }
                if(strcmp(msg_text.msg,"88")==0)          //输入88即可离开对话
                {
                    break;
                }
            }
        }
        else if(chioce=='2')
        {
            bzero(&msg_text,sizeof(msg));
            msg_text.msg_mode=2;
            msg_text.connectfd=connectfd;
            printf("please input account of your friend | 请输入好友账号\n");
            scanf("%d",&msg_text.to_account);
            while(1)
            {
                printf("please input text! | 请输入发送的消息,88退出聊天\n");
                // fgets(msg_text.msg,100,stdin);
                scanf(" %s",msg_text.msg);
                if(send(connectfd,&msg_text,sizeof(msg_text),0)<0)
                {
                    perror("send error!\n");
                    break;
                }
                if(strcmp(msg_text.msg,"88")==0)          //输入88即可离开对话
                {
                    break;
                }
            }
        }
        else if(chioce=='3')            ///////////////
        {
            msg_text.msg_mode=3;
            msg_text.connectfd=connectfd;
            printf("请输入你想充值成为VIP管理员用户的账号:\n");   
            scanf("%d",&msg_text.account);
            send(connectfd,&msg_text,sizeof(msg_text),0);
        }
            
        else if(chioce=='4')      
        {
            msg_text.msg_mode=4;
            send(connectfd,&msg_text,sizeof(msg_text),0);
            updatepassword(connectfd);
            printf("密码修改,把您踢下线\n");
            break;
        }
        else if(chioce=='5')      
        {
            ReadFile(connectfd);      //这一段循环所有选项都一样：如果要回firstmenu就加break，不回而还是在第二菜单就不加
        }
        else if(chioce=='6')          //传输文件
        {
            msg_text.msg_mode=6;
            send(connectfd,&msg_text,sizeof(msg_text),0);
        }
        else if(chioce=='7')            /////////////// 管理员小窝 禁言踢人  进入小窝发现没有权限 有权限发现对方也是管理 
        {
            printf("❤ 正在进入VIP&管理员小窝 ❤:\n");
            printf("1.❤ 禁言他人 ❤ 2.❤ 无情踢出 ❤ 3.❤ 解开禁言 ❤:\n");
            int i;
            scanf("%d",&i);
            printf("请指定目标账号 :(慎用)\n");
            scanf("%d",&msg_text.to_account);
            if(i==1)
            {
                msg_text.msg_mode=71;
                send(connectfd,&msg_text,sizeof(msg_text),0);
            }    
            else if(i==2)
            {
                msg_text.msg_mode=72;
                send(connectfd,&msg_text,sizeof(msg_text),0);
            }
            else if(i==3)
            {
                msg_text.msg_mode=73;
                send(connectfd,&msg_text,sizeof(msg_text),0);
            } 
        }
        else if(chioce=='8')          //退出
        {
            msg_text.msg_mode=8;
            send(connectfd,&msg_text,sizeof(msg_text),0);
            printf("欢迎下次使用\n");
            break;
        }
        else
        {
            printf("input chioce error! input again!\n");
            // system("pause");            //没用,这个查了是windows能用
            // pause();                    //没用
            system("read -p 'Press Enter to continue...' var");    //这里可以回去复习一下system,看一下这三种写法哪个对？？？？？
        }
    }
    return ;
}