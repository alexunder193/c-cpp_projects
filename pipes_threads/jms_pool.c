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
	char namedpipe1[25];
	char namedpipe2[25];
	char buffer[MSGSIZE+1];
	int letters,nwrite;
	char letter;
	char** words;
	pid_t job_pid;
	
	total_jobs = 0; // 0 jobs
	num_of_pool=atoi(argv[3]);
	maxprocesses=atoi(argv[4]);
	strcpy(namedpipe1,argv[1]);
	strcpy(namedpipe2,argv[2]);
	
	job_table = malloc(maxprocesses*sizeof(job)); 
    if(job_table==NULL){
	  		printf("Sorry cannot allocate memory\n");
	  		return;
   	}

	if((fd1=open(namedpipe1,O_RDONLY))<0){		///anoigo to namedpipe1 gia diavasma
		perror("console to coord write open error");
		exit(1);
	}	
	
	if((fd2=open(namedpipe2,O_WRONLY|O_NONBLOCK))<0){		///anoigo to namedpipe2 gia grapsimo
		perror("console to coord write open error");
		exit(1);
	}
	for(;;){
		for(letters=0; letters<MSGSIZE; letters++){
			if (read(fd1,&letter,1)<0){
				perror("problem in reading jms_coord");
				exit(5);
			}
			buffer[letters]=letter;
			if(letter=='\n'){
				buffer[letters+1]='\0';
				break; 		//telos entolis
			}
		}
		printf("\nMessage Received:%s\n",buffer);
		fflush(stdout);
		if(strncmp(buffer,"submit",6)==0){
			//////submit/////
			words=split_words(buffer+7);
			job_pid=fork();
			if(job_pid==0){

   				///////////paidi job/////////////
   				execvp(words[0],words);
				perror("exec error");
				exit(1);
			}
			else if(job_pid < 0){
				perror("fork error");
				exit(1);
			}
		
			// pateras
			total_jobs++;
			job_table[total_jobs-1].pid = job_pid;
			job_table[total_jobs-1].jobid=maxprocesses*(num_of_pool-1)+total_jobs;
			job_table[total_jobs-1].status = 1; //active
			job_table[total_jobs-1].total_time = 0; //twra arxise 
			time ( &job_table[total_jobs-1].begin ); // http://stackoverflow.com/questions/5141960/get-the-current-time-in-c
			
			sprintf(buffer, "%d\n", job_pid);
			
			if(nwrite=write(fd2,buffer,strlen(buffer))==-1){  // pool sends jobpid to coord
				perror("pool error in Writing");
				exit(2); 
			}
		}
		/*else if(){
			///////oi upoloipes entoles
		}*/
	}
	
}
