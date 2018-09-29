

#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"



void Stoiva_dimiourgia(TStoivas *stoiva)
{
	stoiva->korifi = -1;
}

int  Stoiva_keni(TStoivas stoiva)
{
	return (stoiva.korifi == -1);
}

void Stoiva_PopValue(TStoivas stoiva,TStoixeioyStoivas *stoixeio,int *ypoxeilisi)          /*h 1h sunarthshs pou antikathista thn exagogi*/ 
{
	if(Stoiva_keni(stoiva))                          
          *ypoxeilisi=1;
        else
        {   *ypoxeilisi=0;
              TSstoiva_setValue(stoixeio,stoiva.pinakas[stoiva.korifi]);
        }
}

void Stoiva_PopState(TStoivas *stoiva,int *ypoxeilisi)                                     /*h 2h sunarthsh pou antika8ista tin exagogi*/
{
       if(Stoiva_keni(*stoiva))
         *ypoxeilisi=1;
       else
       {   *ypoxeilisi=0;
             stoiva->korifi--;
       }
}




void Stoiva_othisi(TStoivas *stoiva,TStoixeioyStoivas stoixeio,int *yperxeilisi)
{  
	if (stoiva->korifi == PLITHOS -1)
    	*yperxeilisi = 1;
	else
	{   *yperxeilisi = 0;
		stoiva->korifi++;
		TSstoiva_setValue(&(stoiva->pinakas[stoiva->korifi]), stoixeio);
	}
}

