#ifndef __TStoixeioyTree__ 
#define __TStoixeioyTree__
#include <stdio.h>
#include <string.h>
typedef struct dedomena {
        char word[20]; /* a word */
        int frequency; /* metrhths poses fores anazhthuhke h lexi */
} TStoixeioyTree;

/* basikes sygkriseis gia xrhsh sthn eisagcgh-diagarfh-anazhthsh se DDA */
int TStree_iso(TStoixeioyTree Elem1, TStoixeioyTree Elem2);
int TStree_mikrotero(TStoixeioyTree Elem1, TStoixeioyTree Elem2);
int TStree_megalytero(TStoixeioyTree Elem1, TStoixeioyTree Elem2);

void TStree_setValue (TStoixeioyTree *target, TStoixeioyTree source);
int TStree_readValue (FILE *from, TStoixeioyTree * Elem);
int TStree_writeValue(FILE *to, TStoixeioyTree Elem);
#endif
