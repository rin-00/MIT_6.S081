#include "kernel/types.h"
#include "user/user.h"

#define READ 0
#define WRITE 1

int main(int argc,char *argv[])
{
	int p1[2];
	int p2[2]; 
	pipe(p1); 
	pipe(p2);    //���������ܵ�
	
	int pid;
	pid=fork();  //�����ӽ���
	
	char buf[1];  //�������ݵĻ�����,��СΪ1�ֽ� 
	
	if(pid<0)
	{ //�ӽ�������ʧ��
		exit(1); 
	} 
	else if(pid==0)
	{//�ӽ���
		close(p1[WRITE]);
		close(p2[READ]);   //�ر�δʹ�õĹܵ� 
		read(p1[READ],buf,1);  //�ӽ��̴�p1�ܵ���
		printf("%d: received ping\n",getpid());
		write(p2[WRITE],"q",1);//�ӽ��̴�p2�ܵ�д
		close(p1[READ]);
		close(p2[WRITE]);  //�ر����йܵ�
		exit(0); 
	} 
	else
	{//������ 
		close(p1[READ]);
		close(p2[WRITE]);  //�ر�δʹ�õĹܵ�
		write(p1[WRITE],"p",1);  //�����̴�p1�ܵ�д
		read(p2[READ],buf,1);   //�����̴�p2�ܵ���
		printf("%d: received pong\n",getpid()); 
		close(p1[WRITE]);
		close(p2[READ]);   //�ر����йܵ� 
		exit(0);		  	
	}
}

