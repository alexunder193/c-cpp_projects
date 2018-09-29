#include "header.h"
#include "graph.h"

void createnodes(int id, dkorifis* Hash,int Bucket){
	dkorifis temp;
	int r;
	if(id<1000000 || id>9999999){                                    /*Elegxos an einai 7psifios o id*/
		printf("failure:To %d den einai eptapsifios\n",id);
		return;
    }
    r=function(id,Bucket);
	temp=Hash[r];	
    while(temp!=NULL){                                                /*Elegxos an to id uparxei hdh ston grafo*/
    	if(temp->salary==id){
    		printf("failure:O logariasmos %d uparxei hdh\n",id);
    		return;
		}   
		temp=temp->next;
	}      
   temp=malloc(sizeof(struct korifi));                         /*An uparxoun komvoi*/
   if(temp==NULL)
   {
	  printf("Sorry cannot allocate memory\n");
	  return;
   }
   temp->salary=id;
   temp->in = 0.0;
   temp->out = 0.0;
   temp->next=Hash[r];                      //eisagogi ws proto kombo
   temp->list=NULL;                         //arxika o logariasmos den exei akmes
   Hash[r]=temp;                             //to keli tou pinaka kat/mou deixnei ston proto logariasmo tis listas
   printf("Success: Created %d\n",id);
   return;
}




 void addtran(int id1,int id2,float varos,dkorifis *Hash,int Bucket){
 	dkorifis temp,temp1;
 	dakmis temp2;
 	int r1,r2;
 	if(id1==id2){
 		printf("Failure: Akmi metaksu idion logariasmwn den ginetai\n");
 		return;
	 }
	if(varos<0.0){
		printf("Failure: Edoses arnitiko varos\n");
		return;
	}
    r1=function(id1,Bucket);
    temp=Hash[r1];
    if(temp==NULL){
    	printf("Failure: Den uparxei o logariasmos %d gia na mpei akmi\n",id1);
    	return;
	}
    while(temp->salary!=id1){                                                        /*o temp deixnei tin korifi me id1*/
        temp=temp->next;
        if(temp==NULL){
    	    printf("Failure: Den uparxei o logariasmos %d gia na mpei akmi\n",id1);
    	    return;
	   }
   }
   r2=function(id2,Bucket);
   temp1=Hash[r2];
   if(temp1==NULL){
    	printf("Failure: Den uparxei o logariasmos %d gia na mpei akmi\n",id2);
    	return;
	}
    while(temp1->salary!=id2){                                                        /*o temp1 deixnei tin korifi me id2*/
        temp1=temp1->next;
        if(temp1==NULL){
    	    printf("Failure: Den uparxei o logariasmos %d gia na mpei akmi\n",id2);
    	    return;
	   }
   }
   temp2=temp->list;
   while(temp2!=NULL){
   	if(temp2->list==temp1){
   		temp2->weight=temp2->weight+varos;                  //an uparxdei akmi auksano to varos tis
   		temp->out=temp->out+varos;                           //oi ekserxomenes tis temp auksanontai
   		temp1->in=temp1->in+varos;                          //oi eiserxomenes tis temp1 auksanontai
   		printf("Success: H akmi %d->%d upirxe hdh to varos auksithike kata %f\n",id1,id2,varos);
   		return;
	   }
	temp2=temp2->next;   
   }
   if(temp2==NULL){
   	temp2=malloc(sizeof(struct akmi));                   //an den uparxei i sugkekrimeni akmi tis dimiourgo kai tin gemizo
   	if(temp2==NULL){
   		printf("Sorry cannot allocate memory\n");
	    return;
	   }
	temp2->weight=varos;
	temp->out=temp->out+varos;
   	temp1->in=temp1->in+varos;
   	temp2->next=temp->list;
   	temp2->list=temp1;
   	temp->list=temp2;
   	printf("Success: Added transaction %d %d with amount %f\n",id1,id2,varos);
   	return;
   }
}



void deltran(int id1,int id2,dkorifis* Hash,int Bucket){
	dkorifis temp,temp1;
	dakmis temp2,temp3;
	int r1,r2;
	if(id1==id2){
 		printf("failure: Diagrafi akmis metaksu idion logariasmwn den ginetai\n");
 		return;
	 }
	r1=function(id1,Bucket);
    temp=Hash[r1];
    if(temp==NULL){
    	printf("failure: Den uparxei o komvos me %d gia na diagrafei i akmi tou\n",id1);
    	return;
	}
    while(temp->salary!=id1){                                                        /*o temp deixnei tin korifi me id1*/
        temp=temp->next;
        if(temp==NULL){
    	    printf("failure: Den uparxei o komvos me %d gia na diagrafei i akmi tou\n",id1);
    	    return;
	   }
   }
   r2=function(id2,Bucket);
   temp1=Hash[r2];
   if(temp1==NULL){
    	printf("failure: Den uparxei o komvos me %d gia na diagrafei i akmi tou\n",id2);
    	return;
	}
    while(temp1->salary!=id2){                                                        /*o temp1 deixnei tin korifi me id2*/
        temp1=temp1->next;
        if(temp1==NULL){
    	    printf("failure: Den uparxei o komvos me %d gia na diagrafei i akmi tou\n",id2);
    	    return;
	   }
   }
   if(temp->list==NULL){
   	 printf("Failure: Den uparxei akmi metaksu %d kai %d gia na diagrafei\n",id1,id2);
   	 return;
   }
   temp2=temp->list;
   temp3=temp->list;
   while(temp2!=NULL){
   	  if(temp->list==temp2 && temp2->list==temp1){                 //an einai h proti akmi tis listas diagrafi
   	  	  temp->out=temp->out-temp2->weight;
   	  	  temp1->in=temp1->in-temp2->weight;
   	  	  temp->list=temp2->next;
   	  	  free(temp2);
   	  	  printf("Success: Deleted transaction %d %d\n",id1,id2);
   	  	  return;
		 }
	  if(temp2->list==temp1){                                       //an einai opoiadipote alli akmi ektos apo proti diagrafi
	  	temp->out=temp->out-temp2->weight;
   	  	temp1->in=temp1->in-temp2->weight;
   	  	temp3->next=temp2->next;
   	  	free(temp2);
   	  	printf("Success: Deleted transaction %d %d\n",id1,id2);
   	  	return;
	  }
	  temp3=temp2;
	  temp2=temp2->next;
   }
   if(temp2==NULL){
   	  printf("Failure: Oi logariasmoi %d %d den sundeontai me kapoia akmi gia na diagrafei\n",id1,id2);
   	  return;
   }
}




void delnodes(int id1, dkorifis*Hash,int Bucket){
	dkorifis temp,temp1;
	int r;
	r=function(id1,Bucket);
	temp=Hash[r];
	temp1=Hash[r];
	while(temp!=NULL)                        /*o temp deixnei ton komvo pou 8a diagrafei o temp1 krataei ton proigoumeno*/
	{
		if(temp->salary == id1)
			break;
		temp1= temp;
		temp=temp->next;
	}	
	if(temp==NULL)                                      /*An to temp deixnei NULL simainei oti den brike kapoio komvo me id pou thelo na diagrapso*/
	{
		printf("Failure:Den vrethike o logariasmos %d gia na diagrafei\n",id1);
		return;
	}
	
	if(temp->in+temp->out>0.0)                         /*An kapoio apo to a8roisma eiserxomenon h ekserxomenon einai >0 tote uparxei akmi*/
	{
		printf("Failure: Den mporei na diagrafei o logariasmos %d exei akmes\n",id1); 
		return;
	}

	if(Hash[r]==temp)                                            /*diagrafi 1ou*/
		Hash[r]=temp->next;
	else
		temp1->next = temp->next;                                 /*diagrafi allou.o proigoumenos deixnei ston epomeno h null an einai teleutaios*/
	printf("Success: Deleted %d\n",temp->salary);
	free(temp);
}
