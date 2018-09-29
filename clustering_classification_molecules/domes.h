#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ---------------------------------------------------------
typedef struct Molecule * MoleculePtr;
typedef struct MoleculeCollection * MoleculeCollectionPtr;
typedef struct Centroids * CentroidsPtr;
typedef struct Cluster * ClusterPtr;
typedef struct ClusterArray * ClusterArrayPtr;
typedef struct MoleculeList * MoleculeListPtr;
typedef struct MoleculeNode * MoleculeNodePtr;
typedef struct SpotList * SpotListPtr;
typedef struct SpotNode * SpotNodePtr;
// ---------------------------------------------------------
typedef struct Molecule {
    int id; // id tou moriou
    int m; // number of points in the molecule    
    MoleculePtr best_center;
    MoleculePtr second_bestcenter;
    int flag;
    double best_min;
    double second_bestmin;
    double ** position; // 2-d array with the points
} Molecule;

typedef struct MoleculeCollection {
    MoleculePtr * molecules;	//deiktis se oles tis moriakes diamorfoseis
    int counter;		//posa moria
} MoleculeCollection;

typedef struct Centroids {
    MoleculePtr * molecule; // deiktis se pinaka me deiktes sta kentra
    int k;              // posa kentra exo
} Centroids;

typedef struct Cluster {
    MoleculePtr center;    // deiktis sto kentro
    MoleculeListPtr memberList;  // lista me kombous me deiktes sta meli tou cluster
} Cluster;

typedef struct ClusterArray {
    ClusterPtr clusters; // deiktis se pinaka me k clusters
    int k;                      
} ClusterArray;

typedef struct MoleculeList {
    MoleculeNodePtr head;	//deiktis ston proto kombo tis listas
    int counter;		//metritis posoi komboi yparxoun
} MoleculeList;

typedef struct MoleculeNode {
    MoleculePtr molecule; // pointer sto morio
    MoleculeNodePtr next; // pointer ston epomeno kombo
} MoleculeNode;

typedef struct SpotList {
	SpotNodePtr head;
	int counter;
}SpotList;

typedef struct SpotNode {
    //PointPtr point; // pointer stin kampul
    double **array;
    SpotNodePtr next; // pointer ston epomeno kombo
} SpotNode;
// ---------------------------------------------------------
MoleculeCollectionPtr loadMolecules(const char * filename);
double crmsd(double **x,double **y,int N);
double discretefrechet(double **X, double **Y, int N);
double frechet(double** XQ,double **Y,int N);
void printtwodarray(double ** x,int m,int n);
void printonedarray(double * x,int m);
void printonedarray_withnewln(double * x, int m);
double * convertToRowMajorMatrix(double ** x, int m, int n);
double ** convertToTwoDimensionMatrix(double * x, int m,int n,int one);
CentroidsPtr initialization_kmeanspp(MoleculeCollectionPtr collection, int k,int N,int whichmetric);
int uniform_distribution_int(int rangeLow, int rangeHigh);
ClusterArrayPtr assignment_lloyd(MoleculeCollectionPtr collection, CentroidsPtr kentra,int N,int whickmetric);
//double silhouette(ClusterArrayPtr all_clusters,int N,int whichmetric);
MoleculePtr frechet_curve(MoleculePtr c1, MoleculePtr c2,int N);
CentroidsPtr update_mdfd(ClusterArrayPtr all_clusters,int N); 
double euclidean(double x1,double y1,double z1,double x2,double y2,double z2);
