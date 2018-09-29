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

main(int argc,char *argv[]){
	FILE *fp;
	fd_set set;
	int arxeio,nwrite,n;
	char operationsname[20],consoletocoord[20],coordtoconsole[20],buffer[MSGSIZE+1];
	char letter;
	int letters;
	if(argc!=5 && argc!=7){
		printf("Dose swsta orismata stin grammi entolon tou jms_console\n");
		exit(1);
	}
	if(argc==5)
		arxeio=0;
	if(argc==7){
		arxeio=1;
		strcpy(operationsname,argv[6]);
	}
	strcpy(consoletocoord,argv[2]);
	strcpy(coordtoconsole,argv[4]);
	if((confd1=open(consoletocoord,O_WRONLY|O_NONBLOCK))<0){		///anoigo to jms-in gia grapsimo
		perror("console to coord write open error");
		exit(1);
	}
	if((confd2=open(coordtoconsole,O_RDONLY))<0){		///anoigo to jms-out gia diavasma
		perror("console to coord write open error");
		exit(1);
	}
	if (arxeio == 1) { 						//an uparxei eksoteriko arxeio operations
		fp = fopen(operationsname, "r");
	} else
		fp = stdin;
	while(!feof(fp)){
		for(letters=0; letters<MSGSIZE; letters++){
			fscanf(fp, "%c",&letter);
			buffer[letters]=letter;
			if(letter=='\n'){
				buffer[letters+1]='\0';
				break; 		//telos entolis
			}
		}
		if((nwrite=write(confd1,buffer,letters))==-1){
			 	perror("console to coord error in Writing");
			 	exit(2); 
			}
		printf("Egrapsa %s\n",buffer);
		fflush(stdout);
		FD_ZERO(&set);
    		FD_SET(confd2, &set);
		for(;;){
			n = select(confd2+1, &set, NULL, NULL, NULL);
			if (!n)
            			continue;
			if (n == -1) {
            			perror("select");
            			return;
        		}
			if (FD_ISSET(confd2, &set)){
				for(letters=0; letters<MSGSIZE; letters++){
						printf("GEIA\n");
						if(read(confd2,&letter,1)<0){
							perror("problem in reading jms_coord");
							exit(5);
						}
						buffer[letters]=letter;
						if(letter=='\n'){
							buffer[letters+1]='\0';
							break; 		//telos entolis
						}
				}
					printf("APANTISI: %s", buffer);
					break;
			}
		}
	}			
	exit(0);
}
