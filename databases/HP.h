typedef struct Record{
  int id;
  char name[15];
  char surname[20];
  char status[1];
  char dateOfBirth[10];
  int salary;
  char section[1];
  int daysOff;
  int prevYears;
  }Record ;



int HP_CreateFile(char *filename);
int HP_OpenFile(char *filename);
int HP_CloseFile(int fp);
int HP_InsertEntry(int fp,Record record);
void HP_GetAllEntries(int fp,char *fieldname,void *value);
