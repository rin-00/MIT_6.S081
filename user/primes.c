#include "kernel/types.h"
#include "user/user.h"

#define READ 0
#define WRITE 1
#define NUM 35

void func(int *p1)
{
	int num;  //存储从管道读出的数 
	 
	close(p1[WRITE]);
	if(0 == read(p1[READ],&num,sizeof(int)))
	{//读管道中的数，当所有数读完后返回0 
		close(p1[READ]);
		exit(0);
	}
	
	int p2[2];  	
	pipe(p2);   //子管道 
	int prime=num; //子进程第一个数为素数
	printf("prime %d\n",prime); 
	 
	if(fork()==0)
	{//子进程递归 
		func(p2); 
	}
	else
	{
		close(p2[READ]);
		while((read((p1[READ]),&num,sizeof(int)))>0)
		{
			if(num%prime!=0) 
			{//筛选素数写入子管道 
				write(p2[WRITE],&num,sizeof(int)); 
			}		
		} 
		close(p2[WRITE]);
		wait((int*)0); //等待所有子进程完成 
	}	
	exit(0);
}

int main(int argc,char *argv[])
{
	int p[2];
	pipe(p);   //管道用于传输数字
	
	if(fork()==0)
	{//子进程递归 
		func(p);  //递归 
	} 
	else
	{//父进程将所有数据写入管道 
		close(p[READ]);
		for(int i=2;i<=NUM;i++)
		{//将2-35数字写入管道 
			write(p[WRITE],&i,sizeof(int));
		}
		close(p[WRITE]);
		wait((int*)0);   //等待所有子进程递归完成 
	} 
	exit(0); 
} 
