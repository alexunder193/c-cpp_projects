#include "header.h"
#include "others.h"

void print(dkorifis *Hash,int Bucket){
	dkorifis temp;
	dakmis temp1;
	int i,counter;
	counter=0;
	for(i=0; i<Bucket; i++){                   //gia kathe keli tou hashtable
		temp=Hash[i];
		if(temp==NULL){
		   counter++;
		   continue;
	    }
		while(temp!=NULL){                     //gia kathe logariasmo
		printf("vertex(%d)=",temp->salary);
		temp1=temp->list;
		temp=temp->next;
		if(temp1==NULL){
			printf("0K\n");
			continue;
		}
		while(temp1!=NULL){                        //gia kathe akmi
			printf("(%d,%f),",(temp1->list)->salary,temp1->weight);
			temp1=temp1->next;
		}
		printf("\n");
	    }
	}
	if(counter==Bucket)
	  printf("O grafos einai kenos\n");
}



void bye(dkorifis *Hash,int Bucket){
	dkorifis temp;
	dakmis temp1;
	int i;
	for(i=0; i<Bucket; i++){                 //gia kathe keli tou hashtable
		if(Hash[i]==NULL)
		   continue;
		temp=Hash[i];
		while(temp!=NULL){                         //gia kathe logariasmo
			temp1=temp->list;
			if(temp1==NULL){
				Hash[i]=temp->next;
				free(temp);          //diagrafi arxi
				temp=Hash[i];
				continue;
			}
			while(temp1!=NULL){                    //gia kathe akmi
				temp->list=temp1->next;
				free(temp1);           //diagrafi arxi
				temp1=temp->list;
			}
			Hash[i]=temp->next;
			free(temp);
			temp=Hash[i];
		}
	}
//	free(Hash);
	printf("Success: Cleaned memory\n");
}



void dump(char* filename,dkorifis* Hash,int Bucket){
	FILE *fp;
	dkorifis temp;
	dakmis temp1;
	int i;
	fp=fopen(filename,"w");
	fprintf(fp,"createnodes ");           //grapse createnodes sto arxeio 
	for(i=0; i<Bucket; i++){
		temp=Hash[i];
		while(temp!=NULL){
			fprintf(fp,"%d ",temp->salary);       //create tin entoli n1,n2,....
			temp=temp->next;
		}
	}
	fprintf(fp,"\n");
	for(i=0; i<Bucket; i++){
		temp=Hash[i];
		while(temp!=NULL){
			temp1=temp->list;
			while(temp1!=NULL){
				fprintf(fp,"addtran %d %d %f",temp->salary,(temp1->list)->salary,temp1->weight);       //grapse add tran n1 n2 amount
				fprintf(fp,"\n");
				temp1=temp1->next;
			}
		    temp=temp->next;
		}
	}
	printf("Success dumped to %s\n",filename);
	fclose(fp);
}
