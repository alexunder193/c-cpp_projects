#ifndef __POINTER__LIST_ 
#define __POINTER__LIST_

#include "TStoixeioyListas.h"

/*dhlwseis typwn*/
typedef struct info_node  * info_deikti;

typedef struct typos_komvou *typos_deikti;

/*dhlwseis synarthsewn*/

/*dhmioyrgia/katastrofi listas*/
info_deikti LIST_dimiourgia();
void LIST_katastrofi(info_deikti * linfo);

/*prakseis elegxoy*/
int	LIST_keni(const info_deikti  linfo);

/*prakseis prosbashs*/
void LIST_periexomeno(const info_deikti  linfo, const typos_deikti p, TStoixeioyListas *val,int * error);
void LIST_allagi(info_deikti * const linfo, typos_deikti * const p, TStoixeioyListas stoixeio,int * error);
void LIST_diadromi(const info_deikti  linfo, int * const error);

/*prakseis eisagwgh-diagrafh*/
void LIST_eisagogi(info_deikti * const linfo, TStoixeioyListas stoixeio,typos_deikti prodeiktis, int *error);
void LIST_eisagogi_arxi(info_deikti * const linfo,TStoixeioyListas stoixeio,int *error);
void LIST_eisagogi_meta(info_deikti * const linfo,TStoixeioyListas stoixeio,typos_deikti prodeiktis,int *error);
void LIST_diagrafi(info_deikti * const linfo, typos_deikti *deiktis, int * const error);

/* Epilogh Kombou */
void LIST_epomenos(const info_deikti  linfo, typos_deikti * const p, int * const error);
void LIST_proigoymenos(const info_deikti linfo, typos_deikti * const p, int * const error);
void LIST_first(const info_deikti  linfo, typos_deikti * const first, int * const error);
void LIST_last(const info_deikti  linfo, typos_deikti * const last, int * const error);

/*prakseis anazhthshs*/

void LIST_anazitisi(const info_deikti  linfo, TStoixeioyListas stoixeio,
					typos_deikti *prodeiktis, int *vrethike);

#endif /*#ifndef __POINTER__LIST_ */
