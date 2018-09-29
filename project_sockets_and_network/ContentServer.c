#include "functions.h"


void listdir(const char *name, int level,int sock){
	int j,nwrite;
    DIR *dir;
    struct dirent *entry;
    char path[1024];
    char dirpath[1024];
	char reallypath[50];
	struct stat statbuf;
	
    if (!(dir = opendir(name))){
		stat(name, &statbuf);
		if ( ( statbuf.st_mode & S_IFMT ) == S_IFREG ) {
			printf("this is a FILE .\n");
			if((nwrite=write(sock,name,strlen(name)))==-1){
			 	perror("console to coord error in Writing");
			 	exit(2); 
			}
			write(sock,"\n",1);
		}
		else{
         	write(sock,".",1);
         	write(sock,"\n",1);
		}
		
        return;
    }
    else
    {
    	// stelnw to dir pou zitise
	 	int len = snprintf(dirpath, sizeof(dirpath)-1, "%s/", name);
       	dirpath[len] = 0;
		if((nwrite=write(sock,dirpath,strlen(dirpath)))==-1){
			 	perror("console to coord error in Writing");
			 	exit(2); 
		}
		write(sock,"\n",1);   
	}
    if (!(entry = readdir(dir)))
        return;
    do {
    	int len = snprintf(path, sizeof(path)-1, "%s/%s", name, entry->d_name);
        path[len] = 0;
        if (entry->d_type == DT_DIR) {
            
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            
            int len = snprintf(dirpath, sizeof(dirpath)-1, "%s/", path);
        	dirpath[len] = 0;       
			if((nwrite=write(sock,dirpath,strlen(dirpath)))==-1){
			 	perror("console to coord error in Writing");
			 	exit(2); 
			}
			write(sock,"\n",1);
			listdir(path,level+1,sock);
        }
        else{
			if((nwrite=write(sock,path,strlen(path)))==-1){
			 	perror("console to coord error in Writing");
			 	exit(2); 
			}
			write(sock,"\n",1);
		}
    } while (entry = readdir(dir));
    closedir(dir);
}

void *thread_function(void *arg){
	int newsock = *(int*)arg;
	int n,delay,content_server_id,i,j,k, in,count;
	char buf[256];
	char buffer;
	char cid[10];
	char cdelay[10];
	char dirfromfetch[50];
	char* clientname;	
	
    k=0;
    while( 1/*read(newsock,buffer, 1) > 0*/){
    	force_read(newsock,&buffer,1);
    	if(buffer == '\n')
			break;
		buf[k]=buffer;
	    k++;
	}
	buf[k]='\0';
    printf("Received from MirrorManager:%s\n",buf);
    if(strncmp(buf,"LIST",4)==0){			//an exei stalei ston content server entoli List
    	i=5;
    	j=0;
    	while(buf[i] != ' '){
    		cid[j]=buf[i];
    		i++;
    		j++;
		}
		cid[j]='\0';
		j=0;
		i++;
		while(buf[i] != '\0'){
    		cdelay[j]=buf[i];
    		i++;
    		j++;
		}
		cdelay[j]='\0';
		content_server_id=atoi(cid);
		delay=atoi(cdelay);
		pthread_mutex_lock(&lmtx);
		insertFirst(content_server_id, delay);
    	pthread_mutex_unlock(&lmtx);
		listdir(pathname,0,newsock);
    	write(newsock,".",1);
    	write(newsock,"\n",1);
	}
	else {
		if(strncmp(buf,"FETCH",5)==0){
			i=6;
			j=0;
	    	while(buf[i] != ' '){
	    		cid[j]=buf[i];
	    		i++;
	    		j++;
			}
			cid[j]='\0';
			j=0;
			i++;
			while(buf[i] != '\0'){
	    		dirfromfetch[j]=buf[i];
	    		i++;
	    		j++;
			}
			dirfromfetch[j]='\0';
			content_server_id=atoi(cid);
			pthread_mutex_lock(&lmtx);
			delay = find(content_server_id);
			pthread_mutex_unlock(&lmtx);
			
			//stelnw to arxeio pou zitise
			usleep(delay*1000000);
			in = open(dirfromfetch, O_RDONLY);
			while ((count = read(in, buf, sizeof(buf))) > 0) //diavazei apo to arxeio
			{
			    write(newsock, buf, count); //grafei sto newsock
			}
			if (count < 0)
			{
			    perror("send failed");
			}
			close(in);
			
			
		}else{
			printf("lathos entoli. dexomai mono LIST h FETCH\n");
			
		}
	}
	close(newsock);
	pthread_exit(NULL);
}

void main(int argc, char *argv[]){
	int port,sock,newsock;
	socklen_t serverlen,clientlen;
	struct sockaddr_in server, client;
    struct sockaddr *serverptr = (struct sockaddr*) &server;
    struct sockaddr *clientptr = (struct sockaddr*) &client;
    struct hostent *rem;
    pthread_t t;
    lhead = NULL;
	if(argc!=5){
		printf("Please give 5 arguments\n");
		exit(1);
	}
	port=atoi(argv[2]);
	strcpy(pathname,argv[4]);
		/* Create datagram socket */
    if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
        perror_exit("socket");
    server.sin_family = AF_INET;       /* Internet domain */
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);      /*select a port */
    serverlen = sizeof(server);
    clientlen=sizeof(client);
    if(bind(sock,serverptr,serverlen)<0)
        perror_exit("bind");
    if (listen(sock, 5) < 0) perror_exit("listen");
    printf("Listening for connections to port %d\n", port);
    while(1){
        if ((newsock = accept(sock, clientptr, &clientlen)) < 0) perror_exit("accept");
        //printf("Accepted connection\n");
        
        pthread_create(&t, NULL, thread_function, (void*)&newsock);
        pthread_detach(t);
	}
}


