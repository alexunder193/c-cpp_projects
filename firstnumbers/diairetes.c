#include <stdio.h>
main()
{
int n,s,i,ip,piliko,m,k;
for(n=2; n<=400000; n++){ 
 s=n;
 for(m=1; m<=6; m++){
 i=1;
 while(i*i<=n){
   ip=n%i;
   if(ip==0){
     s=s+i;
     piliko=n/i;
     if(piliko!=i)
       s=s+piliko;
            }
   i=i+1;
              }
 if(s%n==0){
   k=s/n;
   if(m==1 && k!=2)
    printf("%d is a (%d-%d)-perfect number,that is a multiperfect number \n",n,m,k);
   else if(m==1 & k==2)
    printf("%d is a (%d-%d)-perfect number,that is perfect number \n",n,m,k);
   else if(k==2 &&  m==2)
    printf("%d is a (%d-%d)-perfect number,that is superperfect number \n",n,m,k);
   else
    printf("%d is a (%d-%d)-perfect number \n",n,m,k);
           }
 n=s;
 
                    }
                       }
}  

                    
                    


