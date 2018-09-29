#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <lapacke.h>
#include <cblas.h>
#include <math.h>
#include "functions.h"

int main(int argc, char *argv[]){
	int n,i,j,info,a,b,c,d,e,f,g,h;
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
			A[i][j]=(double)1/(i+1+j+1-1);
			a=pow(-1,i+1+j+1);
			b=fact(n+i+1-1);
			c=fact(n+j+1-1);
			d=i+1+j+1-1;
			e=fact(i+1-1)*fact(j+1-1);
			h=pow(e,2);
			f=fact(n-i+1);
			g=fact(n-j+1);
			B[i][j]=(double)(a*b*c)/(d*h*f*g);
		}
	}
	printtwodarray(A,n,n);
	printf("\n");
	//printf("Inverse of X epalitheusi:\n");
	//printtwodarray(B,n,n);
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
