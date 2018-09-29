#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

bool checkIPT(int pid,int page_no,char mode, int k, struct grammi * ipt);
int findPosition(int k , struct grammi * ipt);
int flushIPT(int k,int pid,struct grammi * ipt);
void processRequest(int page_no,char mode,int k, int * hits, int * pfs, int * pf, int * writes_to_disk, struct grammi * ipt, int pid);

struct grammi{
	int pid; //process id (0 h 1)
	int page_no; // page number
	bool valid; // an yparxei i oxi
	bool dirty; // an exei allaksei i selida sti mnimi
};

int main(int argc,char *argv[]){
	if(argc!=3){
		printf("Give only 2 arguments\n");
		exit(-1);		
	}
	int k=atoi(argv[1]);
	int q=atoi(argv[2]);
	fstream bzip("bzip.trace", ios_base::in);
	fstream gcc("gcc.trace", ios_base::in);

	unsigned int logical_address;
	char mode;

	int page_no;
	// genika statistika
	int hits=0, pfs=0 , writes_to_disk=0;
	
	// statistiko gia kathe diergasia etsi wste na 3eroume pote tha kanoume flush when full me vasi to k
	int pf[2];
	int i=0;
	
	struct grammi * ipt = (struct grammi *)malloc( 2*k *  sizeof(struct grammi));
	for(int i=0;i<(2*k); i++){
		ipt[i].valid=false;
	}
	while(bzip.good()){
		bzip >> std::hex >> logical_address;
		bzip >> mode;
		page_no = logical_address >> 12;
		processRequest(page_no,mode,k,&hits,&pfs,pf,&writes_to_disk,ipt,0);
		gcc >> std::hex >> logical_address;
		gcc >> mode;
		page_no = logical_address >> 12;
		processRequest(page_no,mode,k,&hits,&pfs,pf,&writes_to_disk,ipt,1);
		i++;
		i++;
		if( i == q){
			i=0;
			pf[0]=0;
			pf[1]=0;
			writes_to_disk = writes_to_disk + flushIPT(k,0,ipt); // diegrapse ola ta frames gia ti diergasia 0
			writes_to_disk = writes_to_disk + flushIPT(k,1,ipt); // diegrapse ola ta frames gia ti diergasia 1
		}
	}
	printf("Statistics: [ hits=%d ] , [ page faults=%d ] , [ writes_to_disk=%d ]\n",hits,pfs,writes_to_disk);
	printf("Statistics (): [ hits=%lf ] , [ page faults=%lf ] , [ writes_to_disk=%lf ]\n",hits/2000002.0,pfs/2000002.0,writes_to_disk/2000002.0);
	free(ipt);
    return 0;
}

/* afti i sinartisi, koitaei an yparxei i eggrafi ston IPT */
bool checkIPT(int pid, int page_no, char mode , int k , struct grammi * ipt){
	for(int i=0;i<(2*k);i++){
		if(ipt[i].valid){
			if((pid == ipt[i].pid) &&  (page_no == ipt[i].page_no )){
				if(mode == 'W'){
					ipt[i].dirty=true;
				}
				return true;
			}
		}
	}
	return false;	
}


/* afti i sinartisi, vriskei tin thesi ston IPT */
int findPosition(int k , struct grammi * ipt){
	for(int i=0;i<(2*k);i++){
		if(ipt[i].valid == false){
			return i;
		}
	}
	return -1;
}

/* afti i sinartisi kanei clean oles tis selides tou process me pid, kai epistrefei poses fores egra4e anagkastika sto disko logw dirty bit */
int flushIPT(int k,int pid,struct grammi * ipt){
	int writes_to_disk=0;
	for(int i=0;i<(2*k);i++){
		if(ipt[i].valid == true && ipt[i].pid==pid){
			if(ipt[i].dirty == true){
				writes_to_disk++;
			}
			ipt[i].valid=false;
		}
	}
	return writes_to_disk;
}




void processRequest(int page_no,char mode, int k, int * hits, int * pfs, int * pf, int * writes_to_disk, struct grammi * ipt, int pid){
	bool to_vrike=checkIPT(pid,page_no,mode,k, ipt);
	if(to_vrike){
		(*hits)++;
	}else{
		int position;
		(*pfs)++; // afxanoume ta synolika page faults tou leitourgikou
		pf[pid]++; // edw afxanoume ta page faults pou sinevikan sti diarkeia enos block gia mia diergasia
		// me vasi ton Flush When Full algorithmo prepei sto k+1 pf na ekkenwsoume ta frames tis diergasias
		printf("to pf einai %d kai to k einai %d\n",pf[pid],k);
		if(pf[pid] > k ){
			printf("OVER\n");
			pf[pid]=0;
			(*writes_to_disk) = (*writes_to_disk) + flushIPT(k,pid,ipt); // diegrapse ola ta frames gia ti diergasia 0
		}else{
			position = findPosition(k,ipt);
			if(position < 0){
				// simainei de vrike katholou eleftheri thesi
				// den perimenoume na symvei afto
				printf("ERRRRRRROOOOOOOR");
				exit(-1);
			}else{
				// simplirwnoume mia grammi sto IPT giati yparxei eleftheri thesi
				ipt[position].pid=pid;
				ipt[position].page_no=page_no;
				ipt[position].valid=true;
				if(mode == 'R'){
					ipt[position].dirty= false;
				}else{
					//mode == 'W'
					ipt[position].dirty= true;
				}
			}
		}
	}
	printf("%c %d\n",mode,page_no);
}
