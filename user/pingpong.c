#include "kernel/types.h"
#include "user/user.h"

#define READ 0
#define WRITE 1

int main(int argc,char *argv[])
{
	int p1[2];
	int p2[2]; 
	pipe(p1); 
	pipe(p2);    
	
	int pid;
	pid=fork();  
	
	char buf[1];  
	
	if(pid<0)
	{ //子进程生成失败
		exit(1); 
	} 
	else if(pid==0)
	{//子进程
		close(p1[WRITE]);
		close(p2[READ]);   
		read(p1[READ],buf,1); 
		printf("%d:received ping\n",getpid());
		write(p2[WRITE],"q",1);
		close(p1[READ]);
		close(p2[WRITE]); 
		exit(0); 
	} 
	else
	{//父进程 
		close(p1[READ]);
		close(p2[WRITE]);  
		write(p1[WRITE],"p",1);  
		read(p2[READ],buf,1);  
		printf("%d:received pong\n",getpid()); 
		close(p1[WRITE]);
		close(p2[READ]);  
		exit(0);		  	
	}
}

