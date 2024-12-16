/*Sample C program for Lab 3*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc,char *argv[]){
	key_t key = ftok("shared_memory_key",65);
	int shmid = shmget(key, 1024, IPC_CREAT | 0666);
	if (fork()!=0){
		printf("Writer on the upstream end of the pipe\n");
		char *ctrl = (char*) shmat(shmid, 0, 0);
		sprintf(ctrl,"%s\n", argv[1]);
		printf("Writer: %s\n", ctrl);
		shmdt(ctrl);
		exit(0);
	} else {
		printf("\nReader on the downstream end of the pipe \n");
		char *ctrl_consumer = (char*) shmat(shmid, 0, 0);
		while(strlen(ctrl_consumer) == 0){
			sleep(1);
		}
		printf("Consumer: %s\n", ctrl_consumer);
		shmdt(ctrl_consumer);
		exit(0);
	}
	wait(0);
	shmctl(shmid, IPC_RMID, NULL);
	return 0;
}

