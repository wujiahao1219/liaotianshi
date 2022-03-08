#include "../client_h/liaotianshi_client.h"

void WriteFile(int connectfd,msg m)
{
    printf("文件接收开始\n");
    msg *a= (msg *)malloc(sizeof(msg));
	FILE *to_fp;
	if((to_fp=fopen("liaotianshi111.txt","w+"))==NULL)   
	{
		perror("fopen fp eror!\n");
		return ;
	}
    char readline[1024];
    strcpy(readline,m.msg);
    printf("文件内容:%s",m.msg);
    fwrite(readline,1,strlen(readline),to_fp);

	while(1)    //服务器一遍遍发一行话到客户端 用readline接a->msg  再把readline写入to_fp
	{             
        memset(a,0,sizeof(msg));
		recv(connectfd, a, sizeof(msg),0);          //查出来了因为没人发信息过来所以卡在这了
        if(strcmp(a->msg,"000")==0)
        {
            break;
        }
        printf("文件内容:%s",a->msg);
        fwrite(a->msg,1,strlen(a->msg),to_fp);
        // fputs(a->msg,to_fp);
	}
	fclose(to_fp);
	to_fp=NULL;
    fwrite("\n",1,1,stdout);                   //加一次换行
	printf("文件接收结束\n");
}