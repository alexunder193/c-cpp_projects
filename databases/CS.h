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

typedef struct pliroforia{
   char name[20];
   int anagnwristiko;
   }pliroforia;

void CS_GetAllEntries(int fd,char *fieldName,char *value);
int CS_CreateFile(char **fieldNames);
int CS_OpenFile(char *header_info);
int CS_CloseFile(int fd);
int CS_InsertEntry(int fd,Record record);
int xwrosmetavlitis(int i); 
