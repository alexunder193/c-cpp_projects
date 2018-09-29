#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <signal.h>
#include <errno.h>
#include <sys/socket.h>
#include <ctype.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <limits.h>
#include <dirent.h>
#include <math.h>

#define BUFFER_SIZE 6

//Content Server
struct lnode {
   int content_server_id;
   int delay;
   struct lnode *next;
};

struct lnode *lhead;
pthread_mutex_t lmtx;
pthread_mutex_t bytesmtx;
pthread_mutex_t filesmtx;
pthread_mutex_t numofdevicesmtx;
char pathname[50];

//Mirror Server
struct connect{
	char url[25];
	int port;
	char directory[50]; 
	int delay;
	int identity;
};

typedef struct node{
	char path[70];
	char pcurl[25];
	int content_id;
	int contentport;
}node;


typedef struct {
	node data[BUFFER_SIZE];
	int start;
	int end;
	int count;
} buffer_t;



pthread_mutex_t mtx;
pthread_cond_t cond_nonempty;
pthread_cond_t cond_nonfull;
buffer_t shared_buffer;
int managers; //posous manager exei o mirror server gia afto to request tou initiator
char mirror_server_path[100];
int bytesTransferred;
int filesTransferred;
int numDevicesDone;

void perror_exit(char *message);
char *name_from_address(struct in_addr addr);
void initialize(buffer_t * buffer);
void place(buffer_t * buffer, node data);
void obtain(buffer_t * buffer, node *data);
void make_directories(char *buffer, char *mirror_content_server_path);
char** split_words(char *buffer);
char** split_words1(char *buffer);
void force_read(int,char *,int);

#endif
