#include <iostream>
#include <cstdlib>
#include <ctime>
#include "balls.h"
using namespace std;

Ball::Ball()
{
 loseball=0;
 breakball=0;
}

int Ball::tupos(int a,int b,int c)              //an maxdurability =L1 einai basket l2 einai tennis L3 einai pingpong//
{
 if(maxdurability==a)              
  return 1;
 else if(maxdurability==b)
  return 2;
 else
  return 3;
}


////////////////////////////////BASKETBALL//////////////////////
int Basketball::sum1=0;                          //static dilwsh
Basketball::Basketball(int a)
{
 durability=a;
 maxdurability=a;
 sum1++;                            //ston constructor auksanetai o static metrhths analoga me tin dhmiourgia neou antikeimenou
}


void Basketball::hit()
{
if(loseball==1)
 cout<<"You cannot hit a hidden ball"<<endl;
else{
int n=rand() % 8;                    //pithanothta 1/8 na xa8e mia mpala
if(n==2)
 loseball=1;
if(loseball==1)
 cout<<"You cannot hit a hidden ball"<<endl;
else 
 {
  if(durability>0)
   {cout<<"Tsaf"<<endl;
    durability=durability--;
   }
  else 
    cout<<"Plof"<<endl;
 }
}
}


void Basketball::rest()        //h rets stin basket dn kanei tipota
{
}



void Basketball::meiosi()                //kaleitai gia na meiwsei ton static metrhth analoga me to an h mpala einai f9armenh eksafanismenh spasmenh
{
 if(loseball==1 || breakball==1 || durability<=0)
  sum1--;
}


int Basketball::epistrofi()               //epistrefei to poses mpales basket uparxoun ston array
{
 return sum1;
}

//////////////////////TENNIS////////////////////////////////////
int Tennis::sum2=0;
Tennis::Tennis(int b)
{
 durability=b;
 maxdurability=b;
 sum2++;                             //aukshsh gia ka8e nea kainourgio antikeimeno mpala tennis
}


void Tennis::hit()
{
if(loseball==1)
 cout<<"You cannot hit a hidden ball"<<endl;
else{
int n=rand() % 8 ;
if(n==2)
 loseball=1;
if(loseball==1)
 cout<<"You cannot hit a hidden ball"<<endl;
else
 {
  if(durability>0)
   {cout<<"Tsaf"<<endl;
    durability=durability-5;
   }
  else
    cout<<"Plof"<<endl;
 }
}
}


void Tennis::rest()
{
 durability=durability+3;
}


void Tennis::meiosi()
{
 if(loseball==1 || breakball==1 || durability<=0)
  sum2--;
}


int Tennis::epistrofi()
{
 return sum2;
}

/////////////////////PINGPONG///////////////////////////////////
int Pingpong::sum3=0;
Pingpong::Pingpong(int c)
{
 durability=c;
 maxdurability=c;
 sum3++;                  //aukshsh tou static metrhth gia ka8e neo antikeimeno pingpong
}



void Pingpong::hit()
{
if(loseball==1 || breakball==1)
 {if(loseball==1)
   cout<<"You cannot hit a hidden ball"<<endl;
  else
   cout<<"H mpala espase"<<endl;
 }
else{
int n=rand() % 8;          //pithanotita na xa8ei h mpala1/8
int m=rand() % 14;         //pithanothta na spsei h mpala 1/14
if(n==2)
 loseball=1;
if(m==3)
 breakball=1;
if(loseball==1)
 cout<<"You cannot hit a hidden ball"<<endl;
else
 {if(breakball==1)
   cout<<"H mpala espase"<<endl;
  else
   {
    if(durability>0)
     {cout<<"Tsaf"<<endl;
      durability=durability--;
     }
    else
     cout<<"Plof"<<endl;
   }
 }
}
}


void Pingpong::rest()
{
durability=durability+1;
}



void Pingpong::meiosi()
{
 if(loseball==1 || breakball==1 || durability<=0)
  sum3--;
}


int Pingpong::epistrofi()
{
 return sum3;
}

