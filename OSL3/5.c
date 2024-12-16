/*Sample C program for Lab 3*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
// main
int main(int argc,char *argv[]){
	int fds[2];
	char buff[60];
	int count;
	int i;
	pipe(fds);
	if (fork()==0){
		printf("\nWriter on the upstream end of the pipe -> %d messages \n",argc-1);
		close(fds[0]);
		for(i=1; i<argc; i++){
			write(fds[1], argv[i], strlen(argv[i]));
			write(fds[1], "\n", 2);
		}
		exit(0);
	} else if(fork()==0){
		printf("\nReader on the downstream end of the pipe \n");
		close(fds[1]);
		while((count=read(fds[0],buff,60))>0){
			write(1,buff,count);
		}
		exit(0);
	} else{
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0);
	}
	return 0;
}

