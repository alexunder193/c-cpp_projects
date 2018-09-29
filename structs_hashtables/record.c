#include "record.h"
   
int hash_function(char * a, int hashtablesize) { //h hash einai apo stack overflow:  http://stackoverflow.com/questions/20462826/hash-hash_function-for-strings-in-c
	unsigned int hash = 0;
	int i;
	for (i = 0; a[i] != '\0'; i++)
		hash = 31 * hash + a[i];

	return hash % hashtablesize; //epistrefei 0 ews bluebucket-1
}
