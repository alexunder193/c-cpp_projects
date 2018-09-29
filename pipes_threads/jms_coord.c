#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <signal.h>
#include <errno.h>
#include "header.h"
#define MSGSIZE 65



main(int argc,char *argv[]){
	char path[50],buffer[MSGSIZE+1];
	char *fifo1="jms_in";
	char *fifo2="jms_out";
	int letters;
	char letter;
	
	pool_queue = NULL; // adeia oura pool
	total_jobs = 0; //kanena job
	int n;
    	fd_set set;
	if(argc!=5){
		printf("Dose swsta orismata stin grammi entolon tou jms_console\n");
		exit(6);
	}
	strcpy(path,argv[2]);
	maxprocesses=atoi(argv[4]);
		if(mkfifo(fifo1,0666)==-1){			///////dimiourgia named pipe jms-in
		if(errno!=EEXIST){
			perror("jms_in mkfifo:");
			exit(6);
		}
	}	
	if(mkfifo(fifo2,0666)==-1){			///////dimiourgia named pipe jms-out
		if(errno!=EEXIST){
			perror("jms_out mkfifo:");
			exit(7);
		}
	}
	if((coorfd1=open(fifo1,O_RDWR))<0){			///jms_in
		perror ("console to coord read open error");
		exit(3);
	}
	if((coorfd2=open(fifo2,O_RDWR))<0){			///jms_out
		perror ("coord to console read open error");
		exit(3);
	}
	FD_ZERO(&set);
    	FD_SET(coorfd1, &set);
	for(;;){
		n = select(coorfd1+1, &set, NULL, NULL, NULL);
		if (!n)
            		continue;
        	if (n == -1) {
            		perror("select");
            		return;
        	}
		if (FD_ISSET(coorfd1, &set)){
			for(;;){
				printf("AAAAAAAA\n");
				fflush(stdout);
				for(letters=0; letters<MSGSIZE; letters++){
					if (read(coorfd1,&letter,1)<0){
						perror("problem in reading jms_coord");
						exit(5);
					}
					//printf("%c\n",letter);
					buffer[letters]=letter;
					//printf("\nMessage Received:%s\n",buffer);
					if(letter=='\n'){
						buffer[letters+1]='\0';
						break; 		//telos entolis
					}
				}
				printf("message is:%s\n",buffer);
				fflush(stdout);
				if(strncmp(buffer,"submit",6)==0){
					//////submit/////
					submit_coord(buffer);
		
				}
				/*else if(){
					///////oi upoloipes entoles
				}*/
			}
		}
	}
}
