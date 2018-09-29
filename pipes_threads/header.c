#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <signal.h>
#include <errno.h>
#define MSGSIZE 65

dpool create_pool_queue(){
		pool_queue=malloc(sizeof(pool));
    	if(pool_queue==NULL){
	  		printf("Sorry cannot allocate memory\n");
	  		return NULL;
   		}

		pool_queue->pid = 0;
   		pool_queue->num_of_pool=1;
   		pool_queue->num_of_jobs=0;
   		pool_queue->jobs=malloc(maxprocesses*sizeof(job));
   		if(pool_queue->jobs==NULL){
	  		printf("Sorry cannot allocate memory\n");
	  		return NULL;
   		}
   		pool_queue->next=NULL;
   		return pool_queue;
}

dpool find_pool_with_space(){
	dpool temp = pool_queue;
	dpool temp2;
	while(temp->next!=NULL)
		temp=temp->next;
	if(temp->num_of_jobs==maxprocesses){
		///////ftiaxno kainourgio pool///////
		temp2=malloc(sizeof(struct pool));
    	if(temp2==NULL){
	  		printf("Sorry cannot allocate memory\n");
	  		return NULL;
   		}
   		temp->next = temp2;
   		temp2->pid = 0;
   		temp2->num_of_pool=temp->num_of_pool+1;
   		temp2->num_of_jobs=0;
   		temp2->jobs=malloc(maxprocesses*sizeof(job));
   		if(temp2->jobs==NULL){
	  		printf("Sorry cannot allocate memory\n");
	  		return NULL;
   		}
   		temp2->next=NULL;
   		temp = temp2;
	}
	return temp;
}

void submit_coord(char* buffer){
	int nwrite, pfd1, pfd2,i, letters;
	char letter;
	pid_t job_pid;
	int job_id;
	dpool temp,temp2;
	char fifo1[20];
	char fifo2[20];
	char number[10], processes[10];
	strcpy(fifo1,"coordtopool");
	strcpy(fifo2,"pooltocoord");
	
	if(pool_queue==NULL)
		temp = create_pool_queue();
	else
		temp=find_pool_with_space();
	
		   		/*
		char namedpipe1[25];  	//onoma named pipe
	char namedpipe2[25];  	//onoma named pipe
	pid_t pid;
		   */
	
	sprintf(number,"%d",temp->num_of_pool);
	//itoa(temp->num_of_pool,number,10);
	printf("FAE BAM\n");
	if(temp->pid == 0) { //neo pool
	
   		strcat(fifo1,number);
		strcat(fifo2,number);
		strcpy(temp->namedpipe1,fifo1);
		strcpy(temp->namedpipe2,fifo2);
 		if(mkfifo(fifo1,0666)==-1){			///////dimiourgia named pipe coord to pool
				if(errno!=EEXIST){
					perror("coord to pool mkfifo:");
					exit(6);
				}
			}
		if(mkfifo(fifo2,0666)==-1){			///////dimiourgia named pipe pool to coord
				if(errno!=EEXIST){
					perror("pool to coord mkfifo:");
					exit(7);
				}
			}
		if((temp->fd1=open(fifo1,O_RDWR))<0){
				perror("pool gia read open error");
				exit(3);
			}
		if((temp->fd2=open(fifo2,O_RDWR))<0){
				perror("pool gia read open error");
				exit(3);
			}		
		
   		if((temp->pid=fork())==0){

   			///////////paidi/////////////
   			sprintf(processes,"%d",maxprocesses);
   			//itoa(maxprocesses,processes,10);
   			execl("jms_pool","jms_pool", fifo1, fifo2, number,processes,NULL);
			perror("exec error");
			exit(1);

		}
		else if(temp->pid < 0){
			perror("fork error");
			exit(1);
		}
			
		
	} //neo pool
	
	///////enimerono to pool//////
	if((nwrite=write(temp->fd1,buffer,MSGSIZE+1))==-1){  // coord to pool
		perror("pool error in Writing");
		exit(2); 
	}
	
	//pairnw apantisi
	
	for(letters=0; letters<MSGSIZE; letters++){
		if (read(temp->fd2,&letter,1)<0){
				perror("problem in reading jms_coord");
				exit(5);
			}
			buffer[letters]=letter;
			if(letter=='\n'){
				buffer[letters+1]='\0';
				break; 		//telos entolis
			}
	}
	printf("Answer Received:%s\n",buffer);
	fflush(stdout);
	
	job_id = ++total_jobs;
	job_pid = atoi(buffer);
	//JobID: 3, PID: 2324.
	sprintf(buffer, "JobID: %d, PID: %d.\n", job_id, job_pid);
		if((nwrite=write(pfd1,buffer,MSGSIZE+1))==-1){  // coord to console
		perror("pool error in Writing");
		exit(2); 
	}
	
}

char** split_words(char *buffer){
	char *p;
	int total = 0, i;
	char **words;
	// poses
	for (p= strtok(buffer," "); p != NULL; p = strtok(NULL, " "))
	{
	  total++;
	}
	words=malloc((total+1)*sizeof(char*));
	// tis apothikevw
	for (p= strtok(buffer," "), i=0; p != NULL; p = strtok(NULL, " "), i++)
	{
		words[i]=malloc((strlen(p)+1)*sizeof(char));
		strcpy(words[i],p);
	}
	words[total]=NULL;
	return words;
}
