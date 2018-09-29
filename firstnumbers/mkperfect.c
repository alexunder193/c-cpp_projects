 #include <stdio.h>
#define MAXNUM 400000
#define MAXM 6
main()
{
int n,s,m,temp,k,i,piliko,ip,p,a,b,c,flag,district;
float pososto;
a=0;                                                    /*metrhths gia multiperfect numbers */
b=0;                                                   /*metrhths gia perfect perfect numbers */
c=0;                                                   /*metrhths gia superperfect numbers */ 
p=0;                                                     /*o metrhths pou vriskei olous tous mk perfect ari8mous */
district=0;                                              /*o metrhths pou vriskei poso eianai mk perfect mia fora*/
for(n=2; n<=MAXNUM; n++){                               /*diatrexontai oloi oi ari8moi apo 2 mexri 400000*/
 s=n;                                                   /*o ari8mos pou ka8e fora 8a vriskoume ton a8roisma twn diairetwn tou */
 temp=n+1;                                              /*athroisma diairetwn ths monadas kai tou eautou tou*/
 flag=0;                                                /*o metrhths pou elegxei oti 8a mpei mia fora sto block if k einai akeraios*/
 for(m=1; m<=MAXM; m++){                                /*i diadikasia pou to athroisma tou diaireth ksanaginetai a8roisma diairetwn 6 fores */
   
   i=2;                                                 /*prwtos ipopsifios diaireths ton 2 */
   while((i*i)<=s){                                     /*algori8mos teleiwn tetragwnwn*/
    ip=s%i;
    if(ip==0){       
     temp=temp+i;    
      piliko=s/i;
      if(piliko!=i)
        temp=temp+piliko;
             }
    i++;      }
 s=temp;                                               /*to athroisma temp pairnei thn timi s gia na ipologistei apo thn parapanw diadikasia ksana 6 fores */
 if(s%n==0){                                           /*k akeraios mono an athroisma mod n einai 0*/
     k=s/n;
     p=p+1;
     if(flag==0){
       district=district+1;
       flag=1;
                }
     if(m==1 && k!=2){
      printf("%d is a (%d-%d)-perfect number,that is a multiperfect number\n",n,m,k);
      a=a+1;}  
     else if(m==1 && k==2){
      printf("%d is a (%d-%d)- perfect number,that is a perfect number\n",n,m,k);
      b=b+1;}
     else if(k==2 && m==2){
      printf("%d is a (%d-%d)- perfect number,that is a superperfect number \n",n,m,k);
      c=c+1;}
     else
      printf("%d is a (%d-%d)- perfect number\n",n,m,k);     
             }
temp=temp+1;                                       /*to athroisma auksanetai kata 1 gia na prosmetri8ei sto epomeno kai h monada*/
 
                       }
                        }

pososto=(district*100)/(float)MAXNUM;
printf("Found %d distrinct (m-k)-perfect numbers (%f%% of 400000) in %d occurences\n",district,pososto,p);
printf("Found %d perfect numbers\n",b);
printf("Found %d multiperfect numbers (including perfect numbers)\n",b+a);
printf("Found %d superperfect numbers\n",c);
}
     
     
                        
            
                       


