#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"
#define MAX_LEN 100

int main(int argc, char* argv[])
{
	char* command = argv[1];
	char paramv[MAXARG][MAX_LEN];   //max argument 

	char* p[MAXARG];
	while (1)
	{
		int read_result;
		char buf;
		int count = argc - 1;
		int flag = 0;
		int pos = 0; //语句中字符位置 	

		memset(paramv, 0, MAXARG * MAX_LEN); //初始化 
		for (int i = 1; i < argc; i++)
		{//存储指令 
			strcpy(paramv[i - 1], argv[i]);
		}

		while ((read_result = read(0, &buf, 1)) > 0 && buf != '\n')
		{
			if (buf == ' ' && flag == 1)
			{//下一条语句，重置标识
				pos = 0;
				flag = 0;
				count++;
			}
			else if (buf != ' ')
			{
				paramv[count][pos++] = buf;
				flag = 1;
			}
		}
		//当读到EOF或\n时，结束
		if (read_result <= 0)
			break;  
		for (int i = 0; i < MAXARG - 1; i++)
			p[i] = paramv[i];
		p[MAXARG - 1] = 0;
		if (fork() == 0)
		{//子进程 
			exec(command, p);
			exit(0);
		}
		else
		{//父进程 
			wait((int*)0); //等待子进程完成 
		}
	}
	exit(0);
}
