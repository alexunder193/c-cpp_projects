#include <stdio.h>
#include <ctype.h>
#define MINLENGTH 9
#define MINCRITERIA 3
int main(void) {
int ch,flag=0,line=0,x,y,k=0,l=0,z,m=0,w,n=0,p=0,s=0,t,flag2=0,temp1=0,temp2=0,temp3=1000,b=0,flag3=0,d1=0,d2=0,d3=0,d4=0,flag4=0,c=0;
while((ch=getchar())!=EOF){
  if(flag==0){                                                            /*diakoptis gia na ektiponei to line*/
   line++;
   printf("Line %d: Password ''",line);
   flag=1;
             }
  if(ch==10){                                                            /*otan patas enter=10 ston ascii ektipwnei an o kwdikos einai valid h invalid*/
    if(flag2==1){
      printf("'' is invalid (unecceptable character)\n");
      flag=0;                                                           /*midenizontai oles oi metavlites gia na patithei ap to xristi o epomenos kwdikos*/
      k=0;
      l=0;
      m=0;
      n=0;
      p=0;
      flag2=0;
      s=0;
      continue; }                                                  /*wste na einai mono mia katioria invalid*/
    if(p<MINLENGTH){
      printf("'' is invalid (too short)\n");
      flag=0;
      k=0;
      l=0;
      m=0;
      n=0;
      p=0;
      flag2=0;
      s=0;
      continue;    }
    if(b==2)                                                      /*diakoptis gia to kritirio 5*/
     flag3=1;
    if(flag3==0)
       s++;
    flag3=0;
    if(c==2)                                                     /*diakoptis gia to kritirio 6*/
      flag4=1;
    if(flag4==0)
       s++;
    flag4=0;
    c=0;
    if(k>=1)                                    /*metritis s pou metraei posa kritiria isxioun*/
     s++;
    if(l>=1)
     s++;
    if(m>=1)
     s++;
    if(n>=1)
     s++;
    if(s<MINCRITERIA){
      printf("'' is invalid (few criteria)\n");
      flag=0;
      k=0;
      l=0;
      m=0;
      n=0;
      s=0;
      flag2=0;
      p=0;
      continue;}
    if(s==6 && p>=2*MINLENGTH)
      printf("'' is valid (very strong)\n");
    if(s==6 && p<2*MINLENGTH)
      printf("'' is valid (strong)\n");
    if(s==5)
      printf("'' is valid (fair)\n");
    t=k+l;
    if(s<=4){
      if(t>=m)
        printf("'' is valid (weak)\n");
      else
        printf("'' is valid (very weak)\n");
            }
    flag=0;
    k=0;
    l=0;
    m=0;
    n=0;
    p=0;
    flag2=0;
    s=0;
    t=0;
    continue;
}
  if(ch>='!' && ch<='~'){                                  /*edw mpainei mono otan h eisodos ap thn getchar einai gramma eidikos xar h ari8mos*/
    p=p+1;
    x=isupper(ch);                                         /*kritirio 1*/
    if(x!=0)
     k=k+1;
    y=islower(ch);                                        /*kritirio 2*/
    if(y!=0)
     l=l+1;
    z=isdigit(ch);                                       /*kritirio 3*/
    if(z!=0)
     m=m+1;
    w=ispunct(ch);                                       /*kritirio 4*/
    if(w!=0)
     n=n+1;
    putchar(ch);
    if(flag3==0){                                        /*kritirio 5*/
      if(p==1)
        temp1=ch;
      else if(p==2)
        temp2=ch;
      else{
        temp3=temp1;
        temp1=temp2;
        temp2=ch;
           }
    if(b==2)
      if(temp1!=temp2)
         flag3=1;
    b=0;
    if(p>=2){
      if(temp1==temp2)
       b=1;
    if(b==1)
     if(temp1!=temp3)
        b=2;}
}
if(ispunct(ch)==0){                             /*elegxei wste nampainoun mono grammata mikra megala kai ari8moi*/
  if(flag4==0){                                  /*kritirio 6*/
    if(p==1)
      d1=ch;
    else if(p==2)
      d2=ch;
    else if(p==3)
      d3=ch;
    else{
     d4=d1;
     d1=d2;
     d2=d3;
     d3=ch;
        }
   if(c==2)
    if(d2!=(d3-1))
      flag4=1;
   c=0;
   if(p>=3)
     if(d1==(d2-1))
       if(d2==(d3-1))
         c=1;
   if(c==1)
    if(d4!=(d1-1))
     c=2;
      }
}               
}
  else{                          /*otan mpainei mi apodektos xaraktiras p.x keno*/
    flag2=1;
    p=p+1;
    putchar(ch);
       }
}
return 0;
}
