#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "Pointer_List.h"

typedef struct info_node
{   int      size;	
	typos_deikti     arxi; 	/*deikths sto proto komvo tis listas*/
} info_node;  /* o komvos plhroforias ths listas*/

typedef struct typos_komvou
{   TStoixeioyListas dedomena;	
	typos_deikti    epomenos;
        typos_deikti    proigoumenos; 	
} typos_komvou;	   /*o typos toy kombou ths listas*/


info_deikti  LIST_dimiourgia( )
{/*	Pro: 		kamia
  *	Meta: 		Dhmioyrgia kenhs syndedemenhs listas meso tis desmeusis kai arxikopoiisis tou  komvou
                linfo pou leitourgei os komvos pliroforias kai tha sindethei me ton proto komvo pou tha 
                eisaxthei */
 	info_deikti linfo;
    linfo = malloc(sizeof(info_node));
        if(linfo==NULL)
          return NULL;
   	linfo->size = 0;
	linfo->arxi = NULL;
	return linfo;
}

void LIST_katastrofi(info_deikti * linfo)
{/*	Pro: 	  Dhmioyrgia listas
  *	Meta: 	  Katastrofi ths listas kai apodesmeusi sto telos kai tou komvou linfo */    
    typos_deikti temp, todel;
	
	if(!LIST_keni(*linfo))
	{   temp=((*linfo)->arxi)->epomenos;
		while(temp!=(*linfo)->arxi)
		{   todel=temp;
			temp=temp->epomenos;
			free(todel);
		}
		free((*linfo)->arxi);
		(*linfo)->arxi=NULL;
    }	
		free(*linfo);
		(*linfo)=NULL;
}

int LIST_keni(const info_deikti  linfo)
{/*	Pro: 		Dhmiourgia listas
  *	Meta:		epistrefei 1 an h lista einai kenh, diaforetika 0 */
	return ( linfo->arxi == NULL );
}

void LIST_periexomeno(const info_deikti  linfo, typos_deikti p, TStoixeioyListas *val,int * error)
{/*	Pro: 		O deikths p deixnei ena kombo sth lista
  *	Meta:		epistrefei ta dedomena ston kombo pou deixnei o p */
   *error=0;
   if(p!=NULL)
	  TSlist_setValue(val, p->dedomena);
    else
      *error=1;  
}

void LIST_allagi(info_deikti * const linfo, typos_deikti * const p, TStoixeioyListas stoixeio,int * error)
{/*	Pro: 		Dhmiourgia listas
  *	Meta:		Allazei ta dedomena ston komvo pou deixnei o p */    
    *error=0;
	if((*p)!=NULL)
	  TSlist_setValue(&((*p)->dedomena), stoixeio);
    else
      *error=1;		
}

void LIST_diadromi(const info_deikti  linfo, int * const error)
{/*	Pro: 		Dhmiourgia listas
  *	Meta:		Grafei stin eksodo ola ta stoixeia tis listas */  
	typos_deikti temp;
	temp=linfo->arxi;
	*error=0;
	
	if(LIST_keni(linfo))
	{   *error=1;
		return;
	}
	
	do
	{   TSlist_writeValue(stdout,temp->dedomena);
		temp=temp->epomenos;
	}
	while(temp!=linfo->arxi);
}

void LIST_eisagogi(info_deikti *  const linfo, TStoixeioyListas stoixeio,
					typos_deikti prodeiktis, int *error)
{/*	Pro: 		Dhmiourgia listas
  *	Meta: 		Eisagetai to "stoixeio" meta ton "prodeikti",an einai null autos to stoixeio mpainei
                stin arxi tis listas allios mpainei meta apo ton komvo pou deixnei autos */ 
	
    typos_deikti prosorinos, temp; /*Deixnei ton neo kombo pou prokeitai na eisax8ei*/

	prosorinos = malloc(sizeof(typos_komvou));
	if ( prosorinos == NULL )
	{   *error=1;
		return;
	}
	if(prodeiktis==NULL) //gia eisagogi stin arxi
	{   TSlist_setValue(&(prosorinos->dedomena), stoixeio);
		if(LIST_keni(*linfo))
			prosorinos->epomenos = prosorinos;
		else
		{   LIST_last(*linfo, &temp, error);
			prosorinos->epomenos = (*linfo)->arxi;
			temp->epomenos = prosorinos;
		}
		(*linfo)->arxi= prosorinos;	 
	}
	else  //gia eisagogi meta ton prodeikti
	{   TSlist_setValue(&(prosorinos->dedomena), stoixeio);
		prosorinos->epomenos = prodeiktis->epomenos;
		prodeiktis->epomenos = prosorinos;
	 }
	 (*linfo)->size ++;
}

void LIST_diagrafi(info_deikti *  const linfo, typos_deikti *deiktis, int * const error)
{/*	Pro: 		Dhmiourgia Listas
  *	Meta: 		Diagrafetai to stoixeio ths listas pou deixnei o "deiktis" */    
	typos_deikti prosorinos,previous;
	int error2=0;
	prosorinos=*deiktis;
	*error=0;
	if(LIST_keni(*linfo)|| (*deiktis==NULL))
	{   *error=1;
		return;
	}
    if(((*linfo)->arxi)->epomenos!=(*linfo)->arxi) //an den iparxei mono enas kombos sti lista
     {  previous=prosorinos;                                          
    	LIST_proigoymenos(*linfo, &previous, &error2);
	 	if(error2==2)
        { *error=1;
          return;
        }                                              
       	if((*linfo)->arxi==*deiktis) //an einai o protos kombos pou prepei na diagrafei
 			(*linfo)->arxi=(*deiktis)->epomenos;	
        *deiktis=prosorinos->epomenos;
        previous->epomenos =prosorinos->epomenos;
        free(prosorinos);
        prosorinos=NULL;
    }
    else //diagrafi tou monadikou kombou tis listas
     { free((*linfo)->arxi);
	   (*linfo)->arxi=NULL;
	   *deiktis=NULL;                
      }                      
       (*linfo)->size--;                                                                  	
}


void LIST_epomenos(const info_deikti  linfo, typos_deikti * const p, int * const error)
{/*	Pro: 		Dhmiourgia listas
  *	Meta:		Epistrefei ton epomeno komvo tou "p" kai sto error 0,an o p einai null tote epistrefei 
                sto error 2 allios an den iparxei epomenos epistrefei sto error 1 */    
	*error = 0;
	if((*p)!=NULL)
	 { if((*p)->epomenos!=NULL) 
		 *p=(*p)->epomenos;
       else
         *error=1;                 
      }  
	else
	   *error=2; 
}

void LIST_proigoymenos (const info_deikti linfo, typos_deikti * const p, int * const error)
{/*	Pro: 		Dhmiourgia listas
  *	Meta:		Epistrefei ton prohgoumeno komvo tou "p" kai sto error 0,an o p einai null tote epistrefei 
                sto error 2 allios an o p einai o protos komvos tis listas epistrefei sto error 1 */
          *error=0;     
        if((*p)==NULL)
          *error=2;
        else if((*p)==linfo->arxi)
          {*p=(*p)->proigoumenos;
           *error=1;
          }
        else
           *p=(*p)->proigoumenos;
            
          
}

void LIST_first(const info_deikti  linfo, typos_deikti * const first, int * const error)
{/*	Pro: 		Dhmiourgia listas
  *	Meta:		Epistrefei ton  proto komvo ths listas diaforetika epistrefei 1 sto error */     
	*error=0;
	*first=linfo->arxi;
	if (LIST_keni(linfo))
		*error=1;
}

void LIST_last (const info_deikti  linfo, typos_deikti * const last, int * const error)
{/*	Pro: 		Dhmiourgia listas
  *	Meta:		Epistrefei ton  teleutaio komvo ths listas diaforetika 1 sto error an einai kenh auti */  
	typos_deikti prosorinos=linfo->arxi;
	*error = 0;
	*last=NULL;
    if (LIST_keni(linfo))          /* list is empty */
		*error=1;                 
	else                       /* not empty*/
	{   typos_deikti prosorinos=linfo->arxi;
		while (prosorinos->epomenos != linfo->arxi)
			prosorinos=prosorinos->epomenos;
		*last=prosorinos;
	 } 
}

void LIST_anazitisi(const info_deikti  linfo, TStoixeioyListas stoixeio,
					typos_deikti *prodeiktis, int *vrethike)
{/*	Pro: 		Dhmiourgia listas
  *	Meta:		Anazhta an yparxei sthn lista to stoixeio,an yparxei to vrethike ginetai 1 */     
	TStoixeioyListas temp;
	typos_deikti trexon;
	int error;

	error=0;
	trexon = linfo->arxi;
	LIST_last(linfo, prodeiktis, &error);
	error=0;
	*vrethike = 0;

	if(!LIST_keni(linfo))
	 {	do
		{   LIST_periexomeno(linfo,trexon,&temp,&error);
			if (TSlist_iso(temp, stoixeio)) //an vrethei to stoixeio
				*vrethike =1; 
			else
			{   *prodeiktis = trexon;
				LIST_epomenos(linfo, &trexon, &error);
			 }
		}
		while ( (!(*vrethike)) && (trexon!=linfo->arxi));
      }
}
