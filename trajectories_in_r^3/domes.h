#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Point * PointPtr;
typedef struct Curve * CurvePtr;
// -----------------------------------------------------------
typedef struct Tree * TreePtr;
typedef struct CurveTree * CurveTreePtr;
typedef struct SpotList * SpotListPtr;
typedef struct SpotNode * SpotNodePtr;
typedef struct CurveNode * CurveNodePtr;
typedef struct CurveList * CurveListPtr;
typedef struct ClusterArray * ClusterArrayPtr;
typedef struct Centroids * CentroidsPtr;
typedef struct Cluster * ClusterPtr;
// ------------------------------------------------------------
typedef struct CurveCollection * CurveCollectionPtr;
typedef struct GridCurve * GridCurvePtr;
typedef struct HashTableNode * HashTableNodePtr;
typedef struct HashTable * HashTablePtr;
typedef struct Grid * GridPtr;
typedef struct Vector * VectorPtr;
typedef struct Projection * ProjectionPtr;

// ---------------------------------------------------------

typedef struct Point {
    int dimension; // 2 or 3 or 4
    long double * position;
} Point;

typedef struct Curve {
    int id; // id tis kampulis
    int m; // number of points in the curve    
    PointPtr points; // pointer se dsimeio
    // *******************************************************************
    int flag;
    CurvePtr best_center;
    CurvePtr second_bestcenter;
    long double best_min;
    long double second_bestmin;
    // *******************************************************************
} Curve;

typedef struct CurveCollection {
    CurvePtr * curves;	//deiktis se oles tis kampules
    int counter;		//poses kampules
} CurveCollection;

// *******************************************************************
typedef struct Tree{
	CurvePtr deiktis;
	TreePtr right;
	TreePtr left;
}Tree;

typedef struct CurveTree{
	TreePtr head;
	int counter;
} CurveTree;

typedef struct CurveNode {
    CurvePtr curve; // pointer stin kampuli
    CurveNodePtr next; // pointer ston epomeno kombo
} CurveNode;

typedef struct CurveList {
    CurveNodePtr head;	//deiktis ston proto kombo tis listas
    int counter;		//metritis posoi komboi yparxoun
} CurveList;

typedef struct SpotNode {
    PointPtr point; // pointer stin kampuli
    SpotNodePtr next; // pointer ston epomeno kombo
} SpotNode;

typedef struct SpotList {
	SpotNodePtr head;
	int counter;
}SpotList;

typedef struct Centroids {
    CurvePtr * curve; // deiktis se pinaka me deiktes sta kentra
    int k;              // posa kentra exo
} Centroids;

typedef struct Cluster {
    CurvePtr center;    // deiktis sto kentro
    CurveListPtr memberList;  // lista me kombous me deiktes sta meli tou cluster
} Cluster;

typedef struct ClusterArray {
    ClusterPtr clusters; // deiktis se pinaka me k clusters
    int k;                      
} ClusterArray;


// *******************************************************************
typedef struct Grid {	
    long double delta;	//delta tou plegmatos
    long double* taf;	//dianusma taf
} Grid;

typedef struct GridCurve {		//i anaparastash tou grid curve
    int id;
    int m; // number of points in the curve
    PointPtr points; // pointer se Point
} GridCurve;

typedef struct Vector {		//i monodiastath kampuli xwris diplotupa
    int m; // number of points in the curve
    long double * components;
} Vector;

typedef struct Projection {		//dianusma r kai mikos dianusmatos r
    int r_length;
    long double * r;
} Projection;

typedef struct HashTableNode {		//komvos tis alusidas
    CurvePtr curve;		//deiktis se kampuli
    GridCurvePtr gridcurve;		//deiktis se kampuli anaristomeni se grid
    HashTableNodePtr next;		//deiktis se epomeno node
} HashTableNode;

typedef struct HashTable {
    GridPtr * grids;		//k grids 
    ProjectionPtr projection;		//o tupos tis provolis
    int k;
    int size;	//posa exei mesa
    HashTableNodePtr * nodes;
} HashTable;


float uniform_distribution(int rangeLow, int rangeHigh);		//kanoniki katanomi apo rangelow ews rangehigh double
int uniform_distribution_int(int rangeLow, int rangeHigh);			//kanoniki katanomi apo rangelow ews rangehigh int
CurveCollectionPtr loadCurves(const char * filename, int dimension, int *maxid, int *maxm);		//fortono tis kampules mou
CurveCollectionPtr loadQueries(const char * filename, int dimension, int *qcounter, int *maxm);		//fortono ta queries mou
GridPtr create_grid(int dimension);		//dimiourgo ta grids 
long double euclidean(Point p, Point q, int dimension);		//upologismos eukleidias apostasis 2 simeion
GridCurvePtr gridcurve(GridPtr g, CurvePtr p, int dimension);		//ftiaxno tin kampuli se grid morfi
GridCurvePtr mergecurves(GridCurvePtr g, GridCurvePtr p, int dimension);	//ka fores enono oles tis grid curves exontas vgal;ei diplotupa
long double frechet(CurvePtr c1, CurvePtr c2, int dimension);		//upologizo tin apostash frechet 2 kampulon
VectorPtr onedimension(GridCurvePtr p, int dimension);			//ta grids se monodiastath morfi
long double inner(VectorPtr, VectorPtr);		//upologisnos eosterikou ginomenou
unsigned long int innerWithModulo(VectorPtr a, VectorPtr b);	//upologisnos eosterikou ginomenou mod 2^32 -5
ProjectionPtr create_projection(int v_length);		//tuxaio dianusma gia esotweriko ginomeno me grid
unsigned long int Hashfunction(VectorPtr p, ProjectionPtr project);		//upologismos monadikou ari8mou
HashTablePtr * create_hashtable(CurveCollectionPtr collection, int k, int L, int maxid, int maxm, int dimension);		//dimiourgia tou hash table
int compareGridCurves(GridCurvePtr g, GridCurvePtr p,int dimension);		//sugrisi metaksu 2 grids
void solve_nn(HashTablePtr * hashtables, CurveCollectionPtr collection, CurveCollectionPtr queries, int k, int L, int maxid, int maxm, int dimension);
//solution gia proseggistiko plisiestero geitona
void solve_nn_query(HashTablePtr * hashtables, CurveCollectionPtr collection, CurvePtr query, int k, int L, int maxid, int maxm, int dimension);
void solve_nn_true(CurveCollectionPtr collection, CurveCollectionPtr queries, int k, int L, int maxid, int maxm, int dimension);

int solve_range_query(HashTablePtr * hashpointer, CurveCollectionPtr collection, CurvePtr query, double range, int k, int L, int maxid, int maxm, int dimension);

//solution gia pragmatiko plisiestero geitona
void solve_nn_query_true(CurveCollectionPtr collection, CurvePtr query, int k, int L, int maxid, int maxm, int dimension);
CentroidsPtr initialization_simpleapproach(CurveCollectionPtr collection, int k,int maxid,int dimension);
//CentroidsPtr initialization_dummyapproach(CurveCollectionPtr collection, int k, int maxid, int dimension);
CentroidsPtr initialization_kmeanspp(CurveCollectionPtr collection, int k,int maxid,int dimension);
ClusterArrayPtr assignment_lloyd(CurveCollectionPtr collection, CentroidsPtr kentra,int maxid,int dimension);
ClusterArrayPtr assignment_lsh(CurveCollectionPtr collection, CentroidsPtr kentra, int maxid, int dimension, HashTablePtr * hashtables, int k, int L, int maxM) ;
CurvePtr frechet_curve(CurvePtr c1, CurvePtr c2, int dimension);
CentroidsPtr update_mdfd(ClusterArrayPtr all_clusters,int dimension);
TreePtr newItem();
TreePtr insertTree(TreePtr pn);
unsigned int getLeaf(TreePtr pn,CurveNodePtr lista);
