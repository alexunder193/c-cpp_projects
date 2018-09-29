#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <lapacke.h>
#include <cblas.h>
#include "functions.h"

int main(int argc, char *argv[]){
	int n,i,j,info;
	double **A;
	double **B;
	double *X;
	double *onedimA;
	double *onedimB;
	double *copyB;
	double *copyBB;
	double *minus;
	double *onedimassoi;
	double *AX;
	double *bminusAx;
	double *copyA;
	double **assoi;
	lapack_int *ipiv;
	clock_t t;
	int counter=1;
	printf("Give me the dimension of arrays:");
	scanf("%d",&n);
	t = clock();
	A=malloc(n*sizeof(double *));			//kataskeui A
	//B=malloc(n*sizeof(double *));
	for(i=0; i<n; i++){
		A[i]=malloc(n*sizeof(double));
		//B[i]=malloc(n*sizeof(double));
	}
	assoi=malloc(n*sizeof(double *));
	for(i=0; i<n; i++){
		assoi[i]=malloc(n*sizeof(double));
		//B[i]=malloc(n*sizeof(double));
	}
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			if(i==j)
				assoi[i][j]=1;
			else
				assoi[i][j]=0;
		}
	}
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			//a=fact(i+1+j+1-2);
			//b=fact(i+1-1);
			//c=fact(j+1-1);
			//A[i][j]=(double)a/(b*c);
			if(i==j)
				A[i][j]=n;
			else
				A[i][j]=(double)1/(i+1+j+1-1);
		}
	}
	//for(i=0; i<n; i++)
		//B[i][0]=1;
	printf("Array A:\n");
	printtwodarray(A,n,n);
	double d=determinant(A,n);
	//printf("Determinant of the Matrix = %lf",d);
	if (d==0)
   		printf("\nInverse of Entered Matrix is not possible\n");
  	else
   		B=cofactor(A,n);
	//printtwodarray(C,n,n);
	//printf("Array X:\n");
	//printtwodarray(B,n,n);
	onedimA=convertToRowMajorMatrix(A,n,n);
	onedimB=convertToRowMajorMatrix(B,n,n);
	onedimassoi=convertToRowMajorMatrix(assoi,n,n);
	//X=malloc(n*n*sizeof(double));
	//cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,n,n,n,1.0, onedimA,n,onedimB,n,0.0,X,n);
	//copyB=malloc(n*n*sizeof(double));
	//for(i=0; i<n*n; i++)
		//copyB[i]=X[i];
	ipiv=LAPACKE_malloc(n*sizeof(lapack_int));
	lapack_int NROWS = n;
	//info=LAPACKE_dgesv(LAPACK_ROW_MAJOR,NROWS,NROWS,onedimA,NROWS,ipiv,copyB,NROWS);
	/*printf("Solution without Factorization is:\n");
	for(i=0; i<n*n; i++){
		printf("%lf		",copyB[i]);
		if(counter==n){
			printf("\n");
			counter=0;
		}
		counter ++;
	}
	printf("\n");*/
	counter=1;
	copyA=malloc(n*n*sizeof(double));
	for(i=0; i<n*n; i++)
		copyA[i]=onedimA[i];
	//info=LAPACKE_dgetrf(LAPACK_ROW_MAJOR,NROWS,NROWS,copyA,NROWS,ipiv);
	info=LAPACKE_dpotrf(LAPACK_ROW_MAJOR,'L',NROWS,copyA,NROWS);
	info=LAPACKE_dpotri(LAPACK_ROW_MAJOR,'L',NROWS,copyA,NROWS);
	/*printf("Cholesky Factorization\n");
	for(i=0; i<n*n; i++){
		printf("%lf		",copyA[i]);
		if(counter==n){
			printf("\n");
			counter=0;
		}
		counter ++;
	}
	printf("\n");
	counter=1;*/
	//copyBB=malloc(n*n*sizeof(double));
	//for(i=0; i<n*n; i++){
		//copyBB[i]=X[i];
	//}
	//info=LAPACKE_dgetrs(LAPACK_ROW_MAJOR,'N',NROWS,NROWS,copyA,NROWS,ipiv,copyBB,NROWS);
	//info=LAPACKE_dpotrs(LAPACK_ROW_MAJOR,'L',NROWS,NROWS,copyA,NROWS,copyBB,NROWS);
	/*printf("Solution with Cholesky\n");
	for(i=0; i<n*n; i++){
		printf("%lf		",copyBB[i]);
		if(counter==n){
			printf("\n");
			counter=0;
		}
		counter ++;
	}
	printf("\n");
	counter=1;*/
	//////////////////////////////////////////////////
	minus=malloc(n*n*sizeof(double));
	for(i=0; i<n*n; i++){
		minus[i]=onedimB[i]-copyA[i];
	}
	double normover = LAPACKE_dlange(CblasRowMajor,'I',n,n,minus,n);
	double normunder = LAPACKE_dlange(CblasRowMajor,'I',n,n,onedimB,n);
    printf("Apoluto sxetiko sfalma=%lf \n", normover/normunder);
    ////////////////////////////////////////////////////
    AX=malloc(n*n*sizeof(double));
    cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,n,n,n,1.0, onedimA,n,copyA,n,0.0,AX,n);
    bminusAx=malloc(n*n*sizeof(double));
    for(i=0; i<n*n; i++){
    	bminusAx[i]=AX[i]-onedimassoi[i];
	}
	normover = LAPACKE_dlange(CblasRowMajor,'I',n,n,bminusAx,n);
	printf("Apoluto sxetiko upoloipo=%lf \n", normover/normunder);
	//////////////////////////////////////////////////////
	//info=LAPACKE_dgetri(LAPACK_ROW_MAJOR,n,copyA,n,ipiv);
	//info=LAPACKE_dpotri(LAPACK_ROW_MAJOR,'L',NROWS,copyA,NROWS);
	normover=LAPACKE_dlange(CblasRowMajor,'I',n,n,onedimA,n);
	normunder=LAPACKE_dlange(CblasRowMajor,'I',n,n,onedimB,n);
	printf("Condition number=%lf \n", normover*normunder);
	////////////////////////////////////////////////////////
	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("CPUtime=%f seconds \n", time_taken);
}
