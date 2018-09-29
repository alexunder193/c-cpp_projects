

#ifndef __STACK__ 
#define __STACK__

#define PLITHOS 100 
#include "TStoixeioyStoivas.h" 



typedef struct 
{   int korifi;        
	TStoixeioyStoivas pinakas[PLITHOS];  
} TStoivas;



  
void Stoiva_dimiourgia(TStoivas *stoiva);


int  Stoiva_keni(TStoivas stoiva);


void Stoiva_PopValue(TStoivas stoiva,TStoixeioyStoivas *stoixeio,int *ypoxeilisi);
void Stoiva_PopState(TStoivas *stoiva,int *ypoxeilisi);
void Stoiva_othisi(TStoivas *stoiva,TStoixeioyStoivas stoixeio,int *yperxeilisi);

#endif 
