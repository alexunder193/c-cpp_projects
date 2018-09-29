#include "functions.h"

void perror_exit(char *message){
    perror(message);
    exit(EXIT_FAILURE);
}

char *name_from_address(struct in_addr addr){
    struct hostent *rem; int asize = sizeof(addr.s_addr);
    if((rem = gethostbyaddr(&addr.s_addr, asize, AF_INET)))
        return rem->h_name;  /* reverse lookup success */
    return inet_ntoa(addr); /* fallback to a.b.c.d form */
}

//display the list
void printList() {
   struct lnode *ptr = lhead;
   printf("\n[ ");
	
   //start from the beginning
   while(ptr != NULL) {
      printf("(%d,%d) ",ptr->content_server_id,ptr->delay);
      ptr = ptr->next;
   }
	
   printf(" ]");
}

//insert link at the first location
void insertFirst(int content_server_id, int delay) {
   //create a link
   struct lnode *link = (struct lnode*) malloc(sizeof(struct lnode));
	
   link->content_server_id = content_server_id;
   link->delay = delay;
	
   //point it to old first node
   link->next = lhead;
	
   //point first to new first node
   lhead = link;
}

//is list empty
int isEmpty() {
   return lhead == NULL;
}

int length() {
   int length = 0;
   struct lnode *current;
	
   for(current = lhead; current != NULL; current = current->next) {
      length++;
   }
	
   return length;
}

//find a link with given content_server_id
int find(int content_server_id) {

   //start from the first link
   struct lnode* current = lhead;

   //if list is empty
   if(lhead == NULL) {
      return 0;
   }

   //navigate through list
   while(current->content_server_id != content_server_id) {
	
      //if it is last node
      if(current->next == NULL) {
         return 0;
      } else {
         //go to next link
         current = current->next;
      }
   }      
	
   //if delay found, return the current Link
   return current->delay;
}

void force_read(int fd, char* buffer, int size){
	int ok=read(fd,buffer,size);
	while (ok<0 && errno == EAGAIN){
		sleep(1);
		ok=read(fd,buffer,size);
	}
			
	if(ok<0 && errno != EAGAIN){
		perror ("read error");
		exit(3);
	}
}

void initialize(buffer_t * buffer) {
	buffer->start = 0;
	buffer->end = -1;
	buffer->count = 0;
}

void place(buffer_t * buffer, node data) {
	pthread_mutex_lock(&mtx);
	while (buffer->count >= BUFFER_SIZE) {
		printf(">> Found Buffer Full \n");
		pthread_cond_wait(&cond_nonfull, &mtx);
		}
	buffer->end = (buffer->end + 1) % BUFFER_SIZE;
	buffer->data[buffer->end] = data;
	buffer->count++;
	pthread_mutex_unlock(&mtx);
}



void obtain(buffer_t * buffer, node *data) {
	
	pthread_mutex_lock(&mtx);
	while (buffer->count <= 0) {
		printf(">> Found Buffer Empty \n");
		pthread_cond_wait(&cond_nonempty, &mtx); 
	}
	
	*data = buffer->data[buffer->start];
	buffer->start = (buffer->start + 1) % BUFFER_SIZE;
	buffer->count--;
	pthread_mutex_unlock(&mtx);

}


void make_directories(char *buffer, char *mirror_content_server_path){
	char *p;
	char  tmp[512];
	strcpy(tmp, mirror_content_server_path);
	for( p= strtok(buffer,"/") ; p != NULL ; p = strtok(NULL, "/"))
	{
		strcat(tmp, p);
	   	mkdir(tmp, 0777);
	   	strcat(tmp, "/");
	}
}

char** split_words(char *buffer){
	char *p;
	int total = 0, i;
	char **words;
	char  tmp[512];
	
	// poses
	strcpy(tmp, buffer); // prin peiraxw to buffer ton apothikevw
	for (p= strtok(buffer,","); p != NULL; p = strtok(NULL, ","))
	{
	  total++;
	}
	words=malloc((total+1)*sizeof(char*));
	
	strcpy(buffer, tmp); // peiraxa to buffer kai gia afto ton diavazw apo ekei pou ton eixa kratisei
	// tis apothikevw
	for (p= strtok(buffer,","), i=0; p != NULL; p = strtok(NULL, ","), i++)
	{
		words[i]=malloc((strlen(p)+1)*sizeof(char));
		strcpy(words[i],p);
	}
	words[total]=NULL;
	return words;
}


char** split_words1(char *buffer){
	char *p;
	int total = 0, i;
	char **words;
	char  tmp[512];
	
	// poses
	strcpy(tmp, buffer); // prin peiraxw to buffer ton apothikevw
	for (p= strtok(buffer,":"); p != NULL; p = strtok(NULL, ":"))
	{
	  total++;
	}
	words=malloc((total+1)*sizeof(char*));
	
	strcpy(buffer, tmp); // peiraxa to buffer kai gia afto ton diavazw apo ekei pou ton eixa kratisei
	// tis apothikevw
	for (p= strtok(buffer,":"), i=0; p != NULL; p = strtok(NULL, ":"), i++)
	{
		words[i]=malloc((strlen(p)+1)*sizeof(char));
		strcpy(words[i],p);
	}
	words[total]=NULL;
	return words;
}


