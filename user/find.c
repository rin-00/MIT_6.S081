#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

char* fmtname(char *path)
{//将路径名转换为文件名 
	static char buf[DIRSIZ+1];
	char *p;
	for(p=path+strlen(path);p >= path && *p!='/';p--)
		;
	p++;
	memmove(buf, p, strlen(p));

	return buf;
}

void find(char *path,char *filename)
{//参考ls.c 
	char buf[512], *p;
	int fd;
	struct dirent de;
	struct stat st;
	
	if((fd = open(path, 0)) < 0)
	{
    	fprintf(2, "find: cannot open %s\n", path);
    	return;
    }
    if(fstat(fd, &st) < 0)
    {
    	fprintf(2, "find: cannot stat %s\n", path);
   		close(fd);
    	return;
    }
    
	switch(st.type)
	{
		case T_FILE:
			if(strcmp(fmtname(path),filename)== 0)
			{			  
	    		printf("%s\n",path);    		
			}
			break;
  		case T_DIR:
		    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
			{
		    	printf("find: path too long\n");
		    	break;
	    	}
	    	strcpy(buf, path);
		    p = buf+strlen(buf);
		    *p++ = '/';
		    while(read(fd, &de, sizeof(de)) == sizeof(de))
			{//遍历文件 
			    if(de.inum == 0 ||de.inum == 1 ||strcmp(de.name, ".")==0 ||strcmp(de.name, "..")==0)
			    	continue;
			    memmove(p, de.name,strlen(de.name));
			    p[strlen(de.name)] = 0;
			    find(buf,filename);
		    }
		    break;
	}
	close(fd);
}

int main(int argc,char *argv[])
{
	if(argc<2)
	{
		fprintf(2,"find:Please input 2 argurments.");
		exit(1);
	}
	find(argv[1],argv[2]);   //<path>&<filename>
	exit(0);
} 
