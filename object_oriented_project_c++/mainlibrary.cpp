#include <iostream>
#include <cstdlib>
#include <ctime>
#include "vivliothiki.h"
using namespace std;

int main(int argc,char*argv[])
{
int K,L,m,n,i;
bool elegxos;              //xreiazetai gia na ektupwnei mhnumata la8ous 
long curtime,curtime1;     //gia tis arxikopoihseis ths srand
if(argc!=3)                 //ta orismata einai 3
 {cout<<"ERROR"<<endl;
  return 0;
 }
K=atoi(argv[1]);            //ari8mos topo8ethshs kai apomakrunshs vivliou
L=atoi(argv[2]);            //xwrhtikothta rafiwn
Library library(0,0,0,0,0,0);        //arxikopoiw ola ta rafia me ari8mo vivliwn 0
for(i=0;i<K; i++)
 {curtime=time(NULL);
  srand((unsigned int) curtime);
  m=rand()%5 + 1;
  elegxos=library.placebook(L,m);
  if(elegxos==false)
   cout<<"To rafi einai gemato den xwraei allo vivlio"<<endl;
 }
for(i=0;i<K; i++)
  {curtime1=time(NULL);
   srand((unsigned int) curtime1);
   n=rand()%5 + 1;
   elegxos=library.takebook(n);
   if(elegxos==false)
    cout<<"To rafi einai adeio den mporeis na pareis vivlio apo edw"<<endl;
  }
return 0;
}
