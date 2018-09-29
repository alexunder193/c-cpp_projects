#ifndef __TSTOIXEIOYLISTAS_H__
#define __TSTOIXEIOYLISTAS_H__
#define CPLITHOS 15
#include <stdio.h>
#include <string.h>

typedef struct TStoixeioyListas                               /*dimiourgia tou struct pou pairnei onoma epitheto ari8mo se symboloseires*/
{   char Name[25];
    char Surname[25];
    char Number[25];
}  TStoixeioyListas;

int TSlist_iso(TStoixeioyListas Elem1, TStoixeioyListas Elem2);
int TSlist_mikrotero(TStoixeioyListas Elem1, TStoixeioyListas Elem2);
int TSlist_megalytero(TStoixeioyListas Elem1, TStoixeioyListas Elem2);

void TSlist_setValue (TStoixeioyListas *target, TStoixeioyListas source);
int TSlist_readValue (FILE *from, TStoixeioyListas * Elem);
int TSlist_writeValue (FILE *to, TStoixeioyListas Elem);
#endif
