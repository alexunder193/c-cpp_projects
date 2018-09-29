#include <iostream>
#include <cstdlib>
#include <ctime>
#include "balls.h"

using namespace std;
int main(int argc,char *argv[])
 {
if(argc!=6)
 {cout<<"ERROR"<<endl;
  return 0;
 }
int L1=atoi(argv[1]);
int L2=atoi(argv[2]);
int L3=atoi(argv[3]);
int N=atoi(argv[4]);
int K=atoi(argv[5]);

Ball **array;
array=new Ball*[N];                       //pinakas deiktwn pou deixnei sta antikeimena
long curtime=time(NULL);
srand((unsigned int) curtime);
for(int i=0; i<N; i++)
{int n=rand() % 3; 
 if(n==0)
  array[i]=new Basketball(L1);                  //constructor basket 
 else if(n==1)
  array[i]=new Tennis(L2);                      //constructor tennis
 else
  array[i]=new Pingpong(L3);                    //constructor pingpong
}



for(int j=0; j<K; j++)             //K kukloi
 {int r=rand() % N;                //rand se poio keli 8a ginei hit
  array[r]->hit();
  for(int d=0; d<N; d++)           //sta upoloipa kelia ektos tou r rest
   {if(d==r)
     continue;
    array[d]->rest();
   }
 }

for(int p=0; p<N; p++)              //epanalipsi mou trexei olon to pinaka kai meiwnei tous static metrhtes
  array[p]->meiosi();



int *pinakas;          
pinakas=new int[N];                   //dimiourgia pinaka me ola ta plith tou kathe typou mpalwn
for(int n=0; n<N; n++)
 {int a=(array[n]->epistrofi());        //epistrefei sto a to plithos kai to vazei ston pinaka
 pinakas[n]=a;
 }

int max=pinakas[0];                        //euresh megistou stoixeiou pinaka
int thesi=0;                               //tesi megistou stoixeiou
for(int e=1; e<N; e++)
{
 if(pinakas[e]>max)
  {max=pinakas[e];
   thesi=e;
  }
}

int z=array[thesi]->tupos(L1,L2,L3);           //stin thesh tou megistou stoixeiou psaxnw an einai to maxdurability L1 L2 L3 kai epistrefw typo mpalas me tin sunarthsh tupos
if(z==1)
 cout<<"Tha paixtei Basketball"<<endl;
else if(z==2)
 cout<<"Tha paixtei Tennis"<<endl;
else
 cout<<"Tha paixtei Pingpong"<<endl;


return 0;
 }
