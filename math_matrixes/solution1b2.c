#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <lapacke.h>
#include <cblas.h>
#include "functions.h"

int main(int argc, char *argv[]){
	int n,i,j,info;
	double *onedimA;
	double **A;
	double **B;
	int counter=1;
	lapack_int *ipiv;
	////////////////////////////////////////////////////////////////////////////
	printf("Give me the dimension of array:");
	scanf("%d",&n);
	A=malloc(n*sizeof(double *));			//kataskeui A
	for(i=0; i<n; i++){
		A[i]=malloc(n*sizeof(double));
	}
	B=malloc(n*sizeof(double *));			//kataskeui A
	for(i=0; i<n; i++){
		B[i]=malloc(n*sizeof(double));
	}
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			if(i==j){
				A[i][j]=n;
				B[i][j]=(double)2/(2*n-1);
			}
			else{
				A[i][j]=1;
				B[i][j]=(double)-1/((n-1)*(2*n-1));
			}
		}
	}
	printtwodarray(A,n,n);
	printf("\n");
	printf("Inverse of X epalitheusi:\n");
	printtwodarray(B,n,n);
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
