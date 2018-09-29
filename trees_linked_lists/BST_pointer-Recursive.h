#ifndef __BST_POINTER__RECURSIVE_ 
#define __BST_POINTER__RECURSIVE__

#include "typos_stoixeiouDDA.h"

/*diloseis tipon*/
typedef struct typos_komboy * typos_deikti;

/*diloseis synarthseon*/

/*dimiourgia/katastrofi dentrou*/
void Tree_dimiourgia(typos_deikti *tree);
void Tree_katastrofi(typos_deikti *tree);

/*Prakseis elegxou*/
int Tree_keno(typos_deikti tree);

/*Prakseis prosvasis*/
void Tree_apaidi(typos_deikti pateras, typos_deikti *paidi, int *error);
void Tree_dpaidi(typos_deikti pateras, typos_deikti *paidi, int *error);
void Tree_pateras(typos_deikti tree, typos_deikti *pateras, typos_deikti paidi, int *error);

/*Prakseis diaxeirisis */
void Tree_eisagogi(typos_deikti *tree, TStoixeioyTree stoixeio, int *error);
void Tree_diagrafi(typos_deikti *tree, TStoixeioyTree stoixeio, int *error);

/*Prakseis anazitisis*/
void Tree_anazitisi(typos_deikti tree, TStoixeioyTree stoixeio, typos_deikti *deiktis, int *found);
void Tree_periexomeno(typos_deikti tree, TStoixeioyTree *periexomeno,int * error);
void Tree_allagi(typos_deikti *tree, TStoixeioyTree old, TStoixeioyTree new, int *error);

void inorder(typos_deikti riza,FILE *out);

#endif /*#ifndef __BST_POINTER__RECURSIVE__ */
