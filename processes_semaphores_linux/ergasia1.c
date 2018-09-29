#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <math.h>
#include <time.h>

union semun { int semvalue;                            /*domi gia shmaforous*/
              struct semid_ds *buf;
              short * pinakas;
            }arg;



int main(int argc,char *argv[])
{
 struct sembuf operation;
 int n,i,c,pid,memid,r,semid,a,j,l,q,t,u,v;
 int dokimes[argc-2][3];                          /*sthles me diastash ari8mhth kai paronomasth klasmatos*/
 long curtime;
 int *array;
 n=argc-2;
 array=malloc((argc-1)*sizeof(int));               /*Pinakas me ta orismata grammis entolwn*/
 if(array==NULL){
 printf("Sorry, cannot allocate memory\n");
 return -1;
 }
 for(i=0; i<=n; i++)
   array[i]=atoi(argv[i+1]);
 for(j=0; j<argc-2; j++)
  for(l=0; l<3; l++)
   {if(l==0)
    dokimes[j][l]=array[j];
   else
    dokimes[j][l]=0;
   }  
 curtime=time(NULL);
 srand((unsigned int)curtime);
 memid=shmget(IPC_PRIVATE,3*sizeof(int), 0600|IPC_CREAT);
 int *pointer=shmat(memid,0,0);                                    /*Desmeush diamoirazomenis mnimis*/
 semid=semget(IPC_PRIVATE,2,0600|IPC_CREAT);                         /*shmaforoi*/
 arg.semvalue=1;
 semctl(semid,0,SETVAL,arg);
 arg.semvalue=0;
 semctl(semid,1,SETVAL,arg);
 for(c=0; c<argc-2; c++)                                          /*Gennhsh paidiwn*/
 { pid=fork();
  if(pid==0)
	break;
  }
   if(pid==0)
    {int dim;
     float aktina,x,y,oros1,oros2,apotelesma;
     for(u=0; u<array[n]; u++)
     {operation.sem_num=1;
      operation.sem_op=-1;           /*DOWN*/
      semop(semid,&operation,1);
      dim=pointer[0];
      operation.sem_num=0;
      operation.sem_op=1;            /*UP*/
      semop(semid,&operation,1);
      if(dim!=0)
       {aktina=(float)dim/2;
        x=((float)(rand()%(RAND_MAX))/(float)(RAND_MAX))*dim;
        y=((float)(rand()%(RAND_MAX))/(float)(RAND_MAX))*dim;
        oros1=(x-aktina)*(x-aktina);
        oros2=(y-aktina)*(y-aktina);
        apotelesma=sqrt(oros1 + oros2);            /*upologismos apotelesmatos*/
        if(apotelesma>aktina)
         {
          operation.sem_num=1;
          operation.sem_op=-1;
          semop(semid,&operation,1);
          pointer[1]=dim;      /*grapsimo paidiou stin mnhmh tin pleura */
          pointer[2]=0;         /*flag 0 h 1 einai int.Einai h oxi mesa ston egkegrameno kuklo?*/
          operation.sem_num=0;
          operation.sem_op=1;
          semop(semid,&operation,1);
         }
        else
         {
          operation.sem_num=1;
          operation.sem_op=-1;
          semop(semid,&operation,1);
          pointer[1]=dim;
          pointer[2]=1;
          operation.sem_num=0;
          operation.sem_op=1;
          semop(semid,&operation,1);
         }
      }
      else
      { operation.sem_num=1;
        operation.sem_op=1;
        semop(semid,&operation,1);
	exit(0);
      }
     }
    }
   else
    {
     for(a=0; a<array[n]; a++)                                /*EPILOGH THESIS TOY PINAKA ARRAY GIA TYXAIA DIASTASH*/
      {r=rand()%(argc-1);
       if(r==argc-2)
        r--;
       operation.sem_num=0;
       operation.sem_op=-1;
       semop(semid,&operation,1);
       pointer[0]=array[r];
       operation.sem_num=1;
       operation.sem_op=1;
       semop(semid,&operation,1);
       operation.sem_num=0;
       operation.sem_op=-1;
       semop(semid,&operation,1);
       int diastasi=pointer[1];
       int flag=pointer[2];
       operation.sem_num=1;
       operation.sem_op=1;
       semop(semid,&operation,1);
       for(q=0; q<argc-2; q++)                                   /*DEFTERH STHLH PLI8OS EPITIXIMENWN DOKIMWN*/
        {
         if(dokimes[q][0]==diastasi)                              /*TRITH STHLH PLITHOS SUNOLIKWN DOKIMWN*/
          {dokimes[q][2]++;
           if(flag==1)
            dokimes[q][1]++;
          }
         }
      }
     operation.sem_num=0;
     operation.sem_op=-1;
     semop(semid,&operation,1);
     pointer[0]=0;
     operation.sem_num=1;
     operation.sem_op=1;
     semop(semid,&operation,1);
     for(t=0; t<argc-2; t++)
       wait(0);
     shmctl(memid,IPC_RMID,0);                           /*diagrafi mnhmhs*/
     semctl(semid,0,IPC_RMID);                            /*apodesmeusi shmaforwn*/
     for(v=0; v<argc-2; v++)
      {
	if(dokimes[v][2]!=0)
       	{float result=4*((float)dokimes[v][1]/(float)dokimes[v][2]);
          printf("%f\n",result);
	}
      }
    }
 return 0;
}
