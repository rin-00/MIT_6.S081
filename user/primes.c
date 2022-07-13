#include "kernel/types.h"
#include "user/user.h"

#define READ 0
#define WRITE 1
#define NUM 35

void func(int *p1)
{
	int num;  //�洢�ӹܵ��������� 
	 
	close(p1[WRITE]);
	if(0 == read(p1[READ],&num,sizeof(int)))
	{//���ܵ��е�����������������󷵻�0 
		close(p1[READ]);
		exit(0);
	}
	
	int p2[2];  	
	pipe(p2);   //�ӹܵ� 
	int prime=num; //�ӽ��̵�һ����Ϊ����
	printf("prime %d\n",prime); 
	 
	if(fork()==0)
	{//�ӽ��̵ݹ� 
		func(p2); 
	}
	else
	{
		close(p2[READ]);
		while((read((p1[READ]),&num,sizeof(int)))>0)
		{
			if(num%prime!=0) 
			{//ɸѡ����д���ӹܵ� 
				write(p2[WRITE],&num,sizeof(int)); 
			}		
		} 
		close(p2[WRITE]);
		wait((int*)0); //�ȴ������ӽ������ 
	}	
	exit(0);
}

int main(int argc,char *argv[])
{
	int p[2];
	pipe(p);   //�ܵ����ڴ�������
	
	if(fork()==0)
	{//�ӽ��̵ݹ� 
		func(p);  //�ݹ� 
	} 
	else
	{//�����̽���������д��ܵ� 
		close(p[READ]);
		for(int i=2;i<=NUM;i++)
		{//��2-35����д��ܵ� 
			write(p[WRITE],&i,sizeof(int));
		}
		close(p[WRITE]);
		wait((int*)0);   //�ȴ������ӽ��̵ݹ���� 
	} 
	exit(0); 
} 
