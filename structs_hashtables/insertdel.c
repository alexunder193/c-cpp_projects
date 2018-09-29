#include "record.h"
#include "insertdel.h"
  
void printhashtable(dbluebucket* Hash, int hashtablesize) {
	int i;
	printf("-------------\n");
	for (i = 0; i < hashtablesize; i++) {
		if (Hash[i] == NULL)
			printf("Hash[%d] = empty\n", i);
		else {
			printf("Hash[%d] = \n", i);
			printallblue(Hash[i]);
		}
	}
	printf("-------------\n");
}

void bucketscapacity(int sbytes) {
	bluecapacity = (sbytes - sizeof(struct bluebucket*) - sizeof(int))
			/ sizeof(blue);
	pinkcapacity = (sbytes - sizeof(struct pinkbucket*) - sizeof(int))
			/ sizeof(pink);
	printf("bluecapacity=%d pinkcapacity=%d\n", bluecapacity, pinkcapacity);
}

dbluebucket createbluebucket() {
	dbluebucket temp = malloc(sizeof(struct bluebucket));
	if (temp == NULL) {
		printf("Sorry cannot allocate struct bluebucket\n");
		return NULL;
	}
	temp->next = NULL;
	temp->table = malloc(bluecapacity * sizeof(struct blue));
	if (temp->table == NULL) {
		printf("Sorry cannot allocate table for structs blue\n");
		return NULL;
	}
	temp->total = 0;
	return temp;

}

dpinkbucket createpinkbucket() {
	dpinkbucket temp = (dpinkbucket) malloc(sizeof(struct pinkbucket));
	if (temp == NULL) {
		printf("Sorry cannot allocate struct pinkbucket\n");
		return NULL;
	}
	temp->next = NULL;
	temp->table = malloc(pinkcapacity * sizeof(struct pink));
	if (temp->table == NULL) {
		printf("Sorry cannot allocate table for structs pink\n");
		return NULL;
	}
	temp->total = 0;
	return temp;
}

void insertpink(dpink p, char* uniqid, char* caller, char* callee, sdate date,
		stime init_time, int duration, int type, int tarrif,
		int fault_condition) {
	int mikosid = strlen(uniqid) + 1;

	p->uniq_id = malloc(mikosid * sizeof(char));

	strcpy(p->uniq_id, uniqid);
	strcpy(p->originator, caller);
	strcpy(p->destinator, callee);

	p->date = date;
	p->init_time = init_time;
	p->duration = duration;
	p->type = type;
	p->tarrif = tarrif;
	p->fault_condition = fault_condition;
	p->deleted = 0;

}

void insertnewblue(dblue b, char* tel, char* uniqid, char* caller,
		char* callee, sdate date, stime init_time, int duration, int type,
		int tarrif, int fault_condition) {
	dpinkbucket pb;

	strcpy(b->call, tel);
	pb = createpinkbucket();
	pb->total = 1;
	b->pointer = pb;
	insertpink(&(pb->table[0]), uniqid, caller, callee, date, init_time,
			duration, type, tarrif, fault_condition);
}

void updateblue(dblue b, char* tel, char* uniqid, char* caller, char* callee,
		sdate date, stime init_time, int duration, int type, int tarrif,
		int fault_condition) {
	dpinkbucket pb;

	strcpy(b->call, tel);
	pb = createpinkbucket();
	insertpink(&(pb->table[0]), uniqid, caller, callee, date, init_time,
			duration, type, tarrif, fault_condition);
	pb->total = 1;
	b->pointer = pb;
}

dblue searchblue(dbluebucket bb, char* tel) {
	int i;
	dbluebucket tmp;
	tmp = bb;

	while (tmp != NULL) {
		for (i = 0; i < bb->total; i++) {
			if (strcmp(bb->table[i].call, tel) == 0) {
				return &(bb->table[i]);
			}
		}
		tmp = tmp->next;
	}
	return NULL;
}

void printallblue(dbluebucket bb) {
	int i;
	dbluebucket tmp;
	tmp = bb;

	while (tmp != NULL) {
		for (i = 0; i < bb->total; i++) {
			printf(" [tel = %s]\n", bb->table[i].call);
			printf("\n");
			fflush(NULL);
			printallpink(bb->table[i].pointer);
		}
		tmp = tmp->next;
	}
}

dblue searchfreeblue(dbluebucket bb) {
	dbluebucket tmp, prev, newbb;
	tmp = bb;

	while (tmp != NULL) {
		if (tmp->total < bluecapacity) {
			tmp->total++;
			return &(tmp->table[tmp->total - 1]);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	// uperxeilisi ftiakse kainourgio kado kai valto stin proti thesi
	newbb = createbluebucket();
	prev->next = newbb;
	newbb->total = 1;
	return &(newbb->table[0]);
}

void printallpink(dpinkbucket pb) {
	int i;
	dpinkbucket tmp = pb;
	while (tmp != NULL) {

		for (i = 0; i < tmp->total; i++) {

			if (tmp->table[i].deleted == 0) {
				printf("   uniqid = %s\n", tmp->table[i].uniq_id);
				printf("   originator = %s\n", tmp->table[i].originator);
				printf("   destinator = %s\n", tmp->table[i].destinator);
				printf("   date = %d/%d/%d\n", tmp->table[i].date.day,
						tmp->table[i].date.month, tmp->table[i].date.year);
				printf("   init_time = %d:%d\n", tmp->table[i].init_time.hour,
						tmp->table[i].init_time.minute);
				printf("   duration = %d\n", tmp->table[i].duration);
				printf("   type = %d\n", tmp->table[i].type);
				printf("   tarrif = %d\n", tmp->table[i].tarrif);
				printf("   fault_condition = %d\n",
						tmp->table[i].fault_condition);
				printf("\n");
			}
		}

		tmp = tmp->next;
	}
}

dpink searchfreepink(dpinkbucket pb) {
	int i;
	dpinkbucket tmp, prev, newpb;
	tmp = pb;

	while (tmp != NULL) {

		if (tmp->total < pinkcapacity) {
			for (i = 0; i < tmp->total; i++) {

				if (tmp->table[i].deleted == 1) {
					tmp->total++;
					return &(tmp->table[i]);
				}
			}

		}
		prev = tmp;
		tmp = tmp->next;
	}
	//uperxeilisi stin deuteri lista
	newpb = createpinkbucket();
	prev->next = newpb;
	newpb->total = 1;
	return &(newpb->table[0]);
}

void inserthashtable(dbluebucket* Hash, int hashtablesize, char* tel,
		char* uniqid, char* caller, char* callee, sdate date, stime init_time,
		int duration, int type, int tarrif, int fault_condition) {
	dbluebucket bb;
	dblue b;
	dpink p;
	int position;
	position = hash_function(tel, hashtablesize);
	bb = Hash[position];
	if (bb == NULL) { //an o hash deixnei se NULL
		bb = createbluebucket();
		insertnewblue(&(bb->table[0]), tel, uniqid, caller, callee, date,
				init_time, duration, type, tarrif, fault_condition);
		bb->total = 1;
		Hash[position] = bb;
	} else { //an o hash den deixnei se null
		b = searchblue(bb, tel);
		if (b == NULL) { //neo blue
			b = searchfreeblue(bb); //thelw  keno gia kainourgio thlefono
			insertnewblue(b, tel, uniqid, caller, callee, date, init_time,
					duration, type, tarrif, fault_condition);
		} else { //mono neo pink 	an to tilefono exei idi perastei palaiotera se kapoio kado
			//kremase tin deftereuousa domi ston kado afto
			p = searchfreepink(b->pointer); //thelw  keno gia kainourgio cdr
			insertpink(p, uniqid, caller, callee, date, init_time, duration,
					type, tarrif, fault_condition);
		}
	}
}
void Insert(dbluebucket* Hash1, int hashtable1size, dbluebucket* Hash2,
		int hashtable2size, char* uniqid, char* caller, char* callee,
		sdate date, stime init_time, int duration, int type, int tarrif,
		int fault_condition) {

	inserthashtable(Hash1, hashtable1size, caller, uniqid, caller, callee,
			date, init_time, duration, type, tarrif, fault_condition);
	printf("------ To cdr me id=%s eisix8i epituxos sto Hashtable1\n",uniqid);
	inserthashtable(Hash2, hashtable2size, callee, uniqid, caller, callee,
			date, init_time, duration, type, tarrif, fault_condition);
	printf("------ To cdr me id=%s eisix8i epituxos sto Hashtable2\n",uniqid);
}


void delete(dbluebucket* Hash,int hashtablesize,char* uniqid,char* caller){
	dbluebucket bb;
	dblue b;
	dpinkbucket pb,nextpink;
	dpink p;
	int i,j,position;
	int valid=0;
	position=hash_function(caller,hashtablesize);
	bb=Hash[position];
	if(bb==NULL){
		printf("I cannot delete something that not exists\n");
		return;
	}
	while(bb!=NULL){				//elegxos an einai egkuri h entoli
		b=bb->table;
		for(i=0; i<bb->total; i++){
			if(strcmp(b[i].call,caller)==0){
				if(b[i].pointer!=NULL){
					pb=b[i].pointer;
					while(pb!=NULL){
						p=pb->table;
						for(j=0; j<pinkcapacity; j++){
							if(p[j].deleted==0){
								if(strcmp(p[j].uniq_id,uniqid)==0){
									valid=1;
									break;
								}
							}
						}
						if(valid==1)
							break;
						pb=pb->next;
					}
				}
			}
			if(valid==1)
				break;
		}
		if(valid==1)
			break;
		bb=bb->next;
	}						//telous elegxou egkuris entolis
	if(valid==1){
		//////////////delete/////////
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
							if(strcmp(p[j].uniq_id,uniqid)==0){
								if(pb->total>1 && p[j].deleted==0){
									p[j].deleted=1;
									(pb->total)--;
									printf("To cdr me id:%s kai arithmo:%s diagrafike\n",uniqid,caller);
									return;
								}
								else{
									////////////an exei ena stoixeio to diagrafoume kai diagrafoume kai ton pink kado/////
									if(pb==b[i].pointer){
										////////////an einai o protos pink kados tote diagrafi arxi
										nextpink=pb;
										nextpink=nextpink->next;
										free(pb->table);
										free(pb);
										b[i].pointer=nextpink;
										printf("To cdr me id:%s kai arithmo:%s diagrafike\n",uniqid,caller);
										return;
									}
									else{
										nextpink=b[i].pointer;
										while(nextpink->next!=pb)
											nextpink=nextpink->next;
										nextpink->next=pb->next;
										free(pb->table);
										free(pb);
										printf("To cdr me id:%s kai arithmo:%s diagrafike\n",uniqid,caller);
										return;
									}
								}
							}
							}
						}
						pb=pb->next;
					}
				}
			}
			bb=bb->next;
		}
	}
	else{
		printf("I cannot delete something that not exists\n");
		return;
	}
}


void bye(dbluebucket* Hash1,int hashtable1size,dbluebucket* Hash2,int hashtable2size){
	int i,j,k;
	dbluebucket bb,temp1;
	dblue b;
	dpinkbucket pb,temp;
	dpink p;
	for(i=0; i<hashtable1size; i++){
		if(Hash1[i]==NULL)
			continue;
		bb=Hash1[i];
		while(bb!=NULL){
			b=bb->table;
			for(j=0; j<bb->total; j++){
				pb=b[j].pointer;
				if(pb==NULL)
					continue;
				while(pb!=NULL){
					p=pb->table;
					temp=pb;
					for(k=0; k<pinkcapacity; k++){
						if(p[k].deleted!=0 && p[k].deleted!=1)
							continue;
						free(p[k].uniq_id);
					}
					free(p);
					b[j].pointer=pb->next;
					pb=pb->next;
					free(temp);
				}
			}
			free(b);
			temp1=bb;
			Hash1[i]=bb->next;
			bb=bb->next;
			free(temp1);
		}
	}
	printf("Oi domes tou Hashtable1 eleutherothikan\n");
	for(i=0; i<hashtable2size; i++){
		if(Hash2[i]==NULL)
			continue;
		bb=Hash2[i];
		while(bb!=NULL){
			b=bb->table;
			for(j=0; j<bb->total; j++){
				pb=b[j].pointer;
				if(pb==NULL)
					continue;
				while(pb!=NULL){
					p=pb->table;
					temp=pb;
					for(k=0; k<pinkcapacity; k++){
						if(p[k].deleted!=0 && p[k].deleted!=1)
							continue;
						free(p[k].uniq_id);
					}
					free(p);
					b[j].pointer=pb->next;
					pb=pb->next;
					free(temp);
				}
			}
			free(b);
			temp1=bb;
			Hash2[i]=bb->next;
			bb=bb->next;
			free(temp1);
		}
	}
	printf("Oi domes tou Hashtable2 eleutherothikan\n");	
}

