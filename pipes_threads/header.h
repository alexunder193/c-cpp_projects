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


typedef struct pool *dpool;
typedef struct job *djob;

typedef struct pool{
	pid_t pid;
	int num_of_pool;
	int num_of_jobs; 		//a8roisma jobs sto pool
	char namedpipe1[25];  	//onoma named pipe
	char namedpipe2[25];  	//onoma named pipe
	int fd1;
	int fd2;
	djob jobs;
	dpool next;
}pool;



typedef struct job{
	pid_t pid;
	int jobid;
	int status;			//0 gia suspended 1 gia active 2 gia finished
	int total_time;		//se seconds
	time_t begin;		//wra enarksis
	time_t stop;		//wra diakopis ;;;
	time_t resume;		//wra epanenarksis
}job;

//global
int total_jobs;
djob job_table; //pool
dpool pool_queue; //coord
int maxprocesses; // coord pool
int num_of_pool; // pool
//coord-console, console-coord, pool-coord
int fd1; // gia diavasma
int fd2;	//gia grapsimo
int confd1,confd2,coorfd1,coorfd2;

dpool create_pool_queue();
dpool find_pool_with_space();
void submit_coord(char* buffer);
char** split_words(char *buffer);
