#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CS.h"
#include "BF.h"


int CS_CreateFiles(char **fieldNames)
{
 pliroforia temp;
 int flag=0; 
 void *arxiblockhd; //Auto pou epistrefei h ReadBlock tou headerinfo
 void *arxiblockarxeiwn; //Auto pou epistrefei h Read twn 9 arxeiwn
 int i,fd,filedesc; //fd anagnwristiko headerinfo, filedesc anagnwristiko arxeiou
 if(BF_CreateFile("header_info")<0)
      {BF_PrintError("Error creating file");
       return -1;
      }
     fd=BF_OpenFile("header_info");
     if(fd<0)
      {BF_PrintError("Error opening file");
       return -1;
      }
     if(BF_AllocateBlock(fd)<0)
      {BF_PrintError("Error allocate block");
       return -1;
      }
     if(BF_ReadBlock(fd,0,&arxiblockhd)<0)
      {BF_PrintError("Error read block");
       return -1;
      }
 for(i=0;i<=8; i++)
  {
   if(BF_CreateFile(fieldNames[i])<0)
    {BF_PrintError("Error creating file");
     return -1;
    }
   filedesc=BF_OpenFile(fieldNames[i]);
   if(filedesc<0)
    {BF_PrintError("Error opening file");
     return -1;
    }  
   strcpy(temp.name,fieldNames[i]); //struct me onoma pliroforia gia na mpenei sto headeinfo
   temp.anagnwristiko=filedesc;
   memcpy(arxiblockhd+i*sizeof(pliroforia),&temp,sizeof(pliroforia));
   if(BF_AllocateBlock(filedesc)<0)
    {BF_PrintError("Error allocate block");
     return -1;
    }
   if(BF_ReadBlock(filedesc,0,&arxiblockarxeiwn)<0)
    {BF_PrintError("Error read block");
     return -1;
    }
   switch (i) { //Ti graphei to prwto block twn arxeiwn
     case 0: strcpy(arxiblockarxeiwn,"rowld-id");
             break;
     case 1: strcpy(arxiblockarxeiwn,"rowld-name");
             break;
     case 2: strcpy(arxiblockarxeiwn,"rowld-surname");
             break;
     case 3: strcpy(arxiblockarxeiwn,"rowld-status");
             break;
     case 4: strcpy(arxiblockarxeiwn,"rowld-dateOfBirth");
             break;
     case 5: strcpy(arxiblockarxeiwn,"rowld-salary");
             break;
     case 6: strcpy(arxiblockarxeiwn,"rowld-section");
             break;
     case 7: strcpy(arxiblockarxeiwn,"rowld-daysOff");
             break;
     case 8: strcpy(arxiblockarxeiwn,"rowld-prevYears");
             break;
              }
   if(BF_WriteBlock(filedesc,0)<0)
    {BF_PrintError("Error write in block");
     return -1;
    }
   if(BF_CloseFile(filedesc)<0)
    {BF_PrintError("Error closing file");
     return -1;
    }
 }
if(BF_WriteBlock(fd,0)<0)
    {BF_PrintError("Error write in block");
     return -1;
    }
if(BF_CloseFile(fd)<0)
 {BF_PrintError("Error closing file");
  return -1;
 }
return 0;
}





int CS_OpenFile(char *header_info)
{pliroforia temp;
 int i,fd,j,filedesc;
 void *arxiblockhd;
 void *arxiblockarxeiwn;
 fd=BF_OpenFile(header_info);
 if(fd<0)
  {BF_PrintError("Error opening file"); 
   return -1;
  }
 if(BF_ReadBlock(fd,0,&arxiblockhd)<0)
  {BF_PrintError("Error read block");
   return -1;
  }
 for(i=0; i<=8; i++)
  {
   memcpy(&temp,arxiblockhd + i*sizeof(pliroforia),sizeof(pliroforia));
   filedesc=BF_OpenFile(temp.name);
   if(filedesc<0)
    {BF_PrintError("Error opening block");
     return -1;
    }
   temp.anagnwristiko=filedesc;
   
   memcpy(arxiblockhd +i*sizeof(pliroforia),&temp,sizeof(pliroforia));
   if(BF_ReadBlock(filedesc,0,&arxiblockarxeiwn)<0)
    {BF_PrintError("Error read block");
     return -1;
    }
   switch (i) {//Elegxos an einai CS arxeio.
    case 0: j=strcmp(arxiblockarxeiwn,"rowld-id");
            if(j!=0)
             {BF_PrintError("Error is not a CS file");
              return -1;
             }
            break;
   case 1: j=strcmp(arxiblockarxeiwn,"rowld-name");
            if(j!=0)
             {BF_PrintError("Error is not a CS file");
              return -1;
             }
            break;
   case 2: j=strcmp(arxiblockarxeiwn,"rowld-surname");
            if(j!=0)
             {BF_PrintError("Error is not a CS file");
              return -1;
             }
            break;
   case 3: j=strcmp(arxiblockarxeiwn,"rowld-status");
            if(j!=0)
             {BF_PrintError("Error is not a CS file");
              return -1;
             }
            break;
   case 4: j=strcmp(arxiblockarxeiwn,"rowld-dateOfBirth");
            if(j!=0)
             {BF_PrintError("Error is not a CS file");
              return -1;
             }
            break;
   case 5: j=strcmp(arxiblockarxeiwn,"rowld-salary");
            if(j!=0)
             {BF_PrintError("Error is not a CS file");
              return -1;
             }
            break;
   case 6: j=strcmp(arxiblockarxeiwn,"rowld-section");
            if(j!=0)
             {BF_PrintError("Error is not a CS file");
              return -1;
             }
            break;
   case 7: j=strcmp(arxiblockarxeiwn,"rowld-daysOff");
            if(j!=0)
             {BF_PrintError("Error is not a CS file");
              return -1;
             }
            break;
   case 8: j=strcmp(arxiblockarxeiwn,"rowld-prevYears");
            if(j!=0)
             {BF_PrintError("Error is not a CS file");
              return -1;
             }
            break;
             }
  }
 if(BF_WriteBlock(fd,0)<0)
  {BF_PrintError("Error write in block");
   return -1;
  }
 return fd;
}






int CS_CloseFile(int fd)
{
int i;
void *arxiblockhd;
pliroforia temp;
if(BF_ReadBlock(fd,0,&arxiblockhd)<0)
 {BF_PrintError("eroor reading block");
  return -1;
 }
for(i=0; i<=8; i++)
 {
  memcpy(&temp,arxiblockhd + i*sizeof(pliroforia),sizeof(pliroforia));
  if(BF_CloseFile(temp.anagnwristiko)<0)
   {BF_PrintError("eroor closing file");
    return -1;
   }
 }
if(BF_CloseFile(fd)<0)
   {BF_PrintError("eroor closing file");
    return -1;
   }
return 0;
}






int CS_InsertEntry(int fd,Record record)
{
pliroforia temp;
void *arxiblockhd;
void *arxiblockarxeiwn;
int i,filedesc,ari8mosblock,y,recordnumber;
int zero=0;
if(BF_ReadBlock(fd,0,&arxiblockhd)<0)
 {BF_PrintError("Error read block");
  return -1;
 }
for(i=0; i<=8; i++)
 {
  memcpy(&temp,arxiblockhd+i*sizeof(pliroforia),sizeof(pliroforia)); //Pairnei thn plhroforia tou headerinfo kai anoigei to analogo arxeio
  ari8mosblock=BF_GetBlockCounter(temp.anagnwristiko)-1;
  if(ari8mosblock<0)
   {BF_PrintError("Error count block");
    return -1;
   }
  if(ari8mosblock==0)
   {
    if(BF_AllocateBlock(temp.anagnwristiko)<0)
     {BF_PrintError("Error allocate block");
      return -1;
     }
    ari8mosblock=BF_GetBlockCounter(temp.anagnwristiko)-1;
    if(ari8mosblock<0)
     {BF_PrintError("Error count block");
      return -1;
     }
    if(BF_ReadBlock(temp.anagnwristiko,ari8mosblock,&arxiblockarxeiwn)<0)
     {BF_PrintError("Error read block");
      return -1;
     }
    memcpy(arxiblockarxeiwn,&zero,sizeof(int)); //Bazei 0 sthn arxh twn block
   }
  else
   {
    if(BF_ReadBlock(temp.anagnwristiko,ari8mosblock,&arxiblockarxeiwn)<0)
     {BF_PrintError("Error read block");
      return -1;
     }
   }
  memcpy(&recordnumber,arxiblockarxeiwn,sizeof(int));
  y=xwrosmetavlitis(i); //Kalei sunarthsh, epistrefei sto y to mege8os pou 8a apo8hkeutei sto arxeio
  if(recordnumber >= (BLOCK_SIZE-sizeof(int))/y);
   {
    if(BF_AllocateBlock(temp.anagnwristiko)<0)
     {BF_PrintError("Error allocate block");
      return -1;
     }
    ari8mosblock=BF_GetBlockCounter(temp.anagnwristiko)-1;
    if(ari8mosblock<0)
     {BF_PrintError("Error count block");
      return -1;
     }
    if(BF_ReadBlock(temp.anagnwristiko,ari8mosblock,&arxiblockarxeiwn)<0)
     {BF_PrintError("Error read block");
      return -1;
     }
    memcpy(arxiblockarxeiwn,&zero,sizeof(int));
    recordnumber=zero;
   }
  switch (i) {
    case 0: memcpy(arxiblockarxeiwn + sizeof(int)+ recordnumber*sizeof(int),&(record.id),sizeof(int));
            break;
    case 1: memcpy(arxiblockarxeiwn + sizeof(int)+ recordnumber*15*sizeof(char),&(record.name),15);
            break;
    case 2: memcpy(arxiblockarxeiwn + sizeof(int)+ recordnumber*20*sizeof(char),&(record.surname),20);
            break;
    case 3: memcpy(arxiblockarxeiwn + sizeof(int)+ recordnumber,&(record.status),1);
            break;  
    case 4: memcpy(arxiblockarxeiwn + sizeof(int)+ recordnumber*11*sizeof(char),&(record.dateOfBirth),11);
            break;
    case 5: memcpy(arxiblockarxeiwn + sizeof(int)+ recordnumber*sizeof(int),&(record.salary),sizeof(int));
            break;
    case 6: memcpy(arxiblockarxeiwn + sizeof(int)+ recordnumber,&(record.section),1);
            break;
    case 7: memcpy(arxiblockarxeiwn + sizeof(int)+ recordnumber*sizeof(int),&(record.daysOff),sizeof(int));
            break;
    case 8: memcpy(arxiblockarxeiwn + sizeof(int)+ recordnumber*sizeof(int),&(record.prevYears),sizeof(int));
            break;
             }
  recordnumber ++ ;
  memcpy(arxiblockarxeiwn,&recordnumber,sizeof(int));
  if(BF_WriteBlock(temp.anagnwristiko,ari8mosblock)<0)
     {BF_PrintError("Error write in  block");
      return -1;
     }
 }
return 0;
}







int xwrosmetavlitis(int i)
{
 switch (i) {
  case 0: return sizeof(int);
          break;
  case 1: return 15*sizeof(char);
          break;  
  case 2: return 20*sizeof(char);
          break;
  case 3: return sizeof(char);
          break;
  case 4: return 11*sizeof(char);
          break;
  case 5: return sizeof(int);
          break;
  case 6: return sizeof(char);
          break;
  case 7: return sizeof(int);
          break;
  case 8: return sizeof(int);
          break;
            }
}



void CS_GetAllEntries(int fd,char *fieldName,char *value)
{
 void *arxiblockhd;
 void *arxiblockarxeiwn;
 int temp1;
 char temp2[1];
 char temp3[15];
 char temp4[20];
 char temp5[11];
 int counter=0;
 int i,y,ari8mosblock,j,recordnumber,mege8os,k;
 pliroforia temp;
 if((fieldName==NULL)&&(value==NULL))
  { for(i=0; i<=8; i++)
     { y=BF_ReadBlock(fd,0,&arxiblockhd);
       if(y<0)
        {BF_PrintError("Error read block");
         return ;
        }
       memcpy(&temp,arxiblockhd + i*sizeof(pliroforia),sizeof(pliroforia));
       ari8mosblock=BF_GetBlockCounter(temp.anagnwristiko)-1;
       mege8os=xwrosmetavlitis(i);
       for(j=1; j<=ari8mosblock; j++)
        { if(BF_ReadBlock(temp.anagnwristiko,j,&arxiblockarxeiwn)<0)
           {BF_PrintError("Error read block");
            return ;
           }
        counter ++;
        memcpy(&recordnumber,arxiblockarxeiwn,sizeof(int));
        for(k=0; k<recordnumber; k++)
         { if(mege8os==sizeof(int))
            { memcpy(&temp1,arxiblockarxeiwn + sizeof(int) + k*sizeof(int),sizeof(int));
              printf("%d\n",temp1);
            }
           else if(mege8os==sizeof(char))
            { memcpy(&temp2,arxiblockarxeiwn + sizeof(int) + k*sizeof(char),sizeof(char));
              printf("%c\n",temp2[0]);
            }
           else if(mege8os==15*sizeof(char))
            { memcpy(&temp3,arxiblockarxeiwn + sizeof(int) + k*15*sizeof(char),15*sizeof(char));
              printf("%s\n",temp3);
            }
           else if(mege8os==20*sizeof(char))
            { memcpy(&temp4,arxiblockarxeiwn + sizeof(int) + k*20*sizeof(char),20*sizeof(char));
              printf("%s\n",temp4);
            }
           else if(mege8os==11*sizeof(char))
            { memcpy(&temp5,arxiblockarxeiwn + sizeof(int) + k*11*sizeof(char),11*sizeof(char));
              printf("%s\n",temp5);
            }
         }
        }
        
     }
  }
 printf("diavastikan %d blocks \n",counter);
 return;
}

