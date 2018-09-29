#include "functions.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char *argv[]){
	struct hostent *rem;
	struct sockaddr_in server,client;
	char server_address[50],buf[256];
	char *content_servers;
	char **servers;
	int port,length,i,sock,j,nwrite;
	unsigned int serverlen=sizeof(server);
	struct sockaddr *serverptr = (struct sockaddr *) &server;
	if(argc!=7){
		printf("Please give 6 arguments\n");
		exit(1);
	}
	numDevicesDone=0;
	/* Create socket */
	if((sock=socket(AF_INET,SOCK_STREAM,0))<0){
    	perror("socket");
		exit(1);
	}
	strcpy(server_address,argv[2]);
	/* Find server's IP address */
    if((rem=gethostbyname(server_address))==NULL){
    	herror("gethostbyname");
		exit(1);
	}
	port=atoi(argv[4]);
	/* Setup server's IP address and port */
    server.sin_family = AF_INET;        /* Internet domain */
    memcpy(&server.sin_addr, rem->h_addr, rem->h_length);
    server.sin_port = htons(port);
	if (connect(sock, serverptr, sizeof(server)) < 0)
	   perror("connect");
    printf("Connecting to %s port %d\n", argv[2], port);
	length=strlen(argv[6])+1;
	content_servers=malloc(length*sizeof(char));
	if(content_servers==NULL){
		printf("Error in malloc\n");
		exit(2);
	}
	strcpy(content_servers,argv[6]);
	servers=split_words(content_servers);
	i=0;
	while(servers[i] != NULL){
		//printf("%s\n",servers[i]);
		if((nwrite=write(sock,servers[i],strlen(servers[i])))==-1){
			 	perror("console to coord error in Writing");
			 	exit(2); 
		}
		write(sock,"\n",1);
		i++;
	}
	write(sock,"\n",1); //sketo - telos content servers
	//sleep(5);
	//printf("Bytes Transferred:%d\n",bytesTransferred);
	//printf("Files Transferred:%d\n",filesTransferred);
}
