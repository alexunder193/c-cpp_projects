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
	double *onedimB;
	double **A;
	double **B;
	int counter=1;
	lapack_int *ipiv;
	////////////////////////////////////////////////////////////////////////////
	printf("Give me the dimension of arrays:");
	scanf("%d",&n);
	A=malloc(n*sizeof(double *));			//kataskeui A
	for(i=0; i<n; i++){
		A[i]=malloc(n*sizeof(double));
	}
	B=malloc(n*sizeof(double *));
	for(i=0; i<n; i++){
		B[i]=malloc(n*sizeof(double));
	}
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			A[i][j]=(double)1/(i+1+j+1-1);
		}
	}
	B[0][0]=1;
	B[1][0]=-2;
	B[2][0]=1;
	B[3][0]=-2;
	B[4][0]=1;
	B[5][0]=-2;
	B[6][0]=1;
	B[7][0]=-2;
	B[8][0]=1;
	B[9][0]=-2;
	////////////////////////////////////////////////////////
	printtwodarray(A,n,n);
	printf("\n");
	printtwodarray(B,n,n);
	onedimA=convertToRowMajorMatrix(A,n,n);
	onedimB=convertToRowMajorMatrix(B,n,n);
	lapack_int NROWS = n;
    lapack_int NCOLS = n;
    lapack_int LEADING_DIMENSION_A = n;
    ipiv=LAPACKE_malloc(n*sizeof(lapack_int));
	info=LAPACKE_dgetrf(LAPACK_ROW_MAJOR,NROWS,NCOLS,onedimA,LEADING_DIMENSION_A, ipiv);
	//printf("factorization info=%d\n",info);
	//printf("info=%d\n",info);
	//for(i=0; i<n; i++)
		//printf("ipiv:\n%d\n",ipiv[i]);
	//printf("LU Factorization\n");
	//printonedarray(onedimA,n*n);
	//printf("\n");
	info=LAPACKE_dgetrs(LAPACK_ROW_MAJOR,'N',NROWS,NROWS,onedimA,LEADING_DIMENSION_A,ipiv,onedimB,NROWS);
	//printf("solution info=%d\n",info);
	printf("Solution X:\n");
	for(i=0; i<n*n; i++){
		printf("%lf	 ",onedimB[i]);
		if(counter==n){
			printf("\n");
			counter=0;
		}
		counter ++;
	}
	printf("\n");
	/*info=LAPACKE_dgetri(LAPACK_ROW_MAJOR,n,onedimA,n,ipiv);
	printf("Inverse of X:\n");
	for(i=0; i<n*n; i++){
		printf("%lf		",onedimA[i]);
		if(counter==n){
			printf("\n");
			counter=0;
		}
		counter ++;
	}
	//printonedarray(onedimA,n*n);
	printf("\n");*/
}
