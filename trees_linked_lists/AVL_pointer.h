
#ifndef __AVL_POINTER__ 
#define __AVL_POINTER__

#include "typos_stoixeiouDDA.h"

/*diloseis tipon*/

typedef struct typos_komvou *typos_deikti; 

/*diloseis synarthseon*/

/*dimiourgia/katastrofi dentrou*/
void AVLTree_dimiourgia(typos_deikti *riza);
void AVLTree_katastrofi(typos_deikti *riza);

/*Prakseis elegxou*/
int	AVLTree_keno(typos_deikti riza);

/*Prakseis prosvasis*/

void AVLTree_apaidi(typos_deikti p, typos_deikti *paidi,int * error);
void AVLTree_dpaidi(typos_deikti p,typos_deikti *paidi,int * error);

void AVLTree_pateras(typos_deikti riza, typos_deikti *pateras, typos_deikti paidi, int *error);

/*Prakseis diaxeirisis */

void AVLTree_eisagogi(typos_deikti *riza,TStoixeioyTree stoixeio,int *ypsilotero,int *error);
void AVLTree_diagrafi(typos_deikti *riza,TStoixeioyTree stoixeio,int *ypsilotero,int *error);

/*Prakseis anazitisis*/
void AVLTree_anazitisi(typos_deikti riza, TStoixeioyTree stoixeio, typos_deikti *deiktis, int *found);
void AVLTree_periexomeno(typos_deikti riza,TStoixeioyTree *stoixeio,int * error);
void AVLTree_allagi(typos_deikti *tree, TStoixeioyTree old, TStoixeioyTree new, int *error);

void inorder(typos_deikti riza,FILE *out);



#endif /*#ifndef __AVL_POINTER__ */
