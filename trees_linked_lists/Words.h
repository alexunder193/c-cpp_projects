#ifndef __TYPOS_WORDS__ 
#define __TYPOS_WORDS__

/*orismos typou Words */
typedef struct RecWords * typosWords; 

/* epikefalides praxewn */

/* praxeis poy yloioyntai me praxeis DDA */
typosWords dhmiourgia_Words();
void katastrofh_Words(typosWords * Wordsptr);

void InsertWord(typosWords Words, char * w);
void CheckWord(typosWords Words, char * w);
void ShowCommonWords(FILE *out, typosWords Words);

/* praxeis poy diaxeirizontai toys xronoys */
void SetInsertTime(typosWords Words, float time, int position);
void SetCheckTime(typosWords Words, float time);
void SetDiadromhTime(typosWords Words, float time);
void PrintTimes(FILE *out, typosWords Words);
#endif

