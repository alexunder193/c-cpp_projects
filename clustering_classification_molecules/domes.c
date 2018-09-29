#include "domes.h"
#include <math.h>
#include <time.h>
#include <lapacke.h>
#include <cblas.h>

MoleculeCollectionPtr loadMolecules(const char * filename) {
    FILE *fp;
    char buffer[100], number[50];
    MoleculeCollectionPtr collection;
    MoleculePtr * temp;
    int numofmolecules, N, i, j, k, length, a, m;
    double spot;
    fp = fopen(filename, "r");
    collection = malloc(sizeof (MoleculeCollection));
    if (collection == NULL)
        printf("Den mporesa na dimiourgiso struct MoleculeCollection");
    fscanf(fp, "%s", buffer);
    numofmolecules = atoi(buffer); //poses moriakes diamorfoseis exo
    fscanf(fp, "%s", number);
    N = atoi(number);
    collection->molecules = malloc(numofmolecules * sizeof (struct Molecule *));
    if (collection->molecules == NULL)
        printf("Den mporesa na dimiourgiso struct Molecule* mesa sto struct MoleculeCollection");
    temp = collection->molecules;
    for (i = 0; i < numofmolecules; i++) { ////gia kathe thesi tou pinaka me tis moriakes diamorfoseis
        temp[i] = malloc(sizeof (struct Molecule));
        if (temp[i] == NULL)
            printf("Den mporesa na dimiourgiso struct Molecule mesa sto struct MoleculeCollection");
        temp[i]->id = i;
        temp[i]->m = N;
        temp[i]->flag = 0;
        temp[i]->best_center = NULL;
        temp[i]->second_bestcenter = NULL;
        temp[i]->position = malloc(N * sizeof (double *));
        if (temp[i]->position == NULL)
            printf("Den mporesa na dimiourgiso 1 grammi");
        for (j = 0; j < N; j++) {
            temp[i]->position[j] = malloc(3 * sizeof (double));
            if (temp[i]->position[j] == NULL)
                printf("Den mporesa na dimiourgiso 3 stiles mesa stin grammi");
        }
        for (j = 0; j < N; j++) {
            for (k = 0; k < 3; k++) {
                fscanf(fp, "%s", buffer);
                sscanf(buffer, "%lf", &spot); //to simeio
                temp[i]->position[j][k] = spot;
            }
        }
    }
    collection->counter = numofmolecules;
    return collection;
}

double crmsd(double **X, double **Y, int N) {
    lapack_int info;
    double xiX, yiX, ziX, sumxX, sumyX, sumzX, xiY, yiY, ziY, sumxY, sumyY, sumzY;
    double ** XT;
    double ** VT;
    double * onedimensionXT;
    double * onedimensionX;
    double * onedimensionY;
    double * onedimensionVT;
    //double ** U;
    double ** V;
    double * W;
    double *Q;
    int i, j;
    lapack_int piv[3];
    lapack_int m = 3;
    lapack_int n = 3;
    lapack_int LDA = m;
    lapack_int LDV = n;
    sumxX = 0;
    sumyX = 0;
    sumzX = 0;
    sumxY = 0;
    sumyY = 0;
    sumzY = 0;
    for (i = 0; i < N; i++) {
        sumxX = sumxX + X[i][0];
        sumyX = sumyX + X[i][1];
        sumzX = sumzX + X[i][2];
        sumxY = sumxY + Y[i][0];
        sumyY = sumyY + Y[i][1];
        sumzY = sumzY + Y[i][2];
    }
    sumxX = sumxX / N;
    sumyX = sumyX / N;
    sumzX = sumzX / N;
    sumxY = sumxY / N;
    sumyY = sumyY / N;
    sumzY = sumzY / N;
    for (i = 0; i < N; i++) {
        X[i][0] = X[i][0] - sumxX;
        X[i][1] = X[i][1] - sumyX;
        X[i][2] = X[i][2] - sumzX;
        Y[i][0] = Y[i][0] - sumxY;
        Y[i][1] = Y[i][1] - sumyY;
        Y[i][2] = Y[i][2] - sumzY;
    }
    //    printf("X\n");
    //    printtwodarray(X, N, 3);
    //    printf("\n");
    XT = malloc(3 * sizeof (double *));
    if (XT == NULL)
        printf("Den mporesa na desmeuso grammi\n");
    for (i = 0; i < 3; i++) {
        XT[i] = malloc(N * sizeof (double));
        if (XT[i] == NULL)
            printf("Den mporesa na desmeuso stiles\n");
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < 3; j++) {
            XT[j][i] = X[i][j];
        }
    }
    //    printf("XT\n");
    //    printtwodarray(XT, 3, N);
    //    printf("\n");
    //    printf("Y\n");
    //    printtwodarray(Y, N, 3);
    //    printf("\n");
    onedimensionXT = convertToRowMajorMatrix(XT, 3, N); //kano tis 2 diastaseis 1 ston XT gia na mpei stin lapack
    onedimensionX = convertToRowMajorMatrix(X, N, 3); //kano tis 2 diastaseis 1 ston Y gia na mpei stin lapack
    onedimensionY = convertToRowMajorMatrix(Y, N, 3); //kano tis 2 diastaseis 1 ston Y gia na mpei stin lapack
    W = malloc(3 * 3 * sizeof (double));

    //    printf("##### X\n");
    //    printonedarray(onedimensionXT, 6);    
    //    printf("\n##### Y\n");
    //    printonedarray(onedimensionY, 6);
    //    
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 3, 3, N, 1.0, onedimensionXT, N, onedimensionY, 3, 0.0, W, 3); //XT*Y

    //    printonedarray(W, 9);
    //    printf("##### \n");


    //    exit(0);
    /*i = 0;
    W[i++] = 1;
    W[i++] = 2;
    W[i++] = 3;
    W[i++] = 4;
    W[i++] = 5;
    W[i++] = 6;
    W[i++] = 7;
    W[i++] = 8;
    W[i++] = 9;
     */

    double ** WW = convertToTwoDimensionMatrix(W, 3, 3, 9);
    //printtwodarray(WW, 3, 3);

    double * s = LAPACKE_malloc(sizeof (double)*m);
    double * u;
    double * v = LAPACKE_malloc(sizeof (double)*m * n);
    double * stat = LAPACKE_malloc(sizeof (double)*2 * n);
    memset(s, 0, sizeof (double)*m);
    memset(v, 0, sizeof (double)*n * m);
    memset(stat, 0, sizeof (double)*2 * n);

    info = LAPACKE_dgesvj(LAPACK_ROW_MAJOR, 'G', 'U', 'V', m, n, W, LDA, s, 0, v, LDV, stat);
    if (info > 0) {
        printf("The diagonal element of the triangular factor of A,\n");
        printf("U(%i,%i) is zero, so that A is singular;\n", info, info);
        printf("the solution could not be computed.\n");
        exit(1);
    }
    if (s[2] <= 0) {
        printf("#################################### LATHOS s33 == 0\n");

        //printf("\n##### W\n");
        //printonedarray_withnewln(W, 9);

        //printf("\n##### U\n");
        //printonedarray_withnewln(u, 9);

        //printf("\n##### V\n");
        //printonedarray_withnewln(v, 9);

        //printf("\n##### S\n");
        /*for (i = 0; i < 8; i++) {
            printf("%f ", s[i]);
        }*/
        //printf("\n");

        exit(0);
    }
    //U=convertToTwoDimensionMatrix(w,3,3,9);
    V = convertToTwoDimensionMatrix(v, 3, 3, 9);
    u = W;

    //    printf("\n##### U\n");
    //    printonedarray_withnewln(u, 9);
    //
    //    printf("\n##### V\n");
    //    printonedarray_withnewln(v, 9);

    VT = malloc(3 * sizeof (double *));
    if (VT == NULL)
        printf("Den mporesa na desmeuso grammi\n");
    for (i = 0; i < 3; i++) {
        VT[i] = malloc(3 * sizeof (double));
        if (VT[i] == NULL)
            printf("Den mporesa na desmeuso stiles\n");
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            VT[j][i] = V[i][j]; //upologismos VT
        }
    }
    onedimensionVT = convertToRowMajorMatrix(VT, 3, 3);

    //    printf("\n##### VT\n");
    //    printonedarray_withnewln(onedimensionVT, 9);

    Q = malloc(3 * 3 * sizeof (double));
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 3, 3, 3, 1.0, W, 3, onedimensionVT, 3, 0.0, Q, 3);

    //    printf("\n##### Q\n");
    //    printonedarray(Q, 9);

    double ** QQ = convertToTwoDimensionMatrix(Q, 3, 3, 9);
    //    printf("\n\n Q= \n");
    //    printtwodarray(QQ, 3, 3);

    // |Q| = 0.998

    // dgetrf
    LAPACKE_dgetrf(LAPACK_ROW_MAJOR, 3, 3, Q, 3, piv);


    double ** LU = convertToTwoDimensionMatrix(Q, 3, 3, 9);

    //    printf("\n\n LU= \n");
    //    printtwodarray(LU, 3, 3);


    double det = 1;

    for (i = 0; i < 3; i++) {
        if (piv[i] != i) {
            det = -det * LU[i][i];
        } else {
            det = det * LU[i][i];
        }
    }

    //printf("det Q = %lf \n", det);

    if (det < 0) {
        u[2] = -u[2];
        u[5] = -u[5];
        u[8] = -u[8];

        //        printf("\n##### U\n");
        //        printonedarray_withnewln(u, 9);
        //
        //        printf("\n##### onedimensionVT\n");
        //        printonedarray_withnewln(onedimensionVT, 9);

        for (i = 0; i < 9; i++) {
            Q[i] = 0;
        }
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 3, 3, 3, 1.0, u, 3, onedimensionVT, 3, 0.0, Q, 3);

        //printf("\n##### Q\n");
        //printonedarray_withnewln(Q, 9);
    }

    //    printf("\n##### Q\n");
    //    printonedarray_withnewln(Q, 9);


    double * XQ = malloc(N * 3 * sizeof (double));
    double * XQ_Y = malloc(N * 3 * sizeof (double));
     
    // https://software.intel.com/en-us/mkl-tutorial-c-multiplying-matrices-using-dgemm
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, 3, 3, 1.0, onedimensionX, 3, Q, 3, 0.0, XQ, 3);
    
    for (i = 0; i < N * 3; i++) {
        XQ_Y[i] = XQ[i] - onedimensionY[i];
    }

    double norm = LAPACKE_dlange(CblasRowMajor, 'F', N, 3, XQ_Y, 3);
    //printf("F-norm = %lf \n", norm);

    //    exit(0);
    return norm;
}

double discretefrechet(double **X, double **Y, int N) {
	    lapack_int info;
    double xiX, yiX, ziX, sumxX, sumyX, sumzX, xiY, yiY, ziY, sumxY, sumyY, sumzY;
    double ** XT;
    double ** VT;
    double ** XQtwod;
    double * onedimensionXT;
    double * onedimensionX;
    double * onedimensionY;
    double * onedimensionVT;
    //double ** U;
    double ** V;
    double * W;
    double *Q;
    int i, j;
    lapack_int piv[3];
    lapack_int m = 3;
    lapack_int n = 3;
    lapack_int LDA = m;
    lapack_int LDV = n;
    sumxX = 0;
    sumyX = 0;
    sumzX = 0;
    sumxY = 0;
    sumyY = 0;
    sumzY = 0;
    for (i = 0; i < N; i++) {
        sumxX = sumxX + X[i][0];
        sumyX = sumyX + X[i][1];
        sumzX = sumzX + X[i][2];
        sumxY = sumxY + Y[i][0];
        sumyY = sumyY + Y[i][1];
        sumzY = sumzY + Y[i][2];
    }
    sumxX = sumxX / N;
    sumyX = sumyX / N;
    sumzX = sumzX / N;
    sumxY = sumxY / N;
    sumyY = sumyY / N;
    sumzY = sumzY / N;
    for (i = 0; i < N; i++) {
        X[i][0] = X[i][0] - sumxX;
        X[i][1] = X[i][1] - sumyX;
        X[i][2] = X[i][2] - sumzX;
        Y[i][0] = Y[i][0] - sumxY;
        Y[i][1] = Y[i][1] - sumyY;
        Y[i][2] = Y[i][2] - sumzY;
    }
    //    printf("X\n");
    //    printtwodarray(X, N, 3);
    //    printf("\n");
    XT = malloc(3 * sizeof (double *));
    if (XT == NULL)
        printf("Den mporesa na desmeuso grammi\n");
    for (i = 0; i < 3; i++) {
        XT[i] = malloc(N * sizeof (double));
        if (XT[i] == NULL)
            printf("Den mporesa na desmeuso stiles\n");
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < 3; j++) {
            XT[j][i] = X[i][j];
        }
    }
    //    printf("XT\n");
    //    printtwodarray(XT, 3, N);
    //    printf("\n");
    //    printf("Y\n");
    //    printtwodarray(Y, N, 3);
    //    printf("\n");
    onedimensionXT = convertToRowMajorMatrix(XT, 3, N); //kano tis 2 diastaseis 1 ston XT gia na mpei stin lapack
    onedimensionX = convertToRowMajorMatrix(X, N, 3); //kano tis 2 diastaseis 1 ston Y gia na mpei stin lapack
    onedimensionY = convertToRowMajorMatrix(Y, N, 3); //kano tis 2 diastaseis 1 ston Y gia na mpei stin lapack
    W = malloc(3 * 3 * sizeof (double));

    //    printf("##### X\n");
    //    printonedarray(onedimensionXT, 6);    
    //    printf("\n##### Y\n");
    //    printonedarray(onedimensionY, 6);
    //    
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 3, 3, N, 1.0, onedimensionXT, N, onedimensionY, 3, 0.0, W, 3); //XT*Y

    //    printonedarray(W, 9);
    //    printf("##### \n");


    //    exit(0);
    /*i = 0;
    W[i++] = 1;
    W[i++] = 2;
    W[i++] = 3;
    W[i++] = 4;
    W[i++] = 5;
    W[i++] = 6;
    W[i++] = 7;
    W[i++] = 8;
    W[i++] = 9;
     */

    double ** WW = convertToTwoDimensionMatrix(W, 3, 3, 9);
    //printtwodarray(WW, 3, 3);

    double * s = LAPACKE_malloc(sizeof (double)*m);
    double * u;
    double * v = LAPACKE_malloc(sizeof (double)*m * n);
    double * stat = LAPACKE_malloc(sizeof (double)*2 * n);
    memset(s, 0, sizeof (double)*m);
    memset(v, 0, sizeof (double)*n * m);
    memset(stat, 0, sizeof (double)*2 * n);

    info = LAPACKE_dgesvj(LAPACK_ROW_MAJOR, 'G', 'U', 'V', m, n, W, LDA, s, 0, v, LDV, stat);
    if (info > 0) {
        printf("The diagonal element of the triangular factor of A,\n");
        printf("U(%i,%i) is zero, so that A is singular;\n", info, info);
        printf("the solution could not be computed.\n");
        exit(1);
    }
    if (s[2] <= 0) {
        printf("#################################### LATHOS s33 == 0\n");

        //printf("\n##### W\n");
        //printonedarray_withnewln(W, 9);

        //printf("\n##### U\n");
        //printonedarray_withnewln(u, 9);

        //printf("\n##### V\n");
        //printonedarray_withnewln(v, 9);

        //printf("\n##### S\n");
        /*for (i = 0; i < 8; i++) {
            printf("%f ", s[i]);
        }*/
        //printf("\n");

        exit(0);
    }
    //U=convertToTwoDimensionMatrix(w,3,3,9);
    V = convertToTwoDimensionMatrix(v, 3, 3, 9);
    u = W;

    //    printf("\n##### U\n");
    //    printonedarray_withnewln(u, 9);
    //
    //    printf("\n##### V\n");
    //    printonedarray_withnewln(v, 9);

    VT = malloc(3 * sizeof (double *));
    if (VT == NULL)
        printf("Den mporesa na desmeuso grammi\n");
    for (i = 0; i < 3; i++) {
        VT[i] = malloc(3 * sizeof (double));
        if (VT[i] == NULL)
            printf("Den mporesa na desmeuso stiles\n");
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            VT[j][i] = V[i][j]; //upologismos VT
        }
    }
    onedimensionVT = convertToRowMajorMatrix(VT, 3, 3);

    //    printf("\n##### VT\n");
    //    printonedarray_withnewln(onedimensionVT, 9);

    Q = malloc(3 * 3 * sizeof (double));
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 3, 3, 3, 1.0, W, 3, onedimensionVT, 3, 0.0, Q, 3);

    //    printf("\n##### Q\n");
    //    printonedarray(Q, 9);

    double ** QQ = convertToTwoDimensionMatrix(Q, 3, 3, 9);
    //    printf("\n\n Q= \n");
    //    printtwodarray(QQ, 3, 3);

    // |Q| = 0.998

    // dgetrf
    LAPACKE_dgetrf(LAPACK_ROW_MAJOR, 3, 3, Q, 3, piv);


    double ** LU = convertToTwoDimensionMatrix(Q, 3, 3, 9);

    //    printf("\n\n LU= \n");
    //    printtwodarray(LU, 3, 3);


    double det = 1;

    for (i = 0; i < 3; i++) {
        if (piv[i] != i) {
            det = -det * LU[i][i];
        } else {
            det = det * LU[i][i];
        }
    }

    //printf("det Q = %lf \n", det);

    if (det < 0) {
        u[2] = -u[2];
        u[5] = -u[5];
        u[8] = -u[8];

        //        printf("\n##### U\n");
        //        printonedarray_withnewln(u, 9);
        //
        //        printf("\n##### onedimensionVT\n");
        //        printonedarray_withnewln(onedimensionVT, 9);

        for (i = 0; i < 9; i++) {
            Q[i] = 0;
        }
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 3, 3, 3, 1.0, u, 3, onedimensionVT, 3, 0.0, Q, 3);

        //printf("\n##### Q\n");
        //printonedarray_withnewln(Q, 9);
    }

    //    printf("\n##### Q\n");
    //    printonedarray_withnewln(Q, 9);


    double * XQ = malloc(N * 3 * sizeof (double));
    //double * XQ_Y = malloc(N * 3 * sizeof (double));
     
    // https://software.intel.com/en-us/mkl-tutorial-c-multiplying-matrices-using-dgemm
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, 3, 3, 1.0, onedimensionX, 3, Q, 3, 0.0, XQ, 3);
    XQtwod = convertToTwoDimensionMatrix(XQ, N, 3, N * 3);
    return frechet(XQtwod, Y, N);
}


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

void printonedarray_withnewln(double * x, int m) {
    int i;
    for (i = 0; i < m; i++) {
        printf("%lf	", x[i]);
        if (i == 2 || i == 5 || i == 8) {
            printf("\n");
        }
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

double frechet(double** XQ, double **Y, int N) {
    int i, j, n, m;
    double ** array;
    double distance1, distance2, distance3, distance4;
    n = N;
    m = N;
    array = malloc(n * sizeof (double*));
    for (i = 0; i < n; i++) {
        array[i] = malloc(m * sizeof (double));
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (i == 0 && j == 0) {
                array[i][j] = euclidean(XQ[i][0], XQ[i][1], XQ[i][2], Y[j][0], Y[j][1], Y[j][2]);
            } else if (i == 0) {
                distance1 = euclidean(XQ[i][0], XQ[i][1], XQ[i][2], Y[j][0], Y[j][1], Y[j][2]);
                distance2 = array[i][j - 1];
                if (distance1 >= distance2)
                    array[i][j] = distance1;
                else
                    array[i][j] = distance2;
            } else if (j == 0) {
                distance1 = euclidean(XQ[i][0], XQ[i][1], XQ[i][2], Y[j][0], Y[j][1], Y[j][2]);
                distance2 = array[i - 1][j];
                if (distance1 >= distance2)
                    array[i][j] = distance1;
                else
                    array[i][j] = distance2;
            } else {
                distance1 = euclidean(XQ[i][0], XQ[i][1], XQ[i][2], Y[j][0], Y[j][1], Y[j][2]);
                distance2 = array[i - 1][j];
                distance3 = array[i][j - 1];
                distance4 = array[i - 1][j - 1];

                double m1 = (distance2 < distance3) ? distance2 : distance3;
                double m2 = (m1 < distance4) ? m1 : distance4;

                array[i][j] = (distance1 > m2) ? distance1 : m2;
            }
        }
    }
    return array[n - 1][m - 1];
}

CentroidsPtr initialization_kmeanspp(MoleculeCollectionPtr collection, int k, int N, int whichmetric) {
    int random, i, j, q, t, v, n;
    double * mincenter;
    double * D;
    double sum, f, min, max;
    MoleculePtr * diamorfoseis;
    MoleculePtr * temp;
    CentroidsPtr kentra;
    t = 0;
    diamorfoseis = collection->molecules;
    kentra = malloc(sizeof (struct Centroids));
    kentra->k = k;
    kentra->molecule = malloc(k * sizeof (struct Molecule *));
    if (kentra->molecule == NULL)
        printf("Den mporesa na dimiourgiso struct Molecule * mesa sto struct Centroids");
    temp = kentra->molecule;
    random = uniform_distribution_int(0, collection->counter - 1);
    temp[0] = malloc(sizeof (struct Molecule));
    if (temp[0] == NULL)
        printf("Den mporesa na dimiourgiso struct Molecule mesa sto struct MoleculeCollection");
    temp[0]->id = diamorfoseis[random]->id;
    temp[0]->m = diamorfoseis[random]->m;
    temp[0]->best_center = diamorfoseis[random]->best_center;
    temp[0]->second_bestcenter = diamorfoseis[random]->second_bestcenter;
    temp[0]->position = malloc(diamorfoseis[random]->m * sizeof (double *));
    if (temp[0]->position == NULL)
        printf("Den mporesa na dimiourgiso 1 grammi");
    for (j = 0; j < diamorfoseis[random]->m; j++) {
        temp[0]->position[j] = malloc(3 * sizeof (double));
        if (temp[0]->position[j] == NULL)
            printf("Den mporesa na dimiourgiso 3 stiles mesa stin grammi");
    }
    for (i = 0; i < diamorfoseis[random]->m; i++) {
        for (j = 0; j < 3; j++) {
            temp[0]->position[i][j] = diamorfoseis[random]->position[i][j];
        }
    }
    t++; //plithos kentron mexri tora
    diamorfoseis[random]->flag = 1; //vazo simadi sta kentra pou exo idi sto struct Centroids
    D = malloc(collection->counter * sizeof (double));
    for (i = 0; i < collection->counter; i++)
        D[i] = 0;
    for (t = 1; t < k; t++) {
        for (v = 0; v < collection->counter; v++) { //gia kathe morio tou dataset
            if (diamorfoseis[v]->flag == 1) {
                D[v] = -1;
                continue;
            }
            mincenter = malloc(t * sizeof (double));
            for (i = 0; i < t; i++) { //gia kathe kentroeides
                if (whichmetric == 0)
                    mincenter[i] = crmsd(temp[i]->position, diamorfoseis[v]->position, N); //frechet(temp[i], diamorfoseis[v]);///////////////////////////////
                    //printf("tuxaios=%lf\n", mincenter[i]);
                else
                    mincenter[i] = discretefrechet(temp[i]->position, diamorfoseis[v]->position, N);
            }
            min = mincenter[0];
            if (t != 1) {
                for (i = 1; i < t; i++) {
                    if (mincenter[i] < min)
                        min = mincenter[i];
                }
            }
            min = min*min;
            D[v] = min;
            free(mincenter);
        }
        sum = 0;
        for (i = 0; i < collection->counter; i++) {
            if (D[i] == -1)
                continue;
            sum = sum + D[i];
            D[i] = sum;
        }
        max = D[0];
        for (i = 1; i < collection->counter; i++) {
            if (D[i] > max)
                max = D[i];
        }
        //printf("max=%Lf\n", max);
        f = (double) rand() / RAND_MAX;
        //printf("f=%Lf\n", f);
        f = 0 + f * (max);
        //printf("f=%Lf\n", f);
        for (i = 0; i < collection->counter; i++) {
            if (f < D[i])
                break;
        }
        //printf("i=%d\n", i);
        random = i;
        temp[t] = malloc(sizeof (struct Molecule));
        if (temp[t] == NULL)
            printf("Den mporesa na dimiourgiso struct Curve mesa sto struct CurveCollection");
        temp[t]->id = diamorfoseis[random]->id;
        temp[t]->m = diamorfoseis[random]->m;
        temp[t]->best_center = diamorfoseis[random]->best_center;
        temp[t]->second_bestcenter = diamorfoseis[random]->second_bestcenter;
        temp[t]->position = malloc(diamorfoseis[random]->m * sizeof (double *));
        if (temp[t]->position == NULL)
            printf("Den mporesa na dimiourgiso 1 grammi");
        for (j = 0; j < diamorfoseis[random]->m; j++) {
            temp[t]->position[j] = malloc(3 * sizeof (double));
            if (temp[t]->position[j] == NULL)
                printf("Den mporesa na dimiourgiso 3 stiles mesa stin grammi");
        }
        for (n = 0; n < diamorfoseis[random]->m; n++) {
            for (j = 0; j < 3; j++) {
                temp[t]->position[n][j] = diamorfoseis[random]->position[n][j];
            }
        }
    }
    free(D);
    return kentra;
}

int uniform_distribution_int(int rangeLow, int rangeHigh) ///////apo stack oerflow etoimi epostrefei int me kanoniki katanomi sto [rangelow,rangehigh]
{
    int range = rangeHigh - rangeLow;
    float copies = RAND_MAX / (float) range; // we can fit n-copies of [0...range-1] into RAND_MAX
    // Use rejection sampling to avoid distribution errors
    float limit = range*copies;
    float myRand = -1;
    while (myRand < 0 || myRand >= limit) {
        myRand = rand();
    }
    return (int) (myRand / copies + rangeLow); // note that this involves the high-bits
}

double euclidean(double x1, double y1, double z1, double x2, double y2, double z2) {
    double distance;
    distance = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));
    return distance;
}

ClusterArrayPtr assignment_lloyd(MoleculeCollectionPtr collection, CentroidsPtr kentra, int N, int whichmetric) {
    int i, j, thesi, secthesi;
    double min, secmin;
    double * tempdistance;
    ClusterArrayPtr all_clusters;
    MoleculeNodePtr komvos;
    MoleculeListPtr lista;
    MoleculePtr * kentroeidi;
    MoleculePtr * temp;
    kentroeidi = kentra->molecule;
    temp = collection->molecules;
    // k = 1 ???
    all_clusters = malloc(sizeof (struct ClusterArray));
    if (all_clusters == NULL)
        printf("Den mporesa na dimiourgiso ClusterArray");
    all_clusters->k = kentra->k;
    all_clusters->clusters = malloc(all_clusters->k * sizeof (struct Cluster));
    for (i = 0; i < all_clusters->k; i++) {
        all_clusters->clusters[i].center = kentroeidi[i];
        all_clusters->clusters[i].memberList = malloc(sizeof (struct MoleculeList));
        all_clusters->clusters[i].memberList->counter = 0;
        all_clusters->clusters[i].memberList->head = NULL;
    }
    tempdistance = malloc(all_clusters->k * sizeof (double));
    for (i = 0; i < collection->counter; i++) {
        //tempdistance=malloc(all_clusters->k*sizeof(double));
        for (j = 0; j < all_clusters->k; j++)
            if (whichmetric == 0)
                tempdistance[j] = crmsd(temp[i]->position, kentroeidi[j]->position, N); //frechet(temp[i], kentroeidi[j]);
            else
                tempdistance[j] = discretefrechet(temp[i]->position, kentroeidi[j]->position, N);
        min = tempdistance[0];
        thesi = 0;
        for (j = 1; j < all_clusters->k; j++) {
            if (tempdistance[j] < min) {
                min = tempdistance[j];
                thesi = j;
            }
        }
        secmin = tempdistance[0];
        secthesi = 0;
        for (j = 1; j < all_clusters->k; j++) {
            if (tempdistance[j] > min && tempdistance[j] < secmin) {
                secmin = tempdistance[j];
                secthesi = j;
            }
        }
        temp[i]->best_center = kentroeidi[thesi];
        temp[i]->best_min = min;
        temp[i]->second_bestcenter = kentroeidi[secthesi];
        temp[i]->second_bestmin = secmin;
        lista = all_clusters->clusters[thesi].memberList;
        komvos = malloc(sizeof (struct MoleculeNode));
        komvos->next = lista->head;
        komvos->molecule = temp[i]; //[thesi]
        lista->head = komvos;
        lista->counter++;
    }
    free(tempdistance);
    return all_clusters;
}


MoleculePtr frechet_curve(MoleculePtr c1, MoleculePtr c2, int N) {
    SpotListPtr lista;
    SpotNodePtr komvos, temp, temp1;
    MoleculePtr molecule;
    int minldx;
    int n = c1->m;
    //printf("n=%d\n",n);
    int m = c2->m;
    //printf("m=%d\n",m);
    //double array[n][m];
    double ** array;
    double distance1, distance2, distance3, distance4;
    int i, j, k;
    array = malloc(n * sizeof (double*));
    for (int i = 0; i < n; i++) {
        array[i] = malloc(m * sizeof (double));
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (i == 0 && j == 0) {
                array[i][j] = euclidean(c1->position[i][0], c1->position[i][1], c1->position[i][2], c2->position[j][0], c2->position[j][1], c2->position[j][2]);
            } else if (i == 0) {
                distance1 = euclidean(c1->position[i][0], c1->position[i][1], c1->position[i][2], c2->position[j][0], c2->position[j][1], c2->position[j][2]);
                distance2 = array[i][j - 1];
                if (distance1 >= distance2)
                    array[i][j] = distance1;
                else
                    array[i][j] = distance2;
            } else if (j == 0) {
                distance1 = euclidean(c1->position[i][0], c1->position[i][1], c1->position[i][2], c2->position[j][0], c2->position[j][1], c2->position[j][2]);
                distance2 = array[i - 1][j];
                if (distance1 >= distance2)
                    array[i][j] = distance1;
                else
                    array[i][j] = distance2;
            } else {
                distance1 = euclidean(c1->position[i][0], c1->position[i][1], c1->position[i][2], c2->position[j][0], c2->position[j][1], c2->position[j][2]);
                distance2 = array[i - 1][j];
                distance3 = array[i][j - 1];
                distance4 = array[i - 1][j - 1];

                double m1 = (distance2 < distance3) ? distance2 : distance3;
                double m2 = (m1 < distance4) ? m1 : distance4;

                array[i][j] = (distance1 > m2) ? distance1 : m2;
            }
        }
    }
    //////////////////////
    int pi = n - 1;
    int qi = m - 1;
    lista = malloc(sizeof (struct SpotList));
    lista->head = NULL;
    lista->counter = 0;
    komvos = malloc(sizeof (struct SpotNode));
    komvos->array = malloc(N * sizeof (double *));
    for (i = 0; i < N; i++) {
        komvos->array[i] = malloc(3 * sizeof (double));
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < 3; j++) {
            komvos->array[i][j] = (c1->position[pi][j] + c2->position[qi][j]) / 2;
        }
    }
    komvos->next = lista->head;
    lista->head = komvos;
    lista->counter++;
    while (pi != 0 && qi != 0) {
        if ((array[pi - 1][qi] <= array[pi][qi - 1]) && (array[pi - 1][qi] <= array[pi - 1][qi - 1])) {
            minldx = array[pi - 1][qi];
        } else if ((array[pi][qi - 1] <= array[pi - 1][qi]) && (array[pi][qi - 1] <= array[pi - 1][qi - 1])) {
            minldx = array[pi][qi - 1];
        } else if ((array[pi - 1][qi - 1] <= array[pi - 1][qi]) && (array[pi - 1][qi - 1] <= array[pi][qi - 1])) {
            minldx = array[pi - 1][qi - 1];
        }
        if (minldx == 0) {
            --pi;
        } else if (minldx == 1) {
            --qi;
        } else {
            --pi;
            --qi;
        }
        temp = malloc(sizeof (struct SpotNode));
        temp->array = malloc(N * sizeof (double *));
        for (i = 0; i < N; i++) {
            temp->array[i] = malloc(3 * sizeof (double));
        }
        for (i = 0; i < N; i++) {
            for (j = 0; j < 3; j++) {
                temp->array[i][j] = (c1->position[pi][j] + c2->position[qi][j]) / 2;
            }
        }
        temp->next = lista->head;
        lista->head = temp;
        lista->counter++;
    }
    while (pi != 0) {
        --pi;
        temp = malloc(sizeof (struct SpotNode));
        temp->array = malloc(N * sizeof (double *));
        for (i = 0; i < N; i++) {
            temp->array[i] = malloc(3 * sizeof (double));
        }
        for (i = 0; i < N; i++) {
            for (j = 0; j < 3; j++) {
                temp->array[i][j] = (c1->position[pi][j] + c2->position[qi][j]) / 2;
            }
        }
        temp->next = lista->head;
        lista->head = temp;
        lista->counter++;
    }
    while (qi != 0) {
        --qi;
        temp = malloc(sizeof (struct SpotNode));
        temp->array = malloc(N * sizeof (double *));
        for (i = 0; i < N; i++) {
            temp->array[i] = malloc(3 * sizeof (double));
        }
        for (i = 0; i < N; i++) {
            for (j = 0; j < 3; j++) {
                temp->array[i][j] = (c1->position[pi][j] + c2->position[qi][j]) / 2;
            }
        }
        temp->next = lista->head;
        lista->head = temp;
        lista->counter++;
    }
    temp1 = lista->head;
    //////////kampili epistrofis/////////
    molecule = malloc(sizeof (struct Molecule));
    molecule->m = lista->counter;
    printf("i curve exei %d simeia\n",molecule->m);
    molecule->position = malloc(N * sizeof (double *));
    if (molecule->position == NULL)
        printf("Den mporesa na dimiourgiso 1 grammi");
    for (j = 0; j < N; j++) {
        molecule->position[j] = malloc(3 * sizeof (double));
        if (molecule->position[j] == NULL)
            printf("Den mporesa na dimiourgiso 3 stiles mesa stin grammi");
    }
    for (j = 0; j < N; j++) {
        for (k = 0; k < 3; k++) {
            molecule->position[j][k] = temp1->array[j][k];
        }
    }
    return molecule;
}

CentroidsPtr update_mdfd(ClusterArrayPtr all_clusters, int N) {
    int i, j, number_of_leaves, temp, number_of_all_nodes, m;
    MoleculeNodePtr lista;
    CentroidsPtr centers = malloc(sizeof (Centroids));
    centers->k = all_clusters->k;
    centers->molecule = malloc(centers->k * sizeof (MoleculePtr));
    for (i = 0; i < all_clusters->k; i++) { //gia kathe cluster
        centers->molecule[i] = NULL;
    }
    for (i = 0; i < all_clusters->k; i++) { //gia kathe cluster
        number_of_leaves = all_clusters->clusters[i].memberList->counter; //poses curves exei to cluster
        lista = all_clusters->clusters[i].memberList->head;
        number_of_all_nodes = number_of_leaves;
        temp = number_of_leaves;
        if (temp == 0) {
            return NULL;
        }
        number_of_all_nodes = number_of_leaves * 2 - 1;
        MoleculePtr * tree = malloc(sizeof (MoleculePtr)*(1 + number_of_all_nodes));
        tree[0] = NULL;
        // initialize leaves
        for (j = 0; j < number_of_leaves; j++) {
            tree[number_of_all_nodes - j] = lista->molecule;
            lista = lista->next;
        }
        // for each inner node
        for (j = number_of_all_nodes / 2; j >= 1; j--) {
            int left = j * 2;
            int right = j * 2 + 1;
            if (left <= number_of_all_nodes && right <= number_of_all_nodes) { // 2 children
                MoleculePtr leftmolecule = tree[left];
                MoleculePtr rightmolecule = tree[right];
                //printf("heloooooo\n");
                MoleculePtr mdfc = frechet_curve(leftmolecule, rightmolecule, N);
                tree[j] = mdfc;
            } else if (left <= number_of_all_nodes) { // 1 child
                tree[j] = tree[left];
            } else { // no children (error)
                printf("oime kai tris ali \n");
                exit(0);
            }
        }
        centers->molecule[i] = tree[1];
    }
    return centers;
}



/*double silhouette(ClusterArrayPtr all_clusters,int N,int whichmetric){
	double * suma;
	double * sumb;
	double **x;
	int i,a;
	suma=malloc(all_clusters->k*sizeof(double));
	sumb=malloc(all_clusters->k*sizeof(double));
	for(i=0; i<all_clusters->k; i++){
		suma[i]=0.0;
		sumb[i]=0.0;
	}
	for (i = 0; i < all_clusters->k; i++){
		MoleculeNodePtr t = all_clusters->clusters[i].memberList->head;
		x=t->molecule->position;
		t=t->next;
		 while (t != NULL){
		 	suma[i]=suma[i]+crmsd(x,t->molecule->position,N);
		 	t=t->next;
		 }
		 suma[i]=suma[i]/(all_clusters->clusters[i].memberList->counter);
	}
	//////////////////////////////////////////////
	for (i = 0; i < all_clusters->k; i++){
		t = all_clusters->clusters[i].memberList->head;
		
	}
}*/
