#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/kdev_t.h>
#include <wiringPi.h>


#define DEV_PATH "/dev/motortest_dev"

int main(int agrc, char *argv[]){
	int fd = 0;

	if((fd = open(DEV_PATH, O_RDWR | O_NONBLOCK)) < 0){
		perror("open()");
		exit(1);
	}

	printf("open success\n");

	

	return 0;
}
