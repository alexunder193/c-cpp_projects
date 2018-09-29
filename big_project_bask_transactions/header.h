#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct akmi *dakmis;                //oi akmes 
typedef struct korifi *dkorifis;            //oi logariasmoi
typedef struct closed *dclosed;             //i lista episkeptomenon kombon gia conn traceflow

typedef struct akmi
 {
  float weight;            //poso pou eiserxetai-ekserxetai
  dkorifis list;           //deiktis se logariasmo N
  dakmis next;             //deiktis stin epomeni akmi
 }akmi;
 
typedef struct korifi
 {
  int salary;             //onoma logariasmou
  float in;               //sunolo eiserxomenon rown 
  float out;              //sunolo ekserxomenon rown
  dakmis list;             //deiktis se akmi       
  dkorifis next;            //deiktis se epomeni korifi
 }korifi;
 
 
 typedef struct closed
  {
  	int salary;               //apothikeusi ari8mou logariasmou
  	dclosed next;             //epomenos kombos 
  }closed;
  
  int function(int,int);           //Hash function
