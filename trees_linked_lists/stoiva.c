#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define PLITHOS 100
#include "stoiva.h"
 
 struct alex{
    int korifi;
    int pinakas[PLITHOS];
            };
 typos_stoivas dimiourgia()
  {typos_stoivas stoiva=malloc(sizeof(typos_stoivas));
   stoiva->korifi=-1;
   return stoiva; 
  }
int main(void)
{


int keni(typos_stoivas stoiva)
  {                                                               /*ean einai adeia 8a epistrepsei 1*/
   return (stoiva->korifi==-1);
 }


void exagogi(const typos_stoivas stoiva,int* const stoixeioptr)
  {
if((stoiva->korifi)==-1)
  printf("i stoiva einai adeia");
else{
  (*stoixeioptr)=stoiva->pinakas[stoiva->korifi];
  (stoiva->korifi)--;
    }
  }  



void othisi(const typos_stoivas stoiva,int stoixeio)
 {
if((stoiva->korifi)==PLITHOS-1)
 printf("h stoiva einai gemati");
else{
  stoiva->korifi ++;
  stoiva->pinakas[stoiva->korifi]=stoixeio;
    }
 }

}
