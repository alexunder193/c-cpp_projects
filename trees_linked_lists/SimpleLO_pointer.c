#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "Pointer_List.h"

typedef struct info_node
{   int      size;	
	typos_deikti     arxi; 	/*deikths sto proto komvo tis listas*/
} info_node;  /* o komvos plhroforias ths listas */

typedef struct typos_komvou
{   TStoixeioyListas dedomena;	
	typos_deikti    epomenos; 	
} typos_komvou;	   /*o typos toy kombou ths listas*/

void eisagogi_arxi(info_deikti * const ,TStoixeioyListas, int *);
void eisagogi_meta(info_deikti * const ,TStoixeioyListas, typos_deikti, int *);


info_deikti LIST_dimiourgia( )
{/*	Pro: 		kamia
  *	Meta: 		Dhmioyrgia kenhs syndedemenhs listas meso tis desmeusis kai arxikopoiisis tou  komvou
                linfo pou leitourgei os komvos pliroforias kai tha sindethei me ton proto komvo pou tha 
                eisaxthei */
    info_deikti linfo; 
    linfo = malloc(sizeof(info_node));
   	linfo->size = 0;
	linfo->arxi = NULL; 
    return linfo;	
}


void LIST_katastrofi(info_deikti * linfo)
{/*	Pro: 	  Dhmioyrgia listas
  *	Meta: 	  Katastrofi ths listas kai apodesmeusi sto telos kai tou komvou linfo */     
	typos_deikti todel,todel2;
	todel= (*linfo)->arxi;
	while(todel!=NULL)
	{   todel2=todel;
		todel=(todel)->epomenos;
		free(todel2);
	}
	(*linfo)->arxi = NULL;
    free(*linfo);
    (*linfo)=NULL;
}

int LIST_keni(const info_deikti  linfo)
{/*	Pro: 		Dhmioyrgia Listas
  *	Meta:		Epistrefei 1 an h lista einai kenh, diaforetika 0  */
 	return ( linfo->arxi == NULL );
}

void LIST_periexomeno(const info_deikti  linfo,const typos_deikti p, TStoixeioyListas *val,int * const error)
{/*	Pro: 		O deikths p deixnei ena kombo sth lista
  *	Meta:		Epistrefei ta dedomena ston komvo pou deixnei o p */
     *error=0;
    if(p!=NULL)
        TSlist_setValue(val, p->dedomena);
	else
	   *error=1;
}

void LIST_allagi(info_deikti * const linfo,typos_deikti * const p, TStoixeioyListas stoixeio,int * const error)
{/*	Pro: 		Dhmiourgia listas
  *	Meta:		Allazei ta dedomena ston komvo pou deixnei o p */    
	int found,error2;
    *error=0;
	TStoixeioyListas st;
	
	if((*p)!=NULL)
    {  LIST_periexomeno(*linfo,*p, &st,&error2);
	   LIST_anazitisi(*linfo, st, p, &found);
       if(found) 
       {  if((*p)!=NULL)
           { LIST_epomenos(*linfo, p, &error2);
             LIST_periexomeno(*linfo,*p, &st,&error2);
             }
          else
             LIST_first(*linfo, p, &error2);     
          LIST_diagrafi(linfo, p, error);
          if(!(*error))
           { LIST_eisagogi(linfo, stoixeio,*p, &error2);
             LIST_anazitisi(*linfo, stoixeio, p, &found);
             if((*p)!=NULL)
             { LIST_epomenos(*linfo, p, &error2);
               LIST_periexomeno(*linfo,*p, &st,&error2);
             }
             else
              LIST_first(*linfo, p, &error2);
           }
        }
       else
          *error=1;    
     }  
	else
       *error=1;
}

void LIST_diadromi(const info_deikti  linfo, int * const error)
{/*	Pro: 		Dhmiourgia listas
  *	Meta:		Grafei stin eksodo ola ta stoixeia tis listas */     
	typos_deikti temp;
	temp=(linfo)->arxi;
	*error=0;
	
	if(LIST_keni(linfo))
	{   *error=1;
		return;
	}
	
	while(temp!=NULL)
	{   TSlist_writeValue(stdout,temp->dedomena);
		temp=temp->epomenos;
	}
}

void LIST_eisagogi(info_deikti * const linfo, TStoixeioyListas stoixeio,typos_deikti prodeiktis, int *error)
{/*	Pro: 		Dhmiourgia listas
 *	Meta: 		Eisagetai to "stoixeio" meta ton "prodeikti",an einai null autos to stoixeio mpainei
                stin arxi tis listas allios mpainei meta apo ton komvo pou deixnei autos */   
	typos_deikti  temp,next;
	*error=0;
	prodeiktis=(*linfo)->arxi;
	if(prodeiktis==NULL)  
		eisagogi_arxi(linfo, stoixeio, error); 
	else if(TSlist_mikrotero(stoixeio, prodeiktis->dedomena))
		eisagogi_arxi(linfo, stoixeio, error); 
	else
	{    temp=prodeiktis;
	 	while(TSlist_megalytero(stoixeio,temp->dedomena) && (temp->epomenos!=NULL))
	 	{   next=temp->epomenos;
			if(TSlist_mikrotero(stoixeio, next->dedomena))
			{   eisagogi_meta(linfo,stoixeio,temp, error);
				return;
			}
			else
				temp=next;
		}
		eisagogi_meta(linfo,stoixeio,temp, error);
	}
}

void eisagogi_arxi(info_deikti * const linfo,TStoixeioyListas stoixeio, int *error)
{/*	Pro: 		Dhmiourgia listas
  *	Meta: 		O kombos me ta dedomena stoixeio exei eisax8ei sthn arxh ths listas */
  
	typos_deikti prosorinos; /*Deixnei ton neo kombo pou prokeitai na eisax8ei*/

	prosorinos = malloc(sizeof(typos_komvou));
	if ( prosorinos == NULL )
	{   *error=1;
		return;
	 }
	TSlist_setValue(&prosorinos->dedomena, stoixeio);
    prosorinos->epomenos = (*linfo)->arxi;
    (*linfo)->arxi = prosorinos;
    (*linfo)->size ++;
}

void eisagogi_meta(info_deikti * const linfo,TStoixeioyListas stoixeio, typos_deikti prodeiktis, int *error)
{/*	Pro: 		O prodeiktis deixnei ena kombo sth lista
  *	Meta: 		O komboe me ta dedomena exei eisax8ei meta ton kombo pou
 				deixnei o prodeiktis */
 				
	typos_deikti prosorinos; /*Deixnei ton neo kombo pou prokeitai na eisax8ei*/

	prosorinos = malloc(sizeof(typos_komvou));
	if (prosorinos == NULL)
	{   *error=1;
		return;
	}
	TSlist_setValue(&prosorinos->dedomena, stoixeio);
	prosorinos->epomenos = prodeiktis->epomenos;
	prodeiktis->epomenos = prosorinos;
	
	(*linfo)->size ++;
}

void LIST_diagrafi(info_deikti * const linfo, typos_deikti *deiktis, int * const error)
{/*	Pro: 		Dhmiourgia Listas
  *	Meta: 		Diagrafetai to stoixeio ths listas pou deixnei o "deiktis" */    
	typos_deikti prosorinos,previous;
	*error=0;
	if (LIST_keni(*linfo)|| (*deiktis==NULL))
	{   *error=1;
		return;
	}
	if((*linfo)->arxi==(*deiktis)) //an einai o protos kombos tis listas
	{    prosorinos=*deiktis;
        *deiktis=prosorinos->epomenos;
		(*linfo)->arxi =prosorinos->epomenos;		
	}
	else
	{     prosorinos=*deiktis;
          previous=prosorinos;
          *deiktis=prosorinos->epomenos;
	      LIST_proigoymenos(*linfo, &previous, error);
          if(((*error)==1) || ((*error)==2))
			 	return; 
	      previous->epomenos=prosorinos->epomenos;	
	}
	free(prosorinos);
    prosorinos=NULL;	
	(*linfo)->size--;
}

void LIST_epomenos( info_deikti  const linfo, typos_deikti * const p, int * const error)
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
	else if((*p)==NULL)
	   *error=2;
}


void LIST_proigoymenos (const info_deikti linfo, typos_deikti * const p, int * const error)
{/*	Pro: 		Dhmiourgia listas
  *	Meta:		Epistrefei ton prohgoumeno komvo tou "p" kai sto error 0,an o p einai null tote epistrefei 
                sto error 2 allios an o p einai o protos komvos tis listas epistrefei sto error 1 */    
	typos_deikti prosorinos=linfo->arxi;
	*error = 0;
	if((*p)!=NULL)             /* lista oxi adeia */
	{   if((*p)==linfo->arxi)           /* p deixnei ston proto kombo */
			*error=1;                  
		else                       /* se kathe alli periptosi */
		{   typos_deikti prosorinos=linfo->arxi;
			while(prosorinos->epomenos != *p)
				prosorinos=prosorinos->epomenos;
			*p=prosorinos;
		}
	}
	else
		*error=2;  
}

void LIST_first (info_deikti  const linfo, typos_deikti * const first, int * const error)
{/*	Pro: 		Dhmiourgia listas
  *	Meta:		Epistrefei ton  proto komvo ths listas diaforetika epistrefei 1 sto error */    
	*error=0;
	*first=linfo->arxi;
	if (LIST_keni(linfo))
		*error=1;
}

void LIST_last (info_deikti  const linfo, typos_deikti * const last, int * const error)
{/*	Pro: 		Dhmiourgia listas
  *	Meta:		Epistrefei ton  teleutaio komvo ths listas diaforetika 1 sto error an einai kenh auti */    
	typos_deikti prosorinos=linfo->arxi;
	*error = 0;
	*last=NULL;
	if (LIST_keni(linfo))           
    	*error=1;                   
	else                      
	{   typos_deikti prosorinos=linfo->arxi;
		while (prosorinos->epomenos != NULL)
			prosorinos=prosorinos->epomenos;
		*last=prosorinos;
	 } 
}

void LIST_anazitisi(info_deikti  const linfo, TStoixeioyListas stoixeio,
					typos_deikti *prodeiktis, int *vrethike)
{/*	Pro: 		Dhmiourgia listas
  *	Meta:		Anazhta an yparxei sthn lista to stoixeio,an yparxei to vrethike ginetai 1 */     
	TStoixeioyListas val;
	typos_deikti trexon;
	int anazitisi, error;

	error=0;
	trexon = linfo->arxi;
	*prodeiktis = NULL;
	*vrethike = 0;
	anazitisi = 0;
	while ( (!anazitisi) && (trexon!=NULL))
	{   LIST_periexomeno(linfo,trexon,&val,&error);
		if (TSlist_megalytero(val, stoixeio) || TSlist_iso(val, stoixeio))
		{   anazitisi=1;
			*vrethike=TSlist_iso(val, stoixeio); //gia elegxo an vrethike ontos to stoixeio
		 }
		else
		{   *prodeiktis = trexon;
			LIST_epomenos(linfo, &trexon,&error); 
			if(error) //an den iparxei epomenos
                trexon=NULL;
		 }
	}
}
