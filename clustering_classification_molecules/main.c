#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <lapacke.h>
#include <cblas.h>
#include "domes.h"
#include <math.h>

int main(int argc, char *argv[]) {
	char filename[50];
    MoleculeCollectionPtr molecules;
    ClusterArrayPtr all_clusters;
    MoleculePtr * temp;
    MoleculePtr * temp1;
    int i, j, k,N,numofclusters,whichmetric;
    long curtime;
    CentroidsPtr centers;
    strcpy(filename,argv[1]);
    numofclusters=atoi(argv[2]);
    whichmetric=atoi(argv[3]);
    /*double ** X = malloc(sizeof(double*)*2);
    double ** Y = malloc(sizeof(double*)*2);
    
    for (i=0;i<2;i++) {
        X[i]  = malloc(sizeof(double)*3);
        Y[i]  = malloc(sizeof(double)*3);
    }
    X[0][0] = 0.1;
    X[0][1] = 0.2;
    X[0][2] = 0.3;
    X[1][0] = 0.4;
    X[1][1] = 0.5;
    X[1][2] = 0.6;
    Y[0][0] = 0.2;
    Y[0][1] = 0.4;
    Y[0][2] = 0.6;
    Y[1][0] = 0.8;
    Y[1][1] = 1.0;
    Y[1][2] = 1.2;*/
    //double y = crmsd(X, Y, 2);
    //y=discretefrechet(X, Y, 2);
    //printf("frechet metriki=%f\n",y);
    molecules = loadMolecules(filename);
    //printf("Oi moriakes diamorfoseis einai: %d\n",molecules->counter);
    temp=molecules->molecules;
    N=temp[0]->m;
    /*for(i=0; i<molecules->counter; i++){
            printf("Diamorfosh me id: %d\n",temp[i]->id);
            printf("Exei %d simeia ta opoia einai\n",temp[i]->m);
            for(j=0; j<temp[i]->m; j++){
                    for(k=0; k<3; k++){
                            printf("%Lf		",temp[i]->position[j][k]);
                    }
                    printf("\n");
            }
    }*/
    curtime = time(NULL);
    srand((unsigned int) curtime);
    centers = initialization_kmeanspp(molecules,numofclusters,N,whichmetric);
    //printf("Exei %d kentroeidh\n", centers->k);
    temp1 = centers->molecule;
    for (i = 0; i < centers->k; i++) {
        printf("Kentro me id: %d\n", temp1[i]->id);
        printf("Exei %d simeia ta opoia einai\n", temp1[i]->m);
    }
    printf("------------------------------------------------------------------------------\n");
    all_clusters = assignment_lloyd(molecules,centers,N,whichmetric);
    for (i = 0; i < centers->k; i++) {
        printf("Cluster #%d:  id:%d  items: %d \n", i, all_clusters->clusters[i].center->id, all_clusters->clusters[i].memberList->counter);
        MoleculeNodePtr t = all_clusters->clusters[i].memberList->head;
        while (t != NULL) {
            printf(" %d \n", t->molecule->id);
            //printf("simeia=%d \n", t->molecule->m);
            t = t->next;
        }
    }
    /*centers=update_mdfd(all_clusters,N);
    all_clusters=assignment_lloyd(molecules,centers, N, whichmetric);
        for (i = 0; i < centers->k; i++) {
        printf("Cluster #%d:  id:%d  items: %d \n", i, all_clusters->clusters[i].center->id, all_clusters->clusters[i].memberList->counter);
        MoleculeNodePtr t = all_clusters->clusters[i].memberList->head;
        while(t != NULL){
            printf(" %d \n", t->molecule->id);
            t = t->next;
        }
    }*/
}
