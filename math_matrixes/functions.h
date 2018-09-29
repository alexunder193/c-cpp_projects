#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printtwodarray(double ** x,int m,int n);
void printonedarray(double * x,int m);
double * convertToRowMajorMatrix(double ** x, int m, int n);
double ** convertToTwoDimensionMatrix(double * x, int m,int n,int one);
int fact(int n);
double** cofactor(double **num,double f);
double determinant(double **a,double k);
double** transpose(double **num,double **fac,double r);
