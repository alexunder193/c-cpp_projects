#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pink *dpink;
typedef struct bluebucket *dbluebucket;
typedef struct blue *dblue;
typedef struct pinkbucket *dpinkbucket;

typedef struct sdate {
	int day;
	int month;
	int year;
} sdate;

typedef struct stime {
	int minute;
	int hour;
} stime;

typedef struct topdestination {				//gia tin top dest
	char code[4];
	int plithos;
}topdestination;

typedef struct blue {
	char call[15]; //tilefono
	dpinkbucket pointer; //pointer se pink
} blue;

typedef struct bluebucket {
	dblue table; //pinakas tilefono-pointer se pink
	dbluebucket next; //deiktis sto epomeno bluebucket
	int total;
} bluebucket;

typedef struct pink {
	char *uniq_id; //monadiko id tou pink
	char originator[15]; //arithmos caller
	char destinator[15]; //arithmos callee
	sdate date; //hmeromhnia klisis
	stime init_time; //wra klisis
	int duration; //diarkeia klisis
	int type; //eidos klisis
	int tarrif; //timi sugkekrimenou tupou klisis
	int fault_condition; //provlima klisis
	int deleted;
} pink;

typedef struct pinkbucket {
	dpink table;
	dpinkbucket next;
	int total;
} pinkbucket;

int hash_function(char *, int); //Hash hash_function
