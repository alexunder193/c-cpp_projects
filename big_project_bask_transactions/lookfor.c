#include "header.h"
#include "lookfor.h"

void lookup(int id,dkorifis *Hash,char* entoli,int Bucket){
	dkorifis temp;
	int r;
	r=function(id,Bucket);
	temp=Hash[r];                                       //o temp deixnei ton logariasmo pou kanei lookup an den uparxei deixnei null sto telos
	if(temp==NULL){
		printf("Failure: O logariasmos %d den uparxei\n",id);
		return;
	}
	while(temp!=NULL){
		if(temp->salary==id){
			if(strcmp("in",entoli)==0){
				printf("Success: in(%d)=%f\n",id,temp->in);
				return;
		    }
		    else if(strcmp("out",entoli)==0){
		    	printf("Success: out(%d)=%f\n",id,temp->out);
		    	return;
		    }
		    else{
		    	printf("Success: sum(%d)=%f\n",id,(temp->in)-(temp->out));
		    	return;
			}
		}
		temp=temp->next;
	}
	if(temp==NULL){
		printf("Failure: O logariasmos %d den uparxei\n",id);
		return;
	}
}




void triangle(int id,dkorifis* Hash,int Bucket,float k){
	dkorifis temp,temp2,temp4;
	dakmis temp1,temp3,temp5;
	int r1,flag,flag1;
        flag=0;
        flag1=0;
	r1=function(id,Bucket);
	temp=Hash[r1];
	if(temp==NULL){
		printf("Failure: O logariasmos %d den uparxei\n",id);
		return;
	}
	while(temp!=NULL){                           //o temp deixnei ton logariasmo pou tha ginei triangle allios null pou einai minima lathous
		if(temp->salary!=id){
			temp=temp->next;
		}
		else
		    break;
	}
	if(temp==NULL){
		printf("Failure: O logariasmos %d den uparxei\n",id);
		return;
	}
	temp1=temp->list;
	if(temp1==NULL){
		printf("O logariasmos %d den empleketai se trigonikes sunallages\n",id);
		return;
	}
	while(temp1!=NULL){
		if(temp1->weight<k){                  //an afti i akmi exei varos mikrotero apo afto pou thelo pigaine se alli akmi
			temp1=temp1->next;
			continue;
		}
		temp2=temp1->list;                     //o temp2 deixnei ton deftero kombo gia trigono
		temp3=temp2->list;                     //o temp3 deixnei tin proti akmi tou temp2
		if(temp3==NULL){
			temp1=temp1->next;
			continue;
		}
		while(temp3!=NULL){
			if(temp3->weight<k){                  //an exei varos mikrotero tou epitreptomenou i akmi tou temp2 pigaine stin epomeni
			temp3=temp3->next;
			continue;
		    }
		    temp4=temp3->list;                    //o temp4 deixnei ton trito upopsifio kombo tou trigonou
		    temp5=temp4->list;                     //i proti akmi tou temp4
		    if(temp5==NULL){
			temp3=temp3->next;
			continue;
		    }
		    while(temp5!=NULL){
		    	if(temp5->list==temp && temp5->weight<k){       //an deixnei o tritos ton proto alla den exei epitreptomeno varos
                                break;
				}
				if(temp5->list==temp && temp5->weight>=k){            //an deixnei o tritos ton proto kai exei epitreptomeno varos
                                  flag1=1;
                                  if(flag==0){
                                    printf("success: Triangle(%d,%f)=\n",id,k);
                                    flag=1;
                                  }
                                  printf("(%d,%d,%d)\n",temp->salary,temp2->salary,temp4->salary);
                                  break;
				}
				temp5=temp5->next;
			}
			temp3=temp3->next;
		}
		temp1=temp1->next;
	}
        if(flag1==0)
	  printf("O logariasmos %d den empleketai se trigonikes sunallages\n",id);
}




void conn(int id1,int id2,dkorifis* Hash,int Bucket){
	dkorifis start, finish;
	dclosed arxi,temp;
	int r1, found;
	arxi=NULL;
	r1=function(id1,Bucket);
	start=Hash[r1];
	while(start!=NULL){                        //o start deixnei ton kombo pou ksekinaei i conn i lathos an den uparxei
		if(start->salary==id1)
			break;
		start=start->next;    
	}
	if(start==NULL){
		 printf("Failure: O logariasmos %d den uparxei\n",id1); 
		  return; 
		}
	
	r1=function(id2,Bucket);
	finish=Hash[r1];                              //i finish deixnei ton kombo pou teleionei i conn i lathos an den uparxei
	while(finish!=NULL){
		if(finish->salary==id2)
			break;
		finish=finish->next;    
	}
	if(finish==NULL){
		printf("Failure: O logariasmos %d den uparxei\n",id2);
		 return; 
	}
	eisagogi(start->salary,&arxi);	                 //vale ton proto kombo stin lista episkeptomenon
	found = monopati(start, finish, &arxi);           //anadromiki pou pernei orismata trexon logariasmo,teliko logariasmo,kai deikti stin lista closed 
	if(found==1)
	   printf("%d\n",id1);                             //ektuposi tou protou
	else
	   printf("conn(%d,%d) not found\n",id1,id2);
	temp=arxi;                          //katastrofi tis listas closed
	while(temp!=NULL){
		arxi=temp->next;
		free(temp);
		temp=arxi;
	}
}




int monopati(dkorifis a, dkorifis b, dclosed* arxi)
{
	dakmis acc;
	int z;
	if(a==NULL)             //an teleiosan oi logariasmoi sinthiki termatismou anadromis
		return 0;
	if(a==b)                 //an o trexon eeinai idios me ton finish telos anadromis
	  return 1;
	acc=a->list;
	while(acc!=NULL)            
	{
		if(anazitisi(acc->list->salary, *arxi) == 1){            //an uparxei stin lista closed epomeni akmi 
		    acc=acc->next;
			continue;
	    }
		eisagogi(acc->list->salary, arxi);                        //an den uparxei stin closed valton
		if(monopati(acc->list, b, arxi) == 1){
			  printf("%d <- ", acc->list->salary);                //ektuposi trexontos logariasmou
			  return 1;
			}
		else
		      acc=acc->next;
	}
	return 0;
}




void traceflow(int id,dkorifis* Hash,int Bucket,int depth){
	dkorifis start;
	dclosed arxi,temp;
	int r1,found;
	arxi=NULL;
	r1=function(id,Bucket);
	start=Hash[r1];
	while(start!=NULL){                                  //o start deixnei ston arxiko logariasmo gia traceflow h null gia lathos input
		if(start->salary==id)
			break;
		start=start->next;    
	}
	if(start==NULL){
		 printf("Failure: O logariasmos %d den uparxei\n",id); 
		  return; 
		}
	
	path(start,1,&arxi,depth);            //anadromiki exei orismata tin arxi ,to trexon vathos,deikti stin lista closed kai to vathos pou theloume na pame
        temp=arxi;
	while(temp!=NULL){                     //katastrofi tis closed
		arxi=temp->next;
		free(temp);
		temp=arxi;
	}
}



void path(dkorifis a,int trexonvathos, dclosed* arxi,int depth){
	dakmis acc;
	int z;
	if(a==NULL)                 //an teleiosan oi komboi tous episkeftikame olous
		return;
	if(trexonvathos>depth)             //termatizei an to trexon bathos einai>tou bathous pou theloume
	  return;
	acc=a->list;
	while(acc!=NULL)            
	{
		if(anazitisi(acc->list->salary, *arxi) == 1)             //an uparxei stin closed epestrepse piso
			return;
			
		eisagogi(acc->list->salary, arxi);                        //allios valto stin closed
		path(acc->list, trexonvathos+1, arxi, depth);              //tin kalo me ton epomeno kombo auksimeno bathos kata 1 ton deiki stin closed kai to depth
		printf("%d : %d me poso %f\n", trexonvathos, acc->list->salary, acc->weight);
		acc=acc->next;
	}
}



void eisagogi(int id, dclosed* head){
	dclosed temp;
	temp=malloc(sizeof(struct closed));
	if(temp==NULL){
		printf("Sorry cannot allocate memory\n");
		return;
	}
	temp->salary=id;
	temp->next=*head;
	*head = temp;
}



int anazitisi(int id, dclosed head){
	dclosed temp = head;
	while(temp!=NULL){
		if(temp->salary==id)
		  return 1;
		temp=temp->next;
	}
	  return 0;
}
