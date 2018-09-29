#include <iostream>
#include <cstdlib>
#include <ctime>
#include "alysida.h"
using namespace std;


Alysida::Alysida()                   //constructor oloi oi deiktes einai null
{
 trexon=NULL;
 header=NULL;
 temp=NULL;
}



void Alysida::eisagogi(int n,int m,int N)
{
int i;
for(i=0; i<=N; i++)                     //eisagwges einai oso kai to N
{List neos_komvos;
neos_komvos=new listnode;
neos_komvos->id=n;
neos_komvos->number=m;
neos_komvos->epomenos=NULL;
if(header!=NULL)                          //an h lista exei stoixeia
  {trexon=header;                         //trexon deixnei ston prwto komvo
   while(trexon->epomenos!=NULL)           //akoma dn exei ulopoii8ei h kuklikh o teleutaios einai null
     trexon=trexon->epomenos;
   trexon->epomenos=neos_komvos;             //pros8iki neou komvou sto telos
  }
else
    header=neos_komvos;                     // o neos komvos prwtos
n++;
m++;
}
trexon->epomenos=header;                 // o trexon pou einai o teleutaios deixnei sthn arxh ulopoihsh kuklikhs
plithos=N;                               //enhmerwsh plithous paiktwn
} 


void Alysida::print_chain()
{
trexon=header;
int i;
for(i=0; i<plithos; i++)
  {
   cout<< trexon->id<<endl;
   cout<< trexon->number<<endl;
   trexon=trexon->epomenos;
  }
}

void Alysida::stop_tune()
{
long curtime;                                       /////////diagrafh tyxaiou komvou//////////
int m;
curtime=time(NULL);
srand((unsigned int) curtime);
m=rand()%6+2;                                       //////////////////mexri edw///////////////
List del=NULL;        //o deikths pou 8a deixnei to stoixeio pou 8a diagrafei
temp=header;                                   //o temp deixnei to prwto stoixeio ths listas
for(int i=0; i<m; i++)                         //ulopoihsh ths tuxaias diagrafhs
 {temp=trexon;
  trexon=trexon->epomenos;
 }
del=trexon;                                    // o delete deixnei pleon ston komvo pou tyxaia epeleksa
trexon=trexon->epomenos;
temp->epomenos=trexon;
if(del==header)                                   // an einai to prwto stoixeio pou 8a diagrafei
 {header=header->epomenos;                         // o header deixnei sto epomeno
  temp=NULL;
 }
cout<< "o paiktis me tautothta "<< del->id<<" diagrafhke"<<endl;
delete del;
plithos --;             //meiwsh plithous paiktwn kata 1
}


void Alysida::hit()
{
temp=header;
for(int i=0; i<plithos; i++)
{
 int prosorinos=temp->number;                //o prosorinos krata thn 8esh tou prwtou komvou
 if(i!=0)                                // an den einai o prwtos komvos
  prosorinos++;
 temp=temp->epomenos;
 temp->number=prosorinos;                  // o epomenos komvos pairnei tin timh tou prohgoumenou +1
}
header=header->epomenos;                    // h arxh allazei deixnei sto epomeno
}


void Alysida::resume()
{
if(header->number != 1)
 header->number=1;                       // ekei pou deixnei o header prepei na einai panta h 8esh 1
temp=header;
for(int i=0; i<plithos-1; i++)
{
 int prosorinos=temp->number;             // prosorinos krata to number tou trexontos komvou
 temp=temp->epomenos;
 int prosorinos1=temp->number;            //prosorinos1 krata to number tou epomenou komvou
 if(prosorinos1-prosorinos != 1)           //prepei na nai diadoxikes oi 8eseis
  temp->number=prosorinos + 1;
}
}


void Alysida::game_over()
{
if(plithos==1)                                    //an exei meinei monos enas paikths
 cout<<"To paixnidi teleiwse"<<endl;
else
 cout<<"To paixnidi sunexizetai"<<endl;
}


void Alysida::winner()
{
cout<<"Nikhths einai o paiktis me ari8mo tautothtas: "<< header->id <<endl;      // xrisimopoiw to header afou otan meinei enas komvos to header 8a deixnei se afton
}
