#include "functions.h"


void *MirrorManager(void *arg){
	struct hostent *rem;
	struct sockaddr_in server,client;
	char buffer[64],buf[100];
	char buffer1[10];
	char dirpath[1024];
	char buffer2;
	char mirror_content_server_path[1024];
	int port,sock,len,i,newsock,j,nwrite;
	unsigned int serverlen=sizeof(server);
	node data;
	struct sockaddr *serverptr = (struct sockaddr *) &server;
	struct connect farg=*(struct connect*)arg;
	if((sock=socket(AF_INET,SOCK_STREAM,0))<0){
    	perror("socket");
		exit(1);
	}
	if((rem=gethostbyname(farg.url))==NULL){
    	herror("gethostbyname");
		exit(1);
	}
	port=farg.port;
	server.sin_family = AF_INET;        /* Internet domain */
    memcpy(&server.sin_addr, rem->h_addr, rem->h_length);
    server.sin_port = htons(port);
	if (connect(sock, serverptr, sizeof(server)) < 0)
	   perror_exit("connect");
    printf("Connecting to %s port %d\n",farg.url,farg.port);
    bytesTransferred=0;
    filesTransferred=0;
	strcpy(buffer,"LIST ");
	sprintf(buffer1,"%d",farg.identity);
	strcat(buffer,buffer1);
	strcat(buffer," ");
	sprintf(buffer1,"%d",farg.delay);
	strcat(buffer,buffer1);
	if((nwrite=write(sock,buffer,strlen(buffer)))==-1){
			 	perror("console to coord error in Writing");
			 	exit(2); 
	}
	write(sock,"\n",1);
	sprintf(mirror_content_server_path, "%s/%s_%d/", mirror_server_path, farg.url, farg.port);
	mkdir(mirror_content_server_path, 0777);
	
	while(1){			  
         j=0;
         while(1){  /* Receive 1 char */
         	force_read(sock,&buffer2,1);
			if(buffer2 == '\n')
				break;
    		buf[j]=buffer2;
    	    j++;
    	}
		buf[j]='\0';
      	printf("MirrorManager received:[%s]\n", buf);
      	if(strcmp(".", buf) == 0 || strlen(buf)==0)
			break;
      		if( strncmp(buf, farg.directory, strlen(farg.directory)) ==0) {
      			if(buf[strlen(buf)-1] == '/') {
				  	// directory
				  	buf[strlen(buf)-1] = '\0';
				  	// afto pou zitisa
				  	if(strcmp(buf, farg.directory) == 0 ){
				  		// prepei na ftiaxw ta dir pou apoteloun to directory  (test_direcory/dir1/dir2)
				  		make_directories(buf, mirror_content_server_path);
					  }
					  else {
						sprintf(dirpath, "%s/%s_%d/%s", mirror_server_path, farg.url, farg.port, buf);
					  	mkdir(dirpath, 0777);
					  	printf("mkdir %s\n",dirpath );
				  	}
				  }
				  else{
				  	// file
      			  		data.contentport = farg.port;
      					data.content_id = farg.identity;
      					strcpy(data.pcurl,farg.url);
      					strcpy(data.path, buf);
      					place(&shared_buffer, data);
      					pthread_cond_signal(&cond_nonempty);
      			  }
      		}
	}
	close(sock);
	pthread_exit(NULL);
}


void *worker(void *arg){
	int sock,nwrite, out, count;
	char dirpath[1024];
	char buffer[64];
	node data;
	char id[50];
	struct sockaddr_in server;
	struct sockaddr *serverptr = (struct sockaddr*)&server;
    struct hostent *rem;
	while (1){
		//diavazw buffer
		obtain(&shared_buffer, &data);
		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    		perror_exit("socket");
    	if ((rem = gethostbyname(data.pcurl)) == NULL) {	
	   		herror("gethostbyname");
			exit(1);
    	}
    	server.sin_family = AF_INET;
    	memcpy(&server.sin_addr, rem->h_addr, rem->h_length);
    	server.sin_port = htons(data.contentport);
    	if (connect(sock, serverptr, sizeof(server)) < 0)
	   		perror_exit("connect");
	   	printf("Connecting to %s port %d\n",data.pcurl,data.contentport);
		strcpy(buffer,"FETCH ");
		sprintf(id, "%d", data.content_id);
		strcat(buffer,id);
		strcat(buffer," ");
		strcat(buffer,data.path);
		//stelnw request gia FETCH arxeiou
		if((nwrite=write(sock,buffer,strlen(buffer)))==-1){
			 	perror("Write error worker");
			 	exit(2); 
		}
		write(sock,"\n",1);
		pthread_mutex_lock(&filesmtx);
		filesTransferred=filesTransferred+1;
		pthread_mutex_unlock(&filesmtx);
		pthread_cond_signal(&cond_nonfull);
		usleep(500000);
		//lamvanw to arxeio pou zitisa
		sprintf(dirpath, "%s/%s_%d/%s", mirror_server_path, data.pcurl, data.contentport, data.path);
		printf("worker will receive %s\n", dirpath);
		out = open(dirpath, O_WRONLY| O_CREAT| O_TRUNC);
		while ((count = read(sock, buffer, sizeof(buffer))) > 0) //diavazei apo to sock
		{
		    write(out, buffer, count); //grafei sto arxeio
		}
		pthread_mutex_lock(&bytesmtx);
		bytesTransferred=bytesTransferred+count;
		pthread_mutex_unlock(&bytesmtx);
		if (count < 0)
		{
		    printf("EOF\n");
		}
		close(out);		
		
	}
	pthread_exit(0);

}


void main(int argc, char *argv[]){
	int port,threadnum,sock,n,i,j,k,newsock;
	pthread_t t1[100],t2;
	struct connect a;
	socklen_t serverlen,clientlen;
	char buf, *clientname,buffer[256];
	char** words;
	struct sockaddr_in server, client;
    struct sockaddr *serverptr = (struct sockaddr*) &server;
    struct sockaddr *clientptr = (struct sockaddr*) &client;
    struct hostent *rem;
	if(argc!=7){
		printf("Please give 6 arguments\n");
		exit(1);
	}
	port=atoi(argv[2]);
	strcpy(mirror_server_path,argv[4]);
	mkdir(mirror_server_path, 0777);
	threadnum=atoi(argv[6]);
	
	initialize(&shared_buffer);
	pthread_mutex_init(&mtx, 0);
	pthread_cond_init(&cond_nonempty, 0);
	pthread_cond_init(&cond_nonfull, 0);

	for(k=0; k<threadnum; k++){
		pthread_create(&t2,NULL,worker,NULL);
		pthread_detach(t2);
	}
	/* Create datagram socket */
    if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
        perror_exit("socket");
    /* Bind socket to address */
    server.sin_family = AF_INET;       /* Internet domain */
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);      /*select a port */
    serverlen = sizeof(server);
    if(bind(sock,serverptr,serverlen)<0)
        perror_exit("bind");
    if (listen(sock, 5) < 0) perror_exit("listen");
    printf("Listening for connections to port %d\n", port);
    i=1;
    while(1){ // neos initiator
    	if ((newsock = accept(sock, clientptr, &clientlen)) < 0) 
			perror_exit("accept");
		managers = 0;
		while(1){ // neos content server
			j=0;
			buffer[0]='\0';
			while(1){  /* Receive 1 char */
				force_read(newsock,&buf,1);
				if(buf == '\n')
					break;
	    		buffer[j]=buf;
	    	    j++;
	    	}
	    	buffer[j]='\0';	
			if(strlen(buffer)==0) //sketo \n
	    		break;
            printf("Received from initiator:%s\n",buffer);
            words=split_words1(buffer);
            strcpy(a.url,words[0]);
            a.port=atoi(words[1]);
            strcpy(a.directory,words[2]);
            a.delay=atoi(words[3]);
            a.identity=i;
            pthread_create(&t1[managers++],NULL,MirrorManager,(void *) &a);
            i++;
		}
		// den exei allo content server
		// perimenei managers
		for(i=0;i<managers;i++)
			pthread_join(t1[i], NULL);
			
		//perimenei alldone
	/*	pthread_mutex_lock(&mtx);
		while (filesfetched!=fileslisted) {
			pthread_cond_wait(&cond_alldone, &mtx); //all done sto mirror server
		}
		pthread_mutex_unlock(&mtx); */
		//stelnei statistics
		
		//close(sock);
	}
}


