#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "typos_stoixeiouDDA.h"
#include "Words.h"
#include "BST_pointer-Recursive.h"
typedef struct RecWords 
{
     typos_deikti WordsRiza; 	/* to Words apoteleitai apo to DDA */
     float InsertTime [10];   /* xronoi eisagvghs ana 1024, 2048,...*/
     float CheckTime;         /* xronos elegxou */
     float DiadromhTime;	  /* xronos diadromhs */
} RecWords;

typosWords dhmiourgia_Words()
{  
   typosWords WordsNew=malloc(sizeof(RecWords));
    Tree_dimiourgia(&(WordsNew->WordsRiza));
   return WordsNew;         
}

void katastrofh_Words(typosWords * Wordsptr)
{
   Tree_katastrofi(&(*Wordsptr)->WordsRiza);
   free(*Wordsptr);
   *Wordsptr=NULL;
}

void InsertWord(typosWords Words, char * w)
{
   int error;
   TStoixeioyTree komvos;
   strcpy(komvos.word,w);                 /*antigrafei sto struct pou 8a eisagoume sto dentro to w */
   komvos.frequency=0;                  /*sthn arxh ka8e l;eksi exei suxnothta emfanisis mhden*/
   Tree_eisagogi(&(Words->WordsRiza),komvos,&error);    /*kalw tin eisagwgi gia na mpei o komvos sto dda */
/*   if(error==1)
     printf("Den perastike o komvos sto DDA\n");
   else
     printf("o komvos perastike\n"); */ 
}

void CheckWord(typosWords Words, char * w)
{  int flag;
   flag=0;
   typos_deikti riza;
   TStoixeioyTree komvos;
   strcpy(komvos.word,w);                 /*antigrafei sto struct pou 8a eisagoume sto dentro to w */
   komvos.frequency=0;                  /*sthn arxh ka8e l;eksi exei suxnothta emfanisis mhden*/
   Tree_anazitisi(Words->WordsRiza,komvos,&riza,&flag);    /*kalw tin anazitisi gia na psaksei gia to stoixeio sto dentro*/
   if(flag==1)
     (komvos.frequency)++;                /*simaia gia to an vrethike to stoixeio */
  /*  printf("H lexh  vrethke\n");
              }
   else
    printf("h lexh den vrethke\n"); */
}

void ShowCommonWords(FILE *out, typosWords Words)
{
 typos_deikti riza;
 riza=Words->WordsRiza;
 inorder(riza,out);    /*sunarthsh pou ektupwnei tis koines lekseis*/
}

/* praxeis poy diaxeirizontai toys xronoys */

void SetInsertTime(typosWords Words, float time, int position)
{
	
		 Words->InsertTime[position]=time;

}

void SetCheckTime(typosWords Words,float time)
{
 Words->CheckTime=time;
}

void SetDiadromhTime(typosWords Words, float time)
{	
	 
		 Words->DiadromhTime=time;
	
}

void PrintTimes(FILE *out, typosWords Words)
{
int i;
printf("\n");
for(i=0;i<=5; i++)           /*apo 0 ews 5 gt exoume 1024 2048 4096....6 times mexri to plithos twn leksewn*/
 printf("%f \n",Words->InsertTime[i]);
printf("\n");
printf("%f\n",Words->CheckTime);
printf("%f\n",Words->DiadromhTime);
}


void inorder(typos_deikti riza,FILE *out)
{typos_deikti apaidi,dpaidi;        /*h parametros pou 8a epistrepsei h apaidi dpaidi antistoixa*/
 int error;
 TStoixeioyTree perkomvou;         /*h parametros pou 8a epistrepsei h treeperiexomeo*/
 if(riza!=NULL)                    /*ousiastika ekteleitai h endodiataksi me tin voithia tis apaidi dpaidi kai periexomeno*/
 {
  Tree_apaidi(riza,&apaidi,&error);   
  inorder(apaidi,out);
  Tree_periexomeno(apaidi,&perkomvou,&error);
  if(perkomvou.frequency>1)
   TStree_writeValue(out,perkomvou);      /*ektipwnetai sto out.txt oi koines lekseis*/
  Tree_dpaidi(riza,&dpaidi,&error);
  inorder(dpaidi,out);
 }
}  

