#include "../client_h/liaotianshi_client.h"

void ReadFile(int connectfd)   
{
    printf("开始读取文件\n");
    msg *a= (msg *)malloc(sizeof(msg));
    a->msg_mode=5;   
    a->connectfd=connectfd;
    printf("please input account of your friend | 请输入好友账号\n");                         
    scanf("%d",&a->to_account);       //只要是把这里把对象账号写进去 服务器那边就会死循环，但是我必须要发对象账号过去啊
    printf("正在发送对象账号为%d传输文件\n",a->to_account);

	FILE *fp;
	if((fp=fopen("liaotianshi.txt","r+"))==NULL)
	{
		perror("fopen fp eror!\n");
		return ;
	}
	
    char readline[1024];
    int i=0;  
	while(fgets(readline,sizeof(readline),fp)!=NULL)   //可能是不等于NULL   把fp一行行写到缓冲再写到a->msg一遍遍发到服务器
	{
        strcpy(a->msg,readline);
		send(connectfd, a, sizeof(msg),0);
        i++;
        printf("发送了第%d行文本内容:%s",i,a->msg);   
        memset(readline,0,sizeof(readline));
	}

    strcpy(a->msg,"000");                      //最后手动发一行让接收时知道文件发完了
    send(connectfd, a, sizeof(msg),0);
	fclose(fp);
	fp=NULL;
    printf("文件发送结束\n");
}