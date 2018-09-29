#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"
#include "insertdel.h"
#include "lookfor.h"

int main(int argc, char *argv[]) {
	FILE *fp;
	int i, j, duration, type, tarrif, fault_condition, arxeio, h1, h2, sbytes;
	sdate date,date1;
	stime init_time,init_time1;
	char buffer[100], entoli[20], entoli1[20], entoli2[20], entoli3[20],
			entoli4[20], entoli5[20], entoli6[10], entoli7[10], entoli8[10],
			entoli9[10], filename[15];
	char temp[20];
	dbluebucket* Hash1;
	dbluebucket* Hash2;
	int flag=0;
	arxeio = 0;
	for (i = 1; i < argc; i++) { //upologismos orismaton grammis entolon
		if (strcmp(argv[i], "-o") == 0) {
			strcpy(filename, argv[i + 1]);
			arxeio = 1;
		}
		if (strcmp(argv[i], "-h1") == 0)
			h1 = atoi(argv[i + 1]);
		if (strcmp(argv[i], "-h2") == 0)
			h2 = atoi(argv[i + 1]);
		if (strcmp(argv[i], "-s") == 0)
			sbytes = atoi(argv[i + 1]);
	}

	bucketscapacity(sbytes);
	Hash1 = (dbluebucket*) malloc(h1 * sizeof(dbluebucket));
	for (i = 0; i < h1; i++) //pinakas katakermatismou ola ta kelia null
		Hash1[i] = NULL;
	Hash2 = (dbluebucket*) malloc(h2 * sizeof(dbluebucket));
	for (i = 0; i < h2; i++) //pinakas katakermatismou ola ta kelia null
		Hash2[i] = NULL;
	if (arxeio == 1) { //an uparxei eksoteriko arxeio operations
		fp = fopen(filename, "r");
	} else
		fp = stdin;
while(1){
	while (!feof(fp)) {
		if(flag==0)
			fscanf(fp, "%s", entoli);
		if (strcmp(entoli, "insert") == 0) {
			fscanf(fp, "%s", buffer);
			i = 0;
			while (buffer[i] != ';') {
				entoli1[i] = buffer[i];
				i++;
			}
			entoli1[i] = '\0';
			i++;
			j = 0;
			while (buffer[i] != ';') {
				entoli2[j] = buffer[i];
				i++;
				j++;
			}
			entoli2[14] = '\0';
			i++;
			j = 0;
			while (buffer[i] != ';') {
				entoli3[j] = buffer[i];
				i++;
				j++;
			}
			entoli3[14] = '\0';
			i++;
			j = 0;
			while (buffer[i] != ';') {
				entoli4[j] = buffer[i];
				i++;
				j++;
			}
			i++;
			entoli4[j] = '\0';
			strncpy(temp, entoli4, 2);
			temp[2] = '\0';
			date.day = atoi(temp);
			strncpy(temp, entoli4 + 2, 2);
			temp[2] = '\0';
			date.month = atoi(temp);
			strncpy(temp, entoli4 + 4, 4);
			temp[4] = '\0';
			date.year = atoi(temp);
			j = 0;
			while (buffer[i] != ';') {
				entoli5[j] = buffer[i];
				i++;
				j++;
			}
			i++;
			entoli5[j] = '\0';
			strncpy(temp, entoli5, 2);
			temp[2] = '\0';
			init_time.hour = atoi(temp);
			strncpy(temp, entoli5 + 3, 2);
			temp[2] = '\0';
			init_time.minute = atoi(temp);
			j = 0;
			while (buffer[i] != ';') {
				entoli6[j] = buffer[i];
				i++;
				j++;
			}
			entoli6[j] = '\0';
			i++;
			duration = atoi(entoli6);
			j = 0;
			while (buffer[i] != ';') {
				entoli7[j] = buffer[i];
				i++;
				j++;
			}
			entoli7[j] = '\0';
			i++;
			type = atoi(entoli7);
			j = 0;
			while (buffer[i] != ';') {
				entoli8[j] = buffer[i];
				i++;
				j++;
			}
			i++;
			entoli8[j] = '\0';
			tarrif = atoi(entoli8);
			j = 0;
			while (buffer[i] != '\0') {
				entoli9[j] = buffer[i];
				i++;
				j++;
			}
			entoli9[j] = '\0';
			fault_condition = atoi(entoli9);
			Insert(Hash1, h1, Hash2, h2, entoli1, entoli2, entoli3, date,
					init_time, duration, type, tarrif, fault_condition);
			flag=0;
			continue;
		} ////telos insert/////////
		else if(strcmp(entoli, "delete") == 0){
			fscanf(fp, "%s", entoli2);		///caller
			fscanf(fp, "%s", entoli1);		///uniq-id
			delete(Hash1,h1,entoli1,entoli2);
			flag=0;
			continue;
		}
		else if(strcmp(entoli, "print") == 0){
			fscanf(fp, "%s", entoli2);
			if(strcmp(entoli2,"hashtable1") == 0)
				printhashtable(Hash1,h1);
			if(strcmp(entoli2,"hashtable2") == 0)
				printhashtable(Hash2,h2);
			flag=0;
			continue;
		}
		else if(strcmp(entoli,"find")==0){
			fscanf(fp, "%s", entoli2);			//caller
			fscanf(fp, "%s", entoli);			//proti entoli tis find
			if(entoli[0]>='0' && entoli[0]<='9'){
				if(strlen(entoli)==5){
							/////exoume orisma xronou
					strncpy(temp,entoli,2);
					temp[2] ='\0';
					init_time.hour = atoi(temp);
					strncpy(temp, entoli + 3, 2);
					temp[2] = '\0';
					init_time.minute = atoi(temp);
					fscanf(fp,"%s",entoli3);		///deftero noumero  sta orismata tin find
					if(strlen(entoli3)==5){
						strncpy(temp,entoli3,2);
						temp[2] ='\0';
						init_time1.hour = atoi(temp);
						strncpy(temp, entoli3 + 3, 2);
						temp[2] ='\0';
						init_time1.minute = atoi(temp);
						date.year=3000;
						date1.year=3000;
						find(Hash1,h1,entoli2,date,init_time,date1,init_time1);
						flag=0;
						continue;
					}
					else{
						strncpy(temp, entoli3, 2);
						temp[2] = '\0';
						date.day = atoi(temp);
						strncpy(temp, entoli3 + 2, 2);
						temp[2] = '\0';
						date.month = atoi(temp);
						strncpy(temp, entoli3 + 4, 4);
						temp[4] = '\0';
						date.year = atoi(temp);
						fscanf(fp,"%s",entoli4);		///trito noumero stin find wra
						strncpy(temp,entoli4,2);
						temp[2] ='\0';
						init_time1.hour = atoi(temp);
						strncpy(temp, entoli4 + 3, 2);
						temp[2] ='\0';
						init_time1.minute = atoi(temp);
						fscanf(fp,"%s",entoli5);			//tetarto noumero stin find
						strncpy(temp, entoli5, 2);
						temp[2] = '\0';
						date1.day = atoi(temp);
						strncpy(temp, entoli5 + 2, 2);
						temp[2] = '\0';
						date1.month = atoi(temp);
						strncpy(temp, entoli5 + 4, 4);
						temp[4] = '\0';
						date1.year = atoi(temp);
						find(Hash1,h1,entoli2,date,init_time,date1,init_time1);
						flag=0;
						continue;
					}
				}
				else{
					strncpy(temp,entoli,2);
					temp[2] = '\0';
					date.day = atoi(temp);
					strncpy(temp, entoli + 2, 2);
					temp[2] = '\0';
					date.month = atoi(temp);
					strncpy(temp, entoli + 4, 4);
					temp[4] = '\0';
					date.year = atoi(temp);
					fscanf(fp,"%s",entoli7);		//defteri imerominia
					strncpy(temp,entoli7,2);
					temp[2] = '\0';
					date1.day = atoi(temp);
					strncpy(temp, entoli7 + 2, 2);
					temp[2] = '\0';
					date1.month = atoi(temp);
					strncpy(temp, entoli7 + 4, 4);
					temp[4] = '\0';
					date1.year = atoi(temp);
					init_time.hour=25;
					init_time1.hour=25;
					find(Hash1,h1,entoli2,date,init_time,date1,init_time1);
					flag=0;
					continue;
				}
			}
			else{
				//////h find den exei orismata///////
				date.year=3000;
				init_time.hour=25;
				date1.year=3000;
				init_time1.hour=25;
				find(Hash1,h1,entoli2,date,init_time,date1,init_time1);
				flag=1;
				continue;
			}
		}
		else if(strcmp(entoli,"lookup")==0){
			fscanf(fp, "%s", entoli2);			//callee
			fscanf(fp, "%s", entoli);			//proti entoli tis lookup
			if(entoli[0]>='0' && entoli[0]<='9'){
				if(strlen(entoli)==5){
							/////exoume orisma xronou
					strncpy(temp,entoli,2);
					temp[2] ='\0';
					init_time.hour = atoi(temp);
					strncpy(temp, entoli + 3, 2);
					temp[2] = '\0';
					init_time.minute = atoi(temp);
					fscanf(fp,"%s",entoli3);		///deftero noumero  sta orismata tin lookup
					if(strlen(entoli3)==5){
						strncpy(temp,entoli3,2);
						temp[2] ='\0';
						init_time1.hour = atoi(temp);
						strncpy(temp, entoli3 + 3, 2);
						temp[2] ='\0';
						init_time1.minute = atoi(temp);
						date.year=3000;
						date1.year=3000;
						lookup(Hash2,h2,entoli2,date,init_time,date1,init_time1);
						flag=0;
						continue;
					}
					else{
						strncpy(temp, entoli3, 2);
						temp[2] = '\0';
						date.day = atoi(temp);
						strncpy(temp, entoli3 + 2, 2);
						temp[2] = '\0';
						date.month = atoi(temp);
						strncpy(temp, entoli3 + 4, 4);
						temp[4] = '\0';
						date.year = atoi(temp);
						fscanf(fp,"%s",entoli4);		///trito noumero stin lookup wra
						strncpy(temp,entoli4,2);
						temp[2] ='\0';
						init_time1.hour = atoi(temp);
						strncpy(temp, entoli4 + 3, 2);
						temp[2] ='\0';
						init_time1.minute = atoi(temp);
						fscanf(fp,"%s",entoli5);			//tetarto noumero stin lookup
						strncpy(temp, entoli5, 2);
						temp[2] = '\0';
						date1.day = atoi(temp);
						strncpy(temp, entoli5 + 2, 2);
						temp[2] = '\0';
						date1.month = atoi(temp);
						strncpy(temp, entoli5 + 4, 4);
						temp[4] = '\0';
						date1.year = atoi(temp);
						lookup(Hash2,h2,entoli2,date,init_time,date1,init_time1);
						flag=0;
						continue;
					}
				}
				else{
					strncpy(temp,entoli,2);
					temp[2] = '\0';
					date.day = atoi(temp);
					strncpy(temp, entoli + 2, 2);
					temp[2] = '\0';
					date.month = atoi(temp);
					strncpy(temp, entoli + 4, 4);
					temp[4] = '\0';
					date.year = atoi(temp);
					fscanf(fp,"%s",entoli7);		//defteri imerominia
					strncpy(temp,entoli7,2);
					temp[2] = '\0';
					date1.day = atoi(temp);
					strncpy(temp, entoli7 + 2, 2);
					temp[2] = '\0';
					date1.month = atoi(temp);
					strncpy(temp, entoli7 + 4, 4);
					temp[4] = '\0';
					date1.year = atoi(temp);
					init_time.hour=25;
					init_time1.hour=25;
					lookup(Hash2,h2,entoli2,date,init_time,date1,init_time1);
					flag=0;
					continue;
				}
			}
			else{
				//////h lookup den exei orismata///////
				date.year=3000;
				init_time.hour=25;
				date1.year=3000;
				init_time1.hour=25;
				lookup(Hash2,h2,entoli2,date,init_time,date1,init_time1);
				flag=1;
				continue;
			}
		}
		else if(strcmp(entoli,"bye")==0){
			bye(Hash1,h1,Hash2,h2);
			continue;
		}
		else if(strcmp(entoli,"topdest")==0){
			fscanf(fp,"%s",entoli4);	//caller tis dest
			topdest(Hash1,h1,entoli4);
			continue;
		}
		else if(strcmp(entoli,"dump")==0){
			fscanf(fp,"%s",entoli3);	//hashtable number
			fscanf(fp,"%s",entoli2);	//filename
			if(strcmp(entoli3,"hashtable1")==0)
				dump(Hash1,h1,entoli2);
			if(strcmp(entoli3,"hashtable2")==0)
				dump(Hash2,h2,entoli2);
				continue;	
		}
	}
	if(arxeio==1)
		fp=stdin;
	if(arxeio==0)
		break;
}
	fclose(fp);
	free(Hash1);
	free(Hash2);
	return 0;
}

