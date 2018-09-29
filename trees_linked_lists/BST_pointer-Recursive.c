#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "BST_pointer-Recursive.h"

typedef struct typos_komboy
{   TStoixeioyTree dedomena;
	typos_deikti apaidi;
	typos_deikti dpaidi;
} typos_komboy;

void Tree_dimiourgia(typos_deikti *tree)
{/*	Pro: 		kamia
  *	Meta: 		Dimiourgia enos diadikou dentrou anazitisis*/     
	*tree=NULL;
}

void Tree_katastrofi(typos_deikti *tree)
{/*	Pro: 		Dimiourgia enos diadikou dentrou anazitisis
  *	Meta:		Diagrafi olon ton kombon tou dentrou */    
	if(Tree_keno(*tree))
		return;

	Tree_katastrofi(&(*tree)->apaidi);
	Tree_katastrofi(&(*tree)->dpaidi);
	free(*tree);
	*tree=NULL;
}

int Tree_keno(typos_deikti tree)
{/*	Pro: 		Dimiourgia enos diadikou dentrou anazitisis
  *	Meta:		epistrefei 1 an to dentro einai keno,diaforetika 0 */    
 	return (tree==NULL);
}

void Tree_apaidi(typos_deikti pateras, typos_deikti *paidi, int *error)
{/* Pro: 		ï pateras deixnei ena kombo se ena diadiko dentro anazitisis
  *	Meta:		epistrefei to aristero paidi pou deixnei o pateras */       
 	*error=0;
	if(pateras!=NULL)
		*paidi=pateras->apaidi;
	else
		*error=1;
}
	
void Tree_dpaidi(typos_deikti pateras, typos_deikti *paidi, int *error)
{/* Pro: 		ï pateras deixnei ena kombo se ena diadiko dentro anazitisis
  *	Meta:		epistrefei to deksi paidi pou deixnei o "pateras" */     
    *error=0;
	if(pateras!=NULL)
		*paidi=pateras->dpaidi;
	else
		*error=1; 
}

void Tree_pateras(typos_deikti tree, typos_deikti *pateras, typos_deikti paidi, int *error)
{/* Pro: 		to paidi deixnei ena kombo se ena diadiko dentro anazitisis 
  *	Meta:		epistrefei ton patera ston "pateras" tou kombou pou deixnei to "paidi" */     
	if(Tree_keno(tree)||Tree_keno(paidi)||TStree_iso(paidi->dedomena, tree->dedomena))
	{   *pateras=NULL;
		*error=1;
		return;
	}
	if(paidi==tree->apaidi||paidi==tree->dpaidi)
		*pateras=tree;
	else if(TStree_mikrotero(paidi->dedomena, tree->dedomena))
		Tree_pateras(tree->apaidi, pateras, paidi, error);
	else if(TStree_megalytero(paidi->dedomena, tree->dedomena))
		Tree_pateras(tree->dpaidi, pateras, paidi, error); 	 
}

void Tree_eisagogi(typos_deikti *tree, TStoixeioyTree stoixeio, int *error)
{/*	Pro: 		Dimiourgia enos diadikou dentrou anazitisis
  *	Meta:		Eisagogi tou kombou sto dentro efoson autos den iparxei idi */     
	if(Tree_keno(*tree))
	{ *tree=malloc(sizeof(typos_komboy));
		if(*tree==NULL)
		{   *error=1;
			return;
		}
		TStree_setValue(&((*tree)->dedomena), stoixeio);
		(*tree)->apaidi=NULL;
		(*tree)->dpaidi=NULL;
	}
	else if(TStree_mikrotero(stoixeio, (*tree)->dedomena))
		Tree_eisagogi(&((*tree)->apaidi), stoixeio, error); 
	else if(TStree_megalytero(stoixeio, (*tree)->dedomena)) 
		Tree_eisagogi(&((*tree)->dpaidi), stoixeio, error); 
	else
		*error=1; 
}

void Tree_diagrafi(typos_deikti *tree, TStoixeioyTree stoixeio, int *error)
{/*	Pro: 		Dimiourgia enos diadikou dentrou anazitisis
  *	Meta:		Diagrafi tou kombou me periexomeno "stoixeio" */      
    int out_err;
	typos_deikti temp, next;
	*error=0;
		
	if(Tree_keno(*tree))
	{   *error=1;
		return;
	}
	if(TStree_iso(stoixeio, (*tree)->dedomena))
	{  if(Tree_keno((*tree)->apaidi))
		{   temp=*tree;
			*tree=(*tree)->dpaidi;
			free(temp);
		}
		else if(Tree_keno((*tree)->dpaidi))
		{   temp=*tree;
			*tree=(*tree)->apaidi;
			free(temp);
		}
		else
		{   next=(*tree)->dpaidi;
			while(next->apaidi!=NULL)
				next=next->apaidi;
			TStree_setValue(&((*tree)->dedomena), next->dedomena);
			Tree_diagrafi(&((*tree)->dpaidi), (*tree)->dedomena, error);
		}
	}
	else if(TStree_mikrotero(stoixeio, (*tree)->dedomena))
		Tree_diagrafi(&((*tree)->apaidi), stoixeio, error); 
	else
		Tree_diagrafi(&((*tree)->dpaidi), stoixeio, error); 
}
		
void Tree_anazitisi(typos_deikti tree, TStoixeioyTree stoixeio, typos_deikti *deiktis, int *found)
{/*	Pro: 		Dimiourgia enos diadikou dentrou anazitisis
  *	Meta:		epistrefei ton deikti,ston "deiktis",tou kombou pou periexei to "stoixeio"*/  
	*found=0;
	
	if(Tree_keno(tree))
	{   *deiktis=NULL;
		return;
	}
	if(TStree_iso(stoixeio, tree->dedomena))
	{   *deiktis=tree;
		*found=1;
	}
	else if(TStree_mikrotero(stoixeio, tree->dedomena))
		Tree_anazitisi(tree->apaidi, stoixeio, deiktis, found); 
	else if(TStree_megalytero(stoixeio, tree->dedomena))
		Tree_anazitisi(tree->dpaidi, stoixeio, deiktis, found); 
}


void Tree_periexomeno(typos_deikti tree, TStoixeioyTree *periexomeno,int * error)
{/*	Pro: 		Dimiourgia enos diadikou dentrou anazitisis
  *	Meta:	    Epistrefei sto "stoixeio" tin timi ton dedomenon pou iparxoun ston kombo 
  *             pou deixnei to "tree" */    
    *error=0;  
	if(!Tree_keno(tree))
	   TStree_setValue(periexomeno, tree->dedomena);
	else
       *error=1;   
}

void Tree_allagi(typos_deikti *tree, TStoixeioyTree old, TStoixeioyTree new, int *error)
{/*	Pro: 		Dimiourgia enos diadikou dentrou anazitisis
  *	Meta:	    Enimenronei ton kombo pou exei tin timi old allazontas tin timi se new */    
	typos_deikti deiktis;
	int found;
	*error=found=0;
	deiktis=NULL;
	
	Tree_anazitisi(*tree, old, &deiktis, &found);
	if(found)
	{   Tree_diagrafi(tree, old, error);
		if(!(*error))
			Tree_eisagogi(tree, new, error);
	}
	else
		*error=1; 
}


