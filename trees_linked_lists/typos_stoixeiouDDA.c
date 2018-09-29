#include "typos_stoixeiouDDA.h"


int TStree_iso(TStoixeioyTree s1, TStoixeioyTree s2)
{
 return (strcmp(s1.word,s2.word)==0);	
}

int TStree_mikrotero(TStoixeioyTree s1, TStoixeioyTree s2)
{
 return (strcmp(s1.word,s2.word)<0);		
}

int TStree_megalytero(TStoixeioyTree s1, TStoixeioyTree s2)
{
 return (strcmp(s1.word,s2.word)>0);		
}

void TStree_setValue (TStoixeioyTree *target, TStoixeioyTree source)
{
 strcpy(target->word,source.word);       /*antigrafei leksi*/
 target->frequency=source.frequency;    /*antigrafei fores pou emfanistike*/
}
 
int TStree_readValue (FILE *from, TStoixeioyTree * Elem)       /*diavazei ap to arxeio pou stelnoume */
{
     int fd;
     fd=fscanf(from,"%s ",&(Elem->word));    
     if(fd==1)
      return 1;
     else
      return 0;  
}

int TStree_writeValue(FILE *to,TStoixeioyTree Elem)         /*ektipwnei sto arxeio pou 8eloume*/
{
 int fd;
 fd=fprintf(to, "%s", Elem.word);
 fprintf(to, "%s","\n");
 return fd;
}
