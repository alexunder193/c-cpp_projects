#include "functions.h"
#include <math.h>
#include <time.h>
#include <lapacke.h>
#include <cblas.h>

void printtwodarray(double ** x, int m, int n) {
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%lf	", x[i][j]);
        }
        printf("\n");
    }
}

void printonedarray(double * x, int m) {
    int i;
    for (i = 0; i < m; i++) {
        printf("%lf	", x[i]);
    }
}

double * convertToRowMajorMatrix(double ** x, int m, int n) {
    double * data = LAPACKE_malloc(n * m * sizeof (double));
    int i, j, k;
    k = 0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            data[k] = (double) x[i][j];
            k++;
        }
    }
    return data;
}

double ** convertToTwoDimensionMatrix(double * x, int m, int n, int one) {
    double ** data = LAPACKE_malloc(m * sizeof (double*));
    int i, j, k;
    for (i = 0; i < m; i++) {
        data[i] = LAPACKE_malloc(n * sizeof (double));
    }
    k = 0;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            data[i][j] = (double) x[k];
            k++;
        }
    }
    return data;
}

int fact(int n){
    int i;
    unsigned int factorial = 1;
    // show error if the user enters a negative integer
    if (n < 0)
        printf("Error! Factorial of a negative number doesn't exist.");

    else
    {
        for(i=1; i<=n; ++i)
        {
            factorial *= i;              // factorial = factorial*i;
        }
        //printf("Factorial of %d = %llu", n, factorial);
    }

    return factorial;
}



double** cofactor(double **num,double f){
 double **b;
 double **fac;
 double **ret;
 int p,q,m,n,i,j;
 b=malloc(f*sizeof(double *));
 for(i=0; i<f; i++){
 	b[i]=malloc(f*sizeof(double));
 }
 fac=malloc(f*sizeof(double *));
 for(i=0; i<f; i++){
 	fac[i]=malloc(f*sizeof(double));
 }
 for (q=0;q<f;q++)
 {
   for (p=0;p<f;p++)
    {
     m=0;
     n=0;
     for (i=0;i<f;i++)
     {
       for (j=0;j<f;j++)
        {
          if (i != q && j != p)
          {
            b[m][n]=num[i][j];
            if (n<(f-2))
             n++;
            else
             {
               n=0;
               m++;
               }
            }
        }
      }
      fac[q][p]=pow(-1,q + p) * determinant(b,f-1);
    }
  }
  ret=transpose(num,fac,f);
  return ret;
}



double determinant(double **a,double k){
  double s=1,det=0;
  double **b;
  int i,j,m,n,c;
  b=malloc(k*sizeof(double *));
  for(i=0; i<k; i++){
  	b[i]=malloc(k*sizeof(double));
  }
  if (k==1){
     return a[0][0];
  }
  else{
     det=0;
     for (c=0;c<k;c++)
       {
        m=0;
        n=0;
        for (i=0;i<k;i++)
          {
            for (j=0;j<k;j++)
              {
                b[i][j]=0;
                if (i != 0 && j != c)
                 {
                   b[m][n]=a[i][j];
                   if (n<(k-2))
                    n++;
                   else
                    {
                     n=0;
                     m++;
                     }
                   }
               }
             }
          det=det + s * (a[0][c] * determinant(b,k-1));
          s=-1 * s;
          }
    }
    return (det);
}



double** transpose(double **num,double **fac,double r){
  int i,j;
  float d;
  double **b;
  double **inverse;
  b=malloc(r*sizeof(double *));
  for(i=0; i<r; i++){
  	b[i]=malloc(r*sizeof(double));
  }
  inverse=malloc(r*sizeof(double *));
  for(i=0; i<r; i++){
  	inverse[i]=malloc(r*sizeof(double));
  } 
  for (i=0;i<r;i++)
    {
     for (j=0;j<r;j++)
       {
         b[i][j]=fac[j][i];
        }
    }
  d=determinant(num,r);
  for (i=0;i<r;i++)
    {
     for (j=0;j<r;j++)
       {
        inverse[i][j]=b[i][j] / d;
        }
    }
   //printf("\n\n\nThe inverse of matrix is : \n");
 
   for (i=0;i<r;i++)
    {
     for (j=0;j<r;j++)
       {
         //printf("\t%lf",inverse[i][j]);
        }
    //printf("\n");
     }
     return inverse;
}


