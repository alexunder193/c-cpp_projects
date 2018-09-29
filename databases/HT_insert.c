int HT_InsertEntry(HT_info header_info,Record record)
{
int x, recordnumber;

if(header_info->attrType=='i')
 {
  if(strcmp(header_info->attrName,"id")==0)
    x=hash(record.id);
  else if(strcmp(header_info->attrName,"salary")==0)
    x=hash(record.salary);
  else if(strcmp(header_info->attrName,"daysOff")==0)
    x=hash(record.daysOff);
  else
    x=hash(record.prevYears);
 }
else
 {
  if(strcmp(header_info->attrName,"name")==0)
    x=djb_hash(record.name,strlen(record.name));
  else if(strcmp(header_info->attrName,"surname")==0)
    x=djb_hash(record.surname,strlen(record.surname));
  else if(strcmp(header_info->attrName,"status")==0)
    x=djb_hash(record.status,strlen(record.status));
  else if(strcmp(header_info->attrName,"dateOfBirth")==0)
    x=djb_hash(record.dateOfBirth,strlen(record.dateOfBirth));
  else
    x=djb_hash(record.section,strlen(record.section));
 }
y=pow(2,header_info->depth);
x=(x%y)+ 2;
if(BF_ReadBlock(header_info->fp,x,&arxiblock)<0)
 {BF_PrintError("Error read block");
  return -1;
 }
memcpy(&recordnumber, arxiblock + sizeof(int), sizeof(int));
if (recordnumber < BLOCK_SIZE - (2 * sizeof(int) / sizeof(record)))
{memcpy(arxiblock + 2 * sizeof(int) + recordnumber * sizeof(Record), &record, sizeof(Record));
 recordnumber++;
 memcpy(arxiblock + sizeof(int), &recordnumber, sizeof(int));
if (BF_WriteBlock(header_info->fp, x) < 0){
	BF_PrintError("Error write in block");
	return -1;
}
}
else
 {p=0;
 if(BF_ReadBlock(header_info->fp,1,&arxiblock)<0)
 {BF_PrintError("Error read block");
  return -1;
 }
 for (i=0;i<y;i++){
 memcpy(&temp,arxiblock + sizeof(int) + i*sizeof(Record),sizeof(int));
 if(temp==x)
   p++;
 }
 if(p>1){
   header_info->depth ++;
   y=pow(2,header_info->depth);
   for(i=0; i<y/2; i++){
 i=i+2;
 memcpy(arxiblock +sizeof(int) +(y/2)*sizeof(int) +(i-2)*sizeof(int),&i,sizeof(int));
i=i-2;
}
memcpy(arxiblock,header_info->depth,sizeof(int));
}
}
return 0;
}
