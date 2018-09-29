#include "record.h"
#include "lookfor.h"
#include "insertdel.h"
  

void find(dbluebucket* Hash,int hashtable1size,char* caller,sdate date,stime init_time,sdate date1,stime init_time1){
	dbluebucket bb;
	dblue b;
	dpinkbucket pb;
	dpink p;
	int i,j,position,argument,numofmins,numofmins1,numofminscdr,numofdays,numofdays1,numofdayscdr;
	int flag=0;
	int epistrofi=0;
	position=hash_function(caller,hashtable1size);
	bb=Hash[position];
	if(bb==NULL){
		printf("Den uparxei o caller pou eodses\n");
		return;
	}
	while(bb!=NULL){
		b=bb->table;
		for(i=0; i<bb->total; i++){
			if((strcmp(b[i].call,caller)==0)&&(b[i].pointer!=NULL)){
				flag=1;
				break;
			}
		}
		if(flag==1)
			break;
		bb=bb->next;
	}
	if(flag==1){				/////an o arithmos pou dothike stin find uparxei se kapoio blue bucket
		if(init_time.hour==25 && date.year==3000)
			argument=0;			//den uparxoun orismata peran tou caller
		else if(init_time.hour!=25 && date.year==3000)
			argument=1;			//uparxoun peran tou caller mono orismata xronou
		else if(init_time.hour==25 && date.year!=3000)
			argument=2;			//uparxoun peran tou caller mono orismata hmerominias
		else
			argument=3;			//uparxoun kai xronika kai orismata hmerominias	
		bb=Hash[position];
		while(bb!=NULL){
			b=bb->table;
			for(i=0; i<bb->total; i++){
				if((strcmp(b[i].call,caller)==0)&&(b[i].pointer!=NULL)){
					printf("O sundromitis %s exei kalesei to sugkekrimeno diasthma tous:\n",caller);
					printf("____________________________________________\n");
					pb=b[i].pointer;
					while(pb!=NULL){
						p=pb->table;
						if(argument==0){
							for(j=0; j<pinkcapacity; j++){
								if(p[j].deleted==0){
									if(p[j].uniq_id != NULL){
										printf("id=%s\n",p[j].uniq_id);
										printf("destinator=%s\n",p[j].destinator);
										printf("day=%d  month=%d year=%d\n",p[j].date.day,p[j].date.month,p[j].date.year);
										printf("hour=%d  minute=%d\n",p[j].init_time.hour,p[j].init_time.minute);
										printf("duration=%d\n",p[j].duration);
										printf("type=%d\n",p[j].type);
										printf("tarrif=%d\n",p[j].tarrif);
										printf("fault condition=%d\n",p[j].fault_condition);
										printf("____________________________________________\n");
										epistrofi=1;
									}
								}
							}
						}
						else if(argument==1){
							numofmins=((init_time.hour*60)+init_time.minute);
							numofmins1=((init_time1.hour*60)+init_time.minute);
							for(j=0; j<pinkcapacity; j++){
								if(p[j].deleted==0){
									if(p[j].uniq_id != NULL){
										numofminscdr=(((p[j].init_time.hour)*60)+p[j].init_time.minute);
										if(numofminscdr>=numofmins && numofminscdr<=numofmins1){
										printf("id=%s\n",p[j].uniq_id);
										printf("destinator=%s\n",p[j].destinator);
										printf("day=%d  month=%d year=%d\n",p[j].date.day,p[j].date.month,p[j].date.year);
										printf("hour=%d  minute=%d\n",p[j].init_time.hour,p[j].init_time.minute);
										printf("duration=%d\n",p[j].duration);
										printf("type=%d\n",p[j].type);
										printf("tarrif=%d\n",p[j].tarrif);
										printf("fault condition=%d\n",p[j].fault_condition);
										printf("____________________________________________\n");
										epistrofi=1;
										}
									}
								}
							}
						}
						else if(argument==2){
							numofdays=((date.year*365)+(date.month*30)+date.day);
							numofdays1=((date1.year*365)+(date1.month*30)+date1.day);
							for(j=0; j<pinkcapacity; j++){
								if(p[j].deleted==0){
									if(p[j].uniq_id != NULL){
										numofdayscdr=(((p[j].date.year)*365)+((p[j].date.month)*30)+(p[j].date.day));
										if(numofdayscdr>=numofdays && numofdayscdr<=numofdays1){
											printf("id=%s\n",p[j].uniq_id);
											printf("destinator=%s\n",p[j].destinator);
											printf("day=%d  month=%d year=%d\n",p[j].date.day,p[j].date.month,p[j].date.year);
											printf("hour=%d  minute=%d\n",p[j].init_time.hour,p[j].init_time.minute);
											printf("duration=%d\n",p[j].duration);
											printf("type=%d\n",p[j].type);
											printf("tarrif=%d\n",p[j].tarrif);
											printf("fault condition=%d\n",p[j].fault_condition);
											printf("____________________________________________\n");
											epistrofi=1;
										}
									}
								}
							}
						}
						else{
							numofdays=((date.year*365)+(date.month*30)+date.day);
							numofdays1=((date1.year*365)+(date1.month*30)+date1.day);
							numofmins=((init_time.hour*60)+init_time.minute);
							numofmins1=((init_time1.hour*60)+init_time.minute);
							for(j=0; j<pinkcapacity; j++){
								if(p[j].deleted==0){
									if(p[j].uniq_id != NULL){
										numofdayscdr=(((p[j].date.year)*365)+((p[j].date.month)*30)+(p[j].date.day));
										numofminscdr=(((p[j].init_time.hour)*60)+p[j].init_time.minute);
										if(numofdayscdr>=numofdays && numofdayscdr<=numofdays1){
											if(numofdayscdr>numofdays && numofdayscdr<numofdays1){
												printf("id=%s\n",p[j].uniq_id);
												printf("destinator=%s\n",p[j].destinator);
												printf("day=%d  month=%d year=%d\n",p[j].date.day,p[j].date.month,p[j].date.year);
												printf("hour=%d  minute=%d\n",p[j].init_time.hour,p[j].init_time.minute);
												printf("duration=%d\n",p[j].duration);
												printf("type=%d\n",p[j].type);
												printf("tarrif=%d\n",p[j].tarrif);
												printf("fault condition=%d\n",p[j].fault_condition);
												printf("____________________________________________\n");
												epistrofi=1;
											}
											else if(numofdayscdr==numofdays && numofminscdr>=numofmins){
												printf("id=%s\n",p[j].uniq_id);
												printf("destinator=%s\n",p[j].destinator);
												printf("day=%d  month=%d year=%d\n",p[j].date.day,p[j].date.month,p[j].date.year);
												printf("hour=%d  minute=%d\n",p[j].init_time.hour,p[j].init_time.minute);
												printf("duration=%d\n",p[j].duration);
												printf("type=%d\n",p[j].type);
												printf("tarrif=%d\n",p[j].tarrif);
												printf("fault condition=%d\n",p[j].fault_condition);
												printf("____________________________________________\n");
												epistrofi=1;
											}
											else if(numofdayscdr==numofdays1 && numofminscdr<=numofmins1){
												printf("id=%s\n",p[j].uniq_id);
												printf("destinator=%s\n",p[j].destinator);
												printf("day=%d  month=%d year=%d\n",p[j].date.day,p[j].date.month,p[j].date.year);
												printf("hour=%d  minute=%d\n",p[j].init_time.hour,p[j].init_time.minute);
												printf("duration=%d\n",p[j].duration);
												printf("type=%d\n",p[j].type);
												printf("tarrif=%d\n",p[j].tarrif);
												printf("fault condition=%d\n",p[j].fault_condition);
												printf("____________________________________________\n");
												epistrofi=1;
											}
											else{
												
											}
										}
									}
								}
							}
						}
						pb=pb->next;
					}
					if(epistrofi==1)
						return;	
				}
			}
			bb=bb->next;
		}
	printf("Den vrethikan CDR's sto sugkekrimeno diasthma\n");
	}
	else{
		printf("Den uparxei o caller pou edoses\n");
		return;
	}
}




void lookup(dbluebucket* Hash,int hashtable1size,char* caller,sdate date,stime init_time,sdate date1,stime init_time1){
	dbluebucket bb;
	dblue b;
	dpinkbucket pb;
	dpink p;
	int i,j,position,argument,numofmins,numofmins1,numofminscdr,numofdays,numofdays1,numofdayscdr;
	int flag=0;
	int epistrofi=0;
	position=hash_function(caller,hashtable1size);
	bb=Hash[position];
	if(bb==NULL){
		printf("Den uparxei o callee pou eodses\n");
		return;
	}
	while(bb!=NULL){
		b=bb->table;
		for(i=0; i<bb->total; i++){
			if((strcmp(b[i].call,caller)==0)&&(b[i].pointer!=NULL)){
				flag=1;
				break;
			}
		}
		if(flag==1)
			break;
		bb=bb->next;
	}
	if(flag==1){				/////an o arithmos pou dothike stin lookup uparxei se kapoio blue bucket
		if(init_time.hour==25 && date.year==3000)
			argument=0;			//den uparxoun orismata peran tou caller
		else if(init_time.hour!=25 && date.year==3000)
			argument=1;			//uparxoun peran tou caller mono orismata xronou
		else if(init_time.hour==25 && date.year!=3000)
			argument=2;			//uparxoun peran tou caller mono orismata hmerominias
		else
			argument=3;			//uparxoun kai xronika kai orismata hmerominias	
		bb=Hash[position];
		while(bb!=NULL){
			b=bb->table;
			for(i=0; i<bb->total; i++){
				if((strcmp(b[i].call,caller)==0)&&(b[i].pointer!=NULL)){
					printf("O sundromitis %s exei kalestei to sugkekrimeno diasthma apo tous:\n",caller);
					printf("____________________________________________\n");
					pb=b[i].pointer;
					while(pb!=NULL){
						p=pb->table;
						if(argument==0){
							for(j=0; j<pinkcapacity; j++){
								if(p[j].deleted==0){
									if(p[j].uniq_id != NULL){
										printf("id=%s\n",p[j].uniq_id);
										printf("originator=%s\n",p[j].originator);
										printf("day=%d  month=%d year=%d\n",p[j].date.day,p[j].date.month,p[j].date.year);
										printf("hour=%d  minute=%d\n",p[j].init_time.hour,p[j].init_time.minute);
										printf("duration=%d\n",p[j].duration);
										printf("type=%d\n",p[j].type);
										printf("tarrif=%d\n",p[j].tarrif);
										printf("fault condition=%d\n",p[j].fault_condition);
										printf("____________________________________________\n");
										epistrofi=1;
									}
								}
							}
						}
						else if(argument==1){
							numofmins=((init_time.hour*60)+init_time.minute);
							numofmins1=((init_time1.hour*60)+init_time.minute);
							for(j=0; j<pinkcapacity; j++){
								if(p[j].deleted==0){
									if(p[j].uniq_id != NULL){
										numofminscdr=(((p[j].init_time.hour)*60)+p[j].init_time.minute);
										if(numofminscdr>=numofmins && numofminscdr<=numofmins1){
											printf("id=%s\n",p[j].uniq_id);
											printf("originator=%s\n",p[j].originator);
											printf("day=%d  month=%d year=%d\n",p[j].date.day,p[j].date.month,p[j].date.year);
											printf("hour=%d  minute=%d\n",p[j].init_time.hour,p[j].init_time.minute);
											printf("duration=%d\n",p[j].duration);
											printf("type=%d\n",p[j].type);
											printf("tarrif=%d\n",p[j].tarrif);
											printf("fault condition=%d\n",p[j].fault_condition);
											printf("____________________________________________\n");
											epistrofi=1;
										}
									}
								}
							}
						}
						else if(argument==2){
							numofdays=((date.year*365)+(date.month*30)+date.day);
							numofdays1=((date1.year*365)+(date1.month*30)+date1.day);
							for(j=0; j<pinkcapacity; j++){
								if(p[j].deleted==0){
									if(p[j].uniq_id != NULL){
										numofdayscdr=(((p[j].date.year)*365)+((p[j].date.month)*30)+(p[j].date.day));
										if(numofdayscdr>=numofdays && numofdayscdr<=numofdays1){
											printf("id=%s\n",p[j].uniq_id);
											printf("originator=%s\n",p[j].originator);
											printf("day=%d  month=%d year=%d\n",p[j].date.day,p[j].date.month,p[j].date.year);
											printf("hour=%d  minute=%d\n",p[j].init_time.hour,p[j].init_time.minute);
											printf("duration=%d\n",p[j].duration);
											printf("type=%d\n",p[j].type);
											printf("tarrif=%d\n",p[j].tarrif);
											printf("fault condition=%d\n",p[j].fault_condition);
											printf("____________________________________________\n");
											epistrofi=1;
										}
									}
								}
							}
						}
						else{
							numofdays=((date.year*365)+(date.month*30)+date.day);
							numofdays1=((date1.year*365)+(date1.month*30)+date1.day);
							numofmins=((init_time.hour*60)+init_time.minute);
							numofmins1=((init_time1.hour*60)+init_time.minute);
							for(j=0; j<pinkcapacity; j++){
								if(p[j].deleted==0){
									if(p[j].uniq_id != NULL){
										numofdayscdr=(((p[j].date.year)*365)+((p[j].date.month)*30)+(p[j].date.day));
										numofminscdr=(((p[j].init_time.hour)*60)+p[j].init_time.minute);
										if(numofdayscdr>=numofdays && numofdayscdr<=numofdays1){
											if(numofdayscdr>numofdays && numofdayscdr<numofdays1){
												printf("id=%s\n",p[j].uniq_id);
												printf("originator=%s\n",p[j].originator);
												printf("day=%d  month=%d year=%d\n",p[j].date.day,p[j].date.month,p[j].date.year);
												printf("hour=%d  minute=%d\n",p[j].init_time.hour,p[j].init_time.minute);
												printf("duration=%d\n",p[j].duration);
												printf("type=%d\n",p[j].type);
												printf("tarrif=%d\n",p[j].tarrif);
												printf("fault condition=%d\n",p[j].fault_condition);
												printf("____________________________________________\n");
												epistrofi=1;												
											}
											else if(numofdayscdr==numofdays && numofminscdr>=numofmins){
												printf("id=%s\n",p[j].uniq_id);
												printf("originator=%s\n",p[j].originator);
												printf("day=%d  month=%d year=%d\n",p[j].date.day,p[j].date.month,p[j].date.year);
												printf("hour=%d  minute=%d\n",p[j].init_time.hour,p[j].init_time.minute);
												printf("duration=%d\n",p[j].duration);
												printf("type=%d\n",p[j].type);
												printf("tarrif=%d\n",p[j].tarrif);
												printf("fault condition=%d\n",p[j].fault_condition);
												printf("____________________________________________\n");
												epistrofi=1;												
											}
											else if(numofdayscdr==numofdays1 && numofminscdr<=numofmins1){
												printf("id=%s\n",p[j].uniq_id);
												printf("originator=%s\n",p[j].originator);
												printf("day=%d  month=%d year=%d\n",p[j].date.day,p[j].date.month,p[j].date.year);
												printf("hour=%d  minute=%d\n",p[j].init_time.hour,p[j].init_time.minute);
												printf("duration=%d\n",p[j].duration);
												printf("type=%d\n",p[j].type);
												printf("tarrif=%d\n",p[j].tarrif);
												printf("fault condition=%d\n",p[j].fault_condition);
												printf("____________________________________________\n");
												epistrofi=1;												
											}
											else{
												
											}
										}
									}
								}
							}
						}
						pb=pb->next;
					}
					if(epistrofi==1)
						return;	
				}
			}
			bb=bb->next;
		}
	printf("Den vrethikan CDR's sto sugkekrimeno diasthma\n");
	}
	else{
		printf("Den uparxei o callee pou edoses\n");
		return;
	}
}


void topdest(dbluebucket* Hash,int hashtablesize,char* caller){
	dbluebucket bb;
	dblue b;
	dpinkbucket pb;
	dpink p;
	int position,i,j,vrethike,thesi,flag,megisto;
	topdestination pinakas[1000];			//pinakas me kodikous xoron kai plithi
	char temp[4];
	vrethike=0;
	flag=0;
	position=hash_function(caller,hashtablesize);
	bb=Hash[position];
	if(bb==NULL){
		printf("Den uparxei o caller pou edoses\n");
		return;
	}
	while(bb!=NULL){				//elegxos an uparxei sto hashtable o caller pou dothike
		b=bb->table;
		for(i=0; i<bb->total; i++){
			if(strcmp(b[i].call,caller)==0){
				if(b[i].pointer!=NULL){
					vrethike=1;
					break;
				}
			}
		}
		if(vrethike==1)
			break;
		bb=bb->next;
	}							//telos elegxos
	if(vrethike==1){
		for(i=0; i<1000; i++)		
			pinakas[i].plithos=0;
		bb=Hash[position];
		while(bb!=NULL){
			b=bb->table;
			for(i=0; i<bb->total; i++){
				if(strcmp(b[i].call,caller)==0){
					pb=b[i].pointer;
					while(pb!=NULL){
						p=pb->table;
						for(j=0; j<pinkcapacity; j++){
							if(p[j].deleted==0){
								if(p[j].uniq_id != NULL){
									strncpy(temp,p[j].destinator,3);
									temp[3] = '\0';
									thesi=atoi(temp);
									(pinakas[thesi].plithos)++;
									pinakas[thesi].code[0]=temp[0];
									pinakas[thesi].code[1]=temp[1];
									pinakas[thesi].code[2]=temp[2];
									pinakas[thesi].code[3]=temp[3];
									flag=1;
								}
							}
						}
						pb=pb->next;
					}				
				}
				if(flag==1)
					break;
			}
			if(flag==1)
				break;
			bb=bb->next;
		}
		megisto=pinakas[0].plithos;
		for(i=0; i<999; i++){
			if(pinakas[i+1].plithos>megisto)
				megisto=pinakas[i+1].plithos;
		}
		for(i=0; i<1000; i++){
			if(pinakas[i].plithos==megisto){
				thesi=i;
				break;
			}
		}
		printf("_________________________________________________\n");
		printf("O caller exei kanei %d kliseis stin xwra me kwdiko:%s\n",megisto,pinakas[thesi].code);
		printf("_________________________________________________\n");
	}
	else{
		printf("Den uparxei o caller pou edoses\n");
		return;
	}
}



void dump(dbluebucket* Hash,int hashtablesize,char* filename){
	FILE *fp;
	dbluebucket bb;
	dblue b;
	dpinkbucket pb;
	dpink p;
	int i,j,k,number;
	fp=fopen(filename,"w");
	for(i=0; i<hashtablesize; i++){
		if(Hash[i]==NULL)
			continue;
		bb=Hash[i];
		while(bb!=NULL){
			b=bb->table;
			for(j=0; j<bb->total; j++){
				pb=b[j].pointer;
				if(pb==NULL)
					continue;
				while(pb!=NULL){
					p=pb->table;
					for(k=0; k<pinkcapacity; k++){
						if(p[k].deleted==0){
							if(p[k].uniq_id != NULL){
								fprintf(fp,"insert ");           //grapse grapse insert sto arxeio
								fprintf(fp,"%s;",p[k].uniq_id);
								fprintf(fp,"%s;",p[k].originator);
								fprintf(fp,"%s;",p[k].destinator);
								number=(p[k].date.day)/10;
								if(number==0)					////an einai monopsifios o p[k].date.day
									fprintf(fp,"0");
								fprintf(fp,"%d",p[k].date.day);
								number=(p[k].date.month)/10;
								if(number==0)
									fprintf(fp,"0");
								fprintf(fp,"%d",p[k].date.month);
								fprintf(fp,"%d;",p[k].date.year);
								number=(p[k].init_time.hour)/10;
								if(number==0)
									fprintf(fp,"0");
								fprintf(fp,"%d",p[k].init_time.hour);
								fprintf(fp,":");
								number=(p[k].init_time.minute)/10;
								if(number==0)
									fprintf(fp,"0");
								fprintf(fp,"%d;",p[k].init_time.minute);
								fprintf(fp,"%d;",p[k].duration);
								fprintf(fp,"%d;",p[k].type);
								fprintf(fp,"%d;",p[k].tarrif);
								fprintf(fp,"%d",p[k].fault_condition);
								fprintf(fp,"\n");
							}
						}
					}
					pb=pb->next;
				}
			}
			bb=bb->next;
		}
	}
	printf("Success dumped to %s\n",filename);
	fclose(fp);
}
