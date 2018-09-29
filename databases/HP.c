#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HP.h"
#include "BF.h"

int  HP_CreateFile(char *filename){
	int ari8mosblock, fp;
	void *arxiblock;

	if (BF_CreateFile(filename) < 0){
		BF_PrintError("Error creating file");
		return -1;
	}
	fp = BF_OpenFile(filename);
	if (fp < 0){
		BF_PrintError("Error open file");
		return -1;
	}
	if (BF_AllocateBlock(fp) < 0){
		BF_PrintError("Error allocate memory");
		return -1;
	}
	ari8mosblock = BF_GetBlockCounter(fp) - 1;
	if (ari8mosblock < 0){
		BF_PrintError("Error in number of blocks");
		return -1;
	}
	if (BF_ReadBlock(fp, ari8mosblock, &arxiblock) < 0){
		BF_PrintError("Error read block");
		return -1;
	}
	strcpy(arxiblock, "hp");
	if (BF_WriteBlock(fp, ari8mosblock) < 0){
		BF_PrintError("Error write block");
		return -1;
	}
	if (BF_CloseFile(fp) < 0){
		BF_PrintError("Error close file");
		return -1;
	}
	return 0;
}

int HP_OpenFile(char *filename){
	int fp, ari8mosblock, i;
	void *arxiblock;

	fp = BF_OpenFile(filename);
	if (fp < 0){
		BF_PrintError("Error open file");
		return -1;
	}
	ari8mosblock = BF_GetBlockCounter(fp) - 1;
	if (ari8mosblock < 0){
		BF_PrintError("Error in number of block");
		return -1;
	}
	if (BF_ReadBlock(fp, ari8mosblock, &arxiblock) < 0){
		BF_PrintError("Error read block");
		return -1;
	}
	i = strcmp(arxiblock,"hp");
	if (i != 0){
		BF_PrintError("Error is not hp file");
		return -1;
	}
	return fp;
}



int HP_CloseFile(int fp){
	int x;

	x = BF_CloseFile(fp);
	if (x < 0){
		BF_PrintError("Error close file");
		return -1;
	}
	return 0;
}

int HP_InsertEntry(int fp, Record record){
	int ari8mosblock, recordnumber, zero = 0; 
	void *arxiblock;

	ari8mosblock = BF_GetBlockCounter(fp) - 1;
	if (ari8mosblock < 0){
		BF_PrintError("Error count block");
		return -1;
  	}
	if (ari8mosblock == zero){
		if(BF_AllocateBlock(fp) < 0){
			BF_PrintError("Error allocate block");
			return -1;
		}
		ari8mosblock = BF_GetBlockCounter(fp) - 1;
		if (ari8mosblock < 0){
			BF_PrintError("Error count block");
			return -1;
		}
		if (BF_ReadBlock(fp, ari8mosblock, &arxiblock) < 0){
			BF_PrintError("Error read block");
      			return -1;
     		}
   		memcpy(arxiblock, &zero, sizeof(int));
	}
	else{
		if (BF_ReadBlock(fp, ari8mosblock, &arxiblock) < 0){
			BF_PrintError("Error read block");
      			return -1;
     		}
	}
	memcpy(&recordnumber, arxiblock, sizeof(int));
	if (recordnumber >= ((BLOCK_SIZE - sizeof(int)) / sizeof(Record))){
		if (BF_AllocateBlock(fp) < 0){
			BF_PrintError("Error allocateblock");
			return -1;
		}
		ari8mosblock = BF_GetBlockCounter(fp) - 1;
		if (ari8mosblock < 0){
			BF_PrintError("Error count block");
			return -1;
		}
		if (BF_ReadBlock(fp, ari8mosblock, &arxiblock) < 0 ){
			BF_PrintError("Error read block");
			return -1;
		}
		memcpy(arxiblock, &zero, sizeof(int));
		recordnumber = zero;
	}		
	memcpy(arxiblock + sizeof(int) + recordnumber * sizeof(Record), &record, sizeof(Record));
	recordnumber++;
	memcpy(arxiblock, &recordnumber, sizeof(int));
   	if (BF_WriteBlock(fp, ari8mosblock) < 0){
		BF_PrintError("Error write in block");
		return -1;
	}
  	return 0;
}

void HP_GetAllEntries(int fp, char *fieldname, void *value){
	int counter = 0, ari8mosblock, recordnumber, i, j;
	void *arxiblock;
	Record record;

	ari8mosblock = BF_GetBlockCounter(fp) - 1;
	if (ari8mosblock < 0){
		BF_PrintError("Error count block");
		return;
	}
	for (i = 1; i <= ari8mosblock; i++){
		if (BF_ReadBlock(fp, i, &arxiblock) < 0){
			BF_PrintError("Error read block");
			return;
		}
		counter++;
  		memcpy(&recordnumber, arxiblock, sizeof(int));
  		for (j = 0; j < recordnumber; j++){	
			memcpy(&record, arxiblock + sizeof(int) + j * sizeof(Record), sizeof(Record));
			if (fieldname == NULL && value == NULL)
				printf("%d %s %s %c %s %d %c %d %d\n", record.id, record.name, record.surname, record.status[1], record.dateOfBirth, record.salary, record.section[1], record.daysOff, record.prevYears);
			else if(strcmp(fieldname, "id") == 0 && record.id == atoi(value))
				printf("%d %s %s %c %s %d %c %d %d\n", record.id, record.name, record.surname, record.status[1], record.dateOfBirth, record.salary, record.section[1], record.daysOff, record.prevYears);
			else if(strcmp(fieldname, "name") == 0 && strcmp(record.name,value) == 0)
				printf("%d %s %s %c %s %d %c %d %d\n", record.id, record.name, record.surname, record.status[1], record.dateOfBirth, record.salary, record.section[1], record.daysOff, record.prevYears);
			else if(strcmp(fieldname, "surname") == 0 && strcmp(record.surname,value) == 0)
				printf("%d %s %s %c %s %d %c %d %d\n", record.id, record.name, record.surname, record.status[1], record.dateOfBirth, record.salary, record.section[1], record.daysOff, record.prevYears);
			else if(strcmp(fieldname, "status") == 0 && strcmp(record.status,value) == 0)
				printf("%d %s %s %c %s %d %c %d %d\n", record.id, record.name, record.surname, record.status[1], record.dateOfBirth, record.salary, record.section[1], record.daysOff, record.prevYears);
			else if(strcmp(fieldname, "dateOfBirth") == 0 && strcmp(record.dateOfBirth,value) == 0)
				printf("%d %s %s %c %s %d %c %d %d\n", record.id, record.name, record.surname, record.status[1], record.dateOfBirth, record.salary, record.section[1], record.daysOff, record.prevYears);
			else if(strcmp(fieldname, "salary") == 0 && record.salary == atoi(value))
				printf("%d %s %s %c %s %d %c %d %d\n", record.id, record.name, record.surname, record.status[1], record.dateOfBirth, record.salary, record.section[1], record.daysOff, record.prevYears);
			else if(strcmp(fieldname, "section") == 0 && strcmp(record.section,value) == 0)
				printf("%d %s %s %c %s %d %c %d %d\n", record.id, record.name, record.surname, record.status[1], record.dateOfBirth, record.salary, record.section[1], record.daysOff, record.prevYears);
			else if(strcmp(fieldname, "daysOff") == 0 && record.daysOff == atoi(value))
				printf("%d %s %s %c %s %d %c %d %d\n", record.id, record.name, record.surname, record.status[1], record.dateOfBirth, record.salary, record.section[1], record.daysOff, record.prevYears);
			else if(strcmp(fieldname, "prevYears") == 0 && record.prevYears == atoi(value))
				printf("%d %s %s %c %s %d %c %d %d\n", record.id, record.name, record.surname, record.status[1], record.dateOfBirth, record.salary, record.section[1], record.daysOff, record.prevYears);
		}
	}
	printf("diavastikan %d blocks\n",counter);
	return;

}
