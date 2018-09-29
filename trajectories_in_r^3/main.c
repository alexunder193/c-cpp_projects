#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "domes.h"
#include <math.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    HashTablePtr * hashtables;
    int maxM = 0;
    int maxid, maxm, clustersnumber, k, L, dimension, i, j, l;
    CentroidsPtr dummycenters, centers, centersmean, updatecenters;
    long curtime;
    CurvePtr *temp;
    PointPtr temp1;
    CurveCollectionPtr curves;
    ClusterArrayPtr all_clusters;
    char inputfile[30], configurationfile[30], outputfile[30], buffer[100];
    int loop1, loop2, loop3;
    int log;
    dimension = 2; /////////////////////diastasi///////////////
    curtime = time(NULL);
    srand((unsigned int) curtime);
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0)
            strcpy(inputfile, argv[i + 1]);
        else if (strcmp(argv[i], "-c") == 0)
            strcpy(configurationfile, argv[i + 1]);
        else if (strcmp(argv[i], "-o") == 0)
            strcpy(outputfile, argv[i + 1]);
    }
    curves = loadCurves(inputfile, dimension, &maxid, &maxM);
    //printf("maxid=%d\n", maxid);
    fp = fopen(configurationfile, "r");
    fscanf(fp, "%s", buffer);
    clustersnumber = atoi(buffer);

    //printf("Clusters number =%d\n", clustersnumber);
    fscanf(fp, "%s", buffer);
    k = atoi(buffer);
    //printf("k=%d\n", k);
    fscanf(fp, "%s", buffer);
    L = atoi(buffer);
    //printf("L=%d\n", L);

    ///////////////hash table//////////////
    hashtables = create_hashtable(curves, k, L, maxid, maxM, dimension);


    // -------------------------
    //    log = 0;
    log = 1;
    // -------------------------

    int globalcounter = 0;

    for (loop1 = 0; loop1 < 2; loop1++) {
        for (loop2 = 0; loop2 < 2; loop2++) {
            for (loop3 = 0; loop3 < 2; loop3++) {
                globalcounter++;
                printf("------------------------------------------ \n");
                printf("            Experiment %d \n", globalcounter);
                printf("------------------------------------------ \n");
                switch (globalcounter - 1) {
                    case 0:
                        printf("************  simpleapproach  -  Lloyd  -  MDFD *******************\n");
                        break;
                    case 1:
                        printf("************  simpleapproach  -  Lloyd  -  PAM  *******************\n");
                        break;
                    case 2:
                        printf("************  simpleapproach  -   LSH   -  MDFD *******************\n");
                        break;
                    case 3:
                        printf("************  simpleapproach  -   LSH   -  PAM  *******************\n");
                        break;
                    case 4:
                        printf("************  kmeans++        -  Lloyd  -  MDFD *******************\n");
                        break;
                    case 5:
                        printf("************  kmeans++        -  Lloyd  -  PAM  *******************\n");
                        break;
                    case 6:
                        printf("************  kmeans++        -  LSH    -  MDFD *******************\n");
                        break;
                    case 7:
                        printf("************  kmeans++        -  LSH    -  PAM  *******************\n");
                        break;
                }

                switch (loop1) {
                    case 0:
                        printf("------------------------ \n");
                        printf("  simpleapproach init : \n");
                        printf("------------------------ \n");
                        centers = initialization_simpleapproach(curves, clustersnumber, maxid, dimension);
                        break;
                    case 1:
                        printf("------------------------ \n");
                        printf("     kmeans init : \n");
                        printf("------------------------ \n");
                        centersmean = initialization_kmeanspp(curves, clustersnumber, maxid, dimension);
                        break;
                        //                    default:
                        //                        printf("------------------------ \n");
                        //                        printf("   dummycenters init : \n");
                        //                        printf("------------------------ \n");
                        //                        dummycenters = initialization_dummyapproach(curves, clustersnumber, maxid, dimension);
                        //                        centers = dummycenters; // for debugging
                        //                        break;
                }

                if (log == 1) {
                    temp = centers->curve;
                    printf("\nOi tuxaies kampules einai oi:\n");
                    for (i = 0; i < clustersnumber; i++) {
                        printf("Cluster #%d: \n", temp[i]->id);
                        //                        temp1 = temp[i]->points;
                        //                        for (j = 0; j < temp[i]->m; j++) {
                        //printf("x=%Lf\n",temp1[j].position[0]);
                        //printf("y=%Lf\n",temp1[j].position[1]);
                        //                        }
                    }
                }

                do {
                    switch (loop2) {
                        case 0:
                            printf("------------------------ \n");
                            printf(" Lloyd assignment: \n");
                            printf("------------------------ \n");

                            all_clusters = assignment_lloyd(curves, centers, maxid, dimension);
                            break;
                        case 1:
                            printf("------------------------ \n");
                            printf(" LSH assignment: \n");
                            printf("------------------------ \n");

                            all_clusters = assignment_lsh(curves, centers, maxid, dimension, hashtables, k, L, maxM);
                            break;
                    }

                    if (log == 1) {
                        for (i = 0; i < clustersnumber; i++) {
                            printf("Cluster: id:%d  items: %d \n", all_clusters->clusters[i].center->id, all_clusters->clusters[i].memberList->counter);
                        }
                    }

                    switch (loop3) {
                        case 0:
                            printf("------------------------ \n");
                            printf("   MDFD update: \n");
                            printf("------------------------ \n");

                            updatecenters = update_mdfd(all_clusters, dimension);
                            break;
                        case 1:
                            printf("------------------------ \n");
                            printf("   PAM update: \n");
                            printf("------------------------ \n");

                            //                            updatecenters = update_pam(all_clusters, dimension);
                            break;
                    }
                    break;
                } while (updatecenters != NULL);


                printf("++++++++++++++++++++++++++++++++++++++++++++++++++++ \n");


                for (i = 0; i < clustersnumber; i++) {
                    printf("Cluster #%d:  id:%d  items: %d \n", i, all_clusters->clusters[i].center->id, all_clusters->clusters[i].memberList->counter);
                    CurveNodePtr t = all_clusters->clusters[i].memberList->head;
                    while (t != NULL) {
                        printf(" %d \n", t->curve->id);
                        t = t->next;
                    }
                }

                printf("++++++++++++++++++++++++++++++++++++++++++++++++++++ \n");
            }

        }
    }


    //dummycenters = initialization_dummyapproach(curves, clustersnumber, maxid, dimension);
    //temp=centers->curve;
    //printf("Oi tuxaies kampules einai oi:");
    /*for(i=0; i<clustersnumber; i++){
        printf("%d\n",temp[i]->id);
        temp1=temp[i]->points;
        for(j=0; j<temp[i]->m; j++){
                //printf("x=%Lf\n",temp1[j].position[0]);
                //printf("y=%Lf\n",temp1[j].position[1]);
                }
        }*/

    //    temp = centersmean->curve;
    //    printf("Oi kmean kampules einai oi: \n");
    //    for (i = 0; i < clustersnumber; i++) {
    //        printf("%d\n", temp[i]->id);
    //        temp1 = temp[i]->points;
    //        for (j = 0; j < temp[i]->m; j++) {
    //            //printf("x=%Lf\n",temp1[j].position[0]);
    //            //printf("y=%Lf\n",temp1[j].position[1]);
    //        }
    //    }



    //queries = loadQueries(filename2, dimension, &queriescounter, &maxm);
    //




    //printf("###### \n");
    //printf("----------------------------------------------------- \n");
    //printf("Solving for estimated solution ... \n");
    //printf("----------------------------------------------------- \n");
    //
    //printf("----------------------------------------------------- \n");
    //printf("Solving for true solution ... \n");
    //printf("----------------------------------------------------- \n");
    //solve_nn_true(curves, queries, k, L, maxid, maxM, dimension );
    return 0;
}
