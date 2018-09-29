#ifndef __TStoixeioyStoivas_H__
#define __TStoixeioyStoivas_H__
#include <stdio.h>
typedef int TStoixeioyStoivas;

void TSstoiva_setValue (TStoixeioyStoivas *target, TStoixeioyStoivas source);
int TSstoiva_readValue (FILE *from, TStoixeioyStoivas * Elem);
int TSstoiva_writeValue (FILE *to, TStoixeioyStoivas Elem);
#endif
