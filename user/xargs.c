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
		int pos = 0; //������ַ�λ�� 	

		memset(paramv, 0, MAXARG * MAX_LEN); //��ʼ�� 
		for (int i = 1; i < argc; i++)
		{//�洢ָ�� 
			strcpy(paramv[i - 1], argv[i]);
		}

		while ((read_result = read(0, &buf, 1)) > 0 && buf != '\n')
		{
			if (buf == ' ' && flag == 1)
			{//��һ����䣬���ñ�ʶ
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
		//������EOF��\nʱ������
		if (read_result <= 0)
			break;  
		for (int i = 0; i < MAXARG - 1; i++)
			p[i] = paramv[i];
		p[MAXARG - 1] = 0;
		if (fork() == 0)
		{//�ӽ��� 
			exec(command, p);
			exit(0);
		}
		else
		{//������ 
			wait((int*)0); //�ȴ��ӽ������ 
		}
	}
	exit(0);
}
