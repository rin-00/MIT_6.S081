#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
	if (argc == 1) {
		fprintf(2, "ERROR: sleep time required\n");
		exit(1);
	}   //未传入参数，打印错误信息 
	sleep(atoi(argv[1]));  //将字符串转换为int 
	exit(0);
}
