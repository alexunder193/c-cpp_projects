#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <lapacke.h>
#include <cblas.h>
#include "functions.h"

int main(int argc, char *argv[]){
	FILE *fp;
	int n,i,j,info;
	long curtime;
	double input;
	double *onedimA;
	double **A;
	int counter=1;
	lapack_int *ipiv;
	////////////////////////////////////////////////////////////////////////////
	if(argc<2){
		printf("Give me one arguments or two arguments for file\n");
		exit(-1);
	}
	printf("Give me the dimension of arrays:");
	scanf("%d",&n);
	A=malloc(n*sizeof(double *));			//kataskeui A
	for(i=0; i<n; i++){
		A[i]=malloc(n*sizeof(double));
	}
	if(strcmp(argv[1],"-i")==0){		//orisma gia pinaka apo to pliktrologio
		printf("Give me A array\n");
		for(i=0; i<n; i++){
			for(j=0; j<n; j++){
				scanf("%lf",&input);
				A[i][j]=input;
			}
		}
	}
	else if(strcmp(argv[1],"-r")==0){
		curtime = time(NULL);
    	srand((unsigned int) curtime);
    	double range=100;
    	double div = RAND_MAX / range;
    	for(i=0; i<n; i++){
			for(j=0; j<n; j++){
				A[i][j]=-50.0 + (rand() / div);
			}
		}
	}
	else{
		fp=fopen(argv[2],"r");
		for(i=0; i<n; i++){
			for(j=0; j<n; j++){
				fscanf(fp, "%lf", &input);
				A[i][j]=input;
			}
		}
	}
	////////////////////////////////////////////////////////
	printtwodarray(A,n,n);
	printf("\n");
	onedimA=convertToRowMajorMatrix(A,n,n);
	lapack_int NROWS = n;
    lapack_int NCOLS = n;
    lapack_int LEADING_DIMENSION_A = n;
    ipiv=LAPACKE_malloc(n*sizeof(lapack_int));
	info=LAPACKE_dgetrf(LAPACK_ROW_MAJOR,NROWS,NCOLS,onedimA,LEADING_DIMENSION_A, ipiv);
	info=LAPACKE_dgetri(LAPACK_ROW_MAJOR,n,onedimA,n,ipiv);
	printf("Inverse of X:\n");
	for(i=0; i<n*n; i++){
		printf("%lf		",onedimA[i]);
		if(counter==n){
			printf("\n");
			counter=0;
		}
		counter ++;
	}
	printf("\n");
}
