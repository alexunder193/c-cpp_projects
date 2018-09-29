#include <iostream>
#include <cstdlib>
#include "alysida.h"
#include <ctime>

using namespace std;
 
int main(int argc,char *argv[])
{
int N;
if(argc!=2)
{cout<<"Error"<<endl;
 return 0;
}

N=atoi(argv[1]);                        //ari8mos paiktwn ap thn grammh edolwn
Alysida alysida;
alysida.eisagogi(101,1,N);              //stelnw to 101 gia na nai h prwth id to 1 gia na nai h prwth 8esh kai to pli8os paiktwn
for(int i=0; i<N-1; i++)                  //ekteloume tin diadikasia N-1 fores
{long curtime=time(NULL);
 srand((unsigned int) curtime);
 int K=rand()% 10+1;
 for(int j=0; j<K; j++)                  //tyxaios ari8mos K xtuphma tumpanou
  alysida.hit(); 
 alysida.stop_tune();
 alysida.resume();
 alysida.print_chain();
}
//cout<<"\n"<<endl;
alysida.game_over();
//cout<<"\n"<<endl;
alysida.winner();
return 0;
}
