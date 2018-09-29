#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "others.h"
#include "lookfor.h"
#include "graph.h"

int main(int argc,char *argv[]) {
  FILE *fp;
  char entoli[25];                                   //diavazoun entoles apo arxeio
  char entoli1[25];
  char entoli2[25];
  int i,Bucket,j,arxeio,thesiarxeiou,a,b,flag;
  float c;
  dkorifis* Hash;
  arxeio=0;
  flag=0;
  for(j=1; j<=argc-1; j++){
  	if(strcmp(argv[j],"-o")==0){                    //ean uparxei arxeio vrisketai stin thesi +1
  		arxeio=1;
  		thesiarxeiou=j+1;
	  }
	if(strcmp(argv[j],"-b")==0){                     //to hashtableentries einai meta tin entoli -b
		Bucket=atoi(argv[j+1]);
	}
  }
  //Bucket=3;
  Hash=malloc(Bucket*sizeof(dkorifis));
  for(i=0; i<Bucket; i++)                               //pinakas katakermatismou ola ta kelia null
    Hash[i]=NULL;
  if(arxeio==1){                                                 //An uparxei arxeio os input
  	fp=fopen(argv[thesiarxeiou],"r");
  	while(!feof(fp)){
  	    if(flag==0){                                      //xreiazetai gia na diabazei tis entoles create delete pou den ksero akrivi ari8mo orismaton
  		    fscanf(fp,"%s",entoli);
  		    flag=1;
  		}
  		if(strcmp("createnodes",entoli)==0){
  			while(1){
  				fscanf(fp,"%s",entoli);
  				if(entoli[0]>='0' && entoli[0]<='9'){        //an einai ari8mos diladi
  					a=atoi(entoli);
  					createnodes(a,Hash,Bucket);
				  }
				else
				    break;
			  }
			continue;
		}
		else if(strcmp("addtran",entoli)==0){
			fscanf(fp,"%s %s %s",entoli,entoli1,entoli2);
			a=atoi(entoli);
			b=atoi(entoli1);
			c=atof(entoli2);
			addtran(a,b,c,Hash,Bucket);
			flag=0;
			continue;
		}
		else if(strcmp("delnodes",entoli)==0){
			while(1){
  				fscanf(fp,"%s",entoli);
  				if(entoli[0]>='0' && entoli[0]<='9'){
  					a=atoi(entoli);
  					delnodes(a,Hash,Bucket);
				  }
				else
				    break;
			  }
			continue;
		}
		else if(strcmp("deltran",entoli)==0){
			fscanf(fp,"%s %s",entoli,entoli1);
			a=atoi(entoli);
			b=atoi(entoli1);
			deltran(a,b,Hash,Bucket);
			flag=0;
			continue;
		}
		else if(strcmp("lookup",entoli)==0){
			fscanf(fp,"%s %s",entoli,entoli1);
			a=atoi(entoli1);
			lookup(a,Hash,entoli,Bucket);
			flag=0;
			continue;
		}
		else if(strcmp("triangle",entoli)==0){
			fscanf(fp,"%s %s",entoli,entoli1);
			a=atoi(entoli);
			c=atof(entoli1);
			triangle(a,Hash,Bucket,c);
			flag=0;
			continue;
		}
		else if(strcmp("conn",entoli)==0){
			fscanf(fp,"%s %s",entoli,entoli1);
			a=atoi(entoli);
			b=atoi(entoli1);
			conn(a,b,Hash,Bucket);
			flag=0;
			continue;
		}
		else if(strcmp("allcycles",entoli)==0){
			fscanf(fp,"%s",entoli);
			a=atoi(entoli);
			flag=0;
	        continue;
		}
		else if(strcmp("traceflow",entoli)==0){
			fscanf(fp,"%s %s",entoli,entoli1);
			a=atoi(entoli);
			b=atoi(entoli1);
                        traceflow(a,Hash,Bucket,b);
			flag=0;
			continue;
		}
		else if(strcmp("bye",entoli)==0){
			bye(Hash,Bucket);
			flag=0;
			break;
		}
		else if(strcmp("print",entoli)==0){
			print(Hash,Bucket);
			flag=0;
			continue;
		}
		else{
			fscanf(fp,"%s",entoli);
			dump(entoli,Hash,Bucket);
			flag=0;
			continue;
		}
	  }
	  fclose(fp);
  }
  flag=0;                                                           //An den uparxei arxeio dexetai entoles ap to prompt
  while(!feof(stdin)){
  	if(flag==0){
  		    fscanf(stdin,"%s",entoli);
  		    flag=1;
  		}
  	if(strcmp("createnodes",entoli)==0){
  			while(1){
  				fscanf(stdin,"%s",entoli);
  				if(entoli[0]>='0' && entoli[0]<='9'){        //an einai ari8mos diladi
  					a=atoi(entoli);
  					createnodes(a,Hash,Bucket);
				  }
				else
				    break;
			  }
			continue;
		}
		else if(strcmp("addtran",entoli)==0){
			fscanf(stdin,"%s %s %s",entoli,entoli1,entoli2);
			a=atoi(entoli);
			b=atoi(entoli1);
			c=atof(entoli2);
			addtran(a,b,c,Hash,Bucket);
			flag=0;
			continue;
		}
		else if(strcmp("delnodes",entoli)==0){
			while(1){
  				fscanf(stdin,"%s",entoli);
  				if(entoli[0]>='0' && entoli[0]<='9'){
  					a=atoi(entoli);
  					delnodes(a,Hash,Bucket);
				  }
				else
				    break;
			  }
			continue;
		}
		else if(strcmp("deltran",entoli)==0){
			fscanf(stdin,"%s %s",entoli,entoli1);
			a=atoi(entoli);
			b=atoi(entoli1);
			deltran(a,b,Hash,Bucket);
			flag=0;
			continue;
		}
		else if(strcmp("lookup",entoli)==0){
			fscanf(stdin,"%s %s",entoli,entoli1);
			a=atoi(entoli1);
			lookup(a,Hash,entoli,Bucket);
			flag=0;
			continue;
		}
		else if(strcmp("triangle",entoli)==0){
			fscanf(stdin,"%s %s",entoli,entoli1);
			a=atoi(entoli);
			c=atof(entoli1);
			triangle(a,Hash,Bucket,c);
			flag=0;
			continue;
		}
		else if(strcmp("conn",entoli)==0){
			fscanf(stdin,"%s %s",entoli,entoli1);
			a=atoi(entoli);
			b=atoi(entoli1);
			conn(a,b,Hash,Bucket);
			flag=0;
			continue;
		}
		else if(strcmp("allcycles",entoli)==0){
			fscanf(stdin,"%s",entoli);
			a=atoi(entoli);
			flag=0;
	        continue;
		}
		else if(strcmp("traceflow",entoli)==0){
			fscanf(stdin,"%s %s",entoli,entoli1);
			a=atoi(entoli);
			b=atoi(entoli1);
			flag=0;
			continue;
		}
		else if(strcmp("bye",entoli)==0){
			bye(Hash,Bucket);
			flag=0;
			break;
		}
		else if(strcmp("print",entoli)==0){
			print(Hash,Bucket);
			flag=0;
			continue;
		}
		else{
			fscanf(stdin,"%s",entoli);
			dump(entoli,Hash,Bucket);
			flag=0;
			continue;
		}
  }
  free(Hash);
  return 0;
}
