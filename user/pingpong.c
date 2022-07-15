#include "kernel/types.h"
#include "user/user.h"

#define READ 0
#define WRITE 1

int main(int argc,char *argv[])
{
	int p1[2];
	int p2[2]; 
	pipe(p1); 
	pipe(p2);    //建立两个管道
	
	int pid;
	pid=fork();  //产生子进程
	
	char buf[1];  //传输数据的缓存区,大小为1字节 
	
	if(pid<0)
	{ //子进程生成失败
		exit(1); 
	} 
	else if(pid==0)
	{//子进程
		close(p1[WRITE]);
		close(p2[READ]);   //关闭未使用的管道 
		read(p1[READ],buf,1);  //子进程从p1管道读
		printf("%d: received ping\n",getpid());
		write(p2[WRITE],"q",1);//子进程从p2管道写
		close(p1[READ]);
		close(p2[WRITE]);  //关闭所有管道
		exit(0); 
	} 
	else
	{//父进程 
		close(p1[READ]);
		close(p2[WRITE]);  //关闭未使用的管道
		write(p1[WRITE],"p",1);  //父进程从p1管道写
		read(p2[READ],buf,1);   //父进程从p2管道读
		printf("%d: received pong\n",getpid()); 
		close(p1[WRITE]);
		close(p2[READ]);   //关闭所有管道 
		exit(0);		  	
	}
}

