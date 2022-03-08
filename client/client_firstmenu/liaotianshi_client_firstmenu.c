#include "../client_h/liaotianshi_client.h"

int register1(int connectfd);
int login(int connectfd) ;
void send1(int connectfd);
void updatepassword(int connectfd);


void firstmenu(int connectfd)
{

    while (1)
    {
        int k;
        printf("\t\t❤ ❤ ❤ ❤ ❤ ❤ ❤ ❤ ❤ ❤ 欢迎进入日天聊天室! ❤ ❤ ❤ ❤ ❤ ❤ ❤ ❤ ❤ ❤ ❤\n");
        printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n");
        sleep(1);
	    printf("\t\t※※※   正在加载中      ****************     ************** ※※※\n");
	    sleep(1);
	    printf("\t\t※※※  **************      正在加载中        ************** ※※※\n");
	    sleep(1);
	    printf("\t\t※※※  **************   ****************       正在加载中   ※※※\n");
        sleep(1.5);
        printf("\t\t※※※\t\t1.注册账号            2.登录账号\t  ※※※\n");
        printf("\t\t※※※\t\t3.修改密码            4.退出\t\t  ※※※\n");
        printf("\t\t※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n");
        
        printf("请选择您要进行的操作:\n");
        scanf("%d", &k);
        
        send(connectfd,&k,sizeof(k),0);
        if (k == 1)
        {
            register1(connectfd);
        }
        else if (k == 2)
        {
            int ret=login(connectfd);
            if(ret==SUCCESS)
            {
                send1(connectfd);
            }
        }
        else if(k == 3)    
        {
            updatepassword(connectfd);
        }
        else if(k==4)
        {
            exit(1);
        }
        else
        {
            printf("input chioce error! input again!\n");
            system("read -p 'Press Enter to continue...' var");    
        }
    }
}