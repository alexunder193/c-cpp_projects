#include <iostream>
#include "vivliothiki.h"
using namespace std;

////////////////////VASI//////////////////
Vasi::Vasi()
{
 cout<<"I just constructed a Vasi"<<endl;
}

Vasi::~Vasi()
{
 cout<<"I just deleted a Vasi  "<<endl;
}
//////////////////////////////////////////

////////////////////RAFI//////////////////

Rafi::Rafi(int c)
{
 number=c;                                        ///////enimerwsh ths xwrhtikothtas ttu rafiou
 cout<<"I just constructed a Rafi"<<endl;
}

Rafi::~Rafi()
{
 cout<<"I just deleted a Rafi  "<<endl;
}

bool Rafi::placebook(int L)
{
 if(number<L)                               /////ri8mos vivliwn mikroteros tou megistou plithous pou xwraei//
  {number++;
   return true;
  }
 else
  return false;
}

bool Rafi::takebook()
{
 if(number==0)                               /////////an to rafi einai adeio/////
  return false;
 else
  {number--;
   return true;
  }
}

///////////////////////////////////////////

/////////////////DOULAPI///////////////////
Doulapi::Doulapi(int a,int b):panw(a),katw(b)    /////kaleitai o contructor twn 2 rafiwn prin anoiksei h agkulh.to kanw wste na mn kalestei o default constr
{
cout<<"I just constructed a Doulapi"<<endl;
}

Doulapi::~Doulapi()
{
cout<<"I just Deleted a Doulapi "<<endl;
}

bool Doulapi::placebook(int L,int tyxaia)
{
  bool k;
  if(tyxaia==4)                ///h tuxaia einai h metavliti thsn rand pou stelnei h main an einai 4 h 5 vazei vivlia sto doulapi
    {k=panw.placebook(L);
     return k;
    }
  else
    {k=katw.placebook(L);
     return k;
    }
}

bool Doulapi::takebook(int tyxaia)
{
  bool k;
  if(tyxaia==4)
   {k=panw.takebook();        ///h tuxaia einai h metavliti thsn rand pou stelnei h main an einai 4 h 5 vgazei vivlia ap to doulapi
    return k;
   }
  else
   {k=katw.takebook();
    return k;
   }
}    
/////////////////////////////////////////////

/////////////VIVLIOTHIKI/////////////////////

Library::Library(int a,int b,int c, int d, int e, int f):doulapi(a,b),rafi1(c),rafi2(d),rafi3(e)       ////kaleitai constructor doulapiou kai rafiwn
{
counter=f;                                       //enhmerwnetai o sunolikos ari8mos vivliwn ths vivliothikis
cout<<"I just constructed a Library"<<endl;
}

Library::~Library()
{
cout<<"I just Deleted a Library"<<endl;
}

bool Library::placebook(int L,int tyxaia)
{
 bool b;
 if(tyxaia==1)                 //an tyxaia 1 vazei rafi1 an 2 vazei rafi 2 an 3 vazei rafi 3 an 4 h 5b vazei doulapi
   {b=rafi1.placebook(L);
    if(b==true)
     counter ++;                //an to rafi dn einai gemato kai mpei vivlio o sunolikos ari8mos vivliwn ths vivliothikis ginetai +1
    return b;
   }
 else if(tyxaia==2)
   {b=rafi2.placebook(L);
    if(b==true)
     counter ++;
    return b;
   }
else if(tyxaia==3)
   {b=rafi3.placebook(L);
    if(b==true)
     counter ++;
    return b;
   }
else
   {b=doulapi.placebook(L,tyxaia);
    if(b==true)
     counter ++;
    return b;
   }
}

bool Library::takebook(int tyxaia)
{
 bool b;
 if(tyxaia==1)             //an tyxaia 1 pairnei apo rafi1 an 2 apo rafi2 an 3 apo rafi 3 an 4 h 5 apo doulapi
   {b=rafi1.takebook();
    if(b==true)            //an kapoio rafi pou pame na paroume vivlio dn einai adeio oloklirwnetai h energeia kai sunolikos ari8mos vivliwn -1
     counter --;
    return b;
   }
 else if(tyxaia==2)
   {b=rafi2.takebook();
    if(b==true)
     counter --;
    return b;
   }
else if(tyxaia==3)
   {b=rafi3.takebook();
    if(b==true)
     counter --;
    return b;
   }
else
   {b=doulapi.takebook(tyxaia);
    if(b==true)
     counter --;
    return b;
   }
}

/////////////////////////////////////////////////
