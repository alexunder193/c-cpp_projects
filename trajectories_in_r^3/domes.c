#include "domes.h"
#include <math.h>
#include <time.h>

float uniform_distribution(int rangeLow, int rangeHigh) ///////apo stack oerflow etoimi epistrefei apo[tangelow,rangehigh] me kanoniki katanomi tuxaious
{
    float range = rangeHigh - rangeLow;
    float copies = RAND_MAX / range; // we can fit n-copies of [0...range-1] into RAND_MAX
    // Use rejection sampling to avoid distribution errors
    float limit = range*copies;
    float myRand = -1;
    while (myRand < 0 || myRand >= limit) {
        myRand = rand();
    }
    return myRand / copies + rangeLow; // note that this involves the high-bits  
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

CurveCollectionPtr loadCurves(const char * filename, int dimension, int *maxid, int *maxm) {
    FILE *fp;
    long double spot;
    char buffer[100], number[50];
    CurvePtr* temp;
    PointPtr temp1;
    int a, curveid, plithos, i, max, max2 = 0, j, k, m, length;
    CurveCollectionPtr collection;
    fp = fopen(filename, "r");
    while (!feof(fp)) { //proto perasma tou arxeiou gia na vroume to plithos ton kampilon meso tou megaliterou id
        fscanf(fp, "%s", buffer);
        curveid = atoi(buffer);
        fscanf(fp, "%s", buffer);
        plithos = atoi(buffer);
        if (plithos > max2) {
            max2 = plithos;
        }
        for (i = 0; i < dimension * plithos; i++) {
            fscanf(fp, "%s", buffer);
        }
    }
    *maxid = curveid; //plithos kampulon
    *maxm = max2; //max=arithmos simeion tis kampilis me ta prisssotera simeia
    max = *maxid;
    fclose(fp);
    ///////////////////////
    ///////////////////////
    fp = fopen(filename, "r");
    collection = malloc(sizeof (CurveCollection));
    if (collection == NULL)
        printf("Den mporesa na dimiourgiso struct CurveCollection");
    collection->curves = malloc((max + 1) * sizeof (struct Curve *)); //deftero perasma tou arxeiou gia eisagogoi kampulon se structs
    if (collection->curves == NULL)
        printf("Den mporesa na dimiourgiso struct Curve* mesa sto struct CurveCollection");
    temp = collection->curves;
    for (i = 0; i <= max; i++) { ////gia kathe thesi tou pinaka kampulon
        fscanf(fp, "%s", buffer);
        curveid = atoi(buffer); //id tis kampulis
        temp[i] = malloc(sizeof (struct Curve));
        if (temp[i] == NULL)
            printf("Den mporesa na dimiourgiso struct Curve mesa sto struct CurveCollection");
        temp[i]->id = curveid;
        fscanf(fp, "%s", buffer);
        //printf("%d \n", temp[i]->id);
        plithos = atoi(buffer); //plithos simeion
        temp[i]->m = plithos;
        temp[i]->flag = 0;
        temp[i]->best_center = NULL;
        temp[i]->second_bestcenter = NULL;
        temp[i]->points = malloc(plithos * sizeof (struct Point));
        if (temp[i]->points == NULL)
            printf("Den mporesa na dimiourgiso struct Point mesa sto struct Curve");
        temp1 = temp[i]->points;
        for (j = 0; j < plithos; j++) {
            temp1[j].dimension = dimension;
            temp1[j].position = malloc(dimension * sizeof (long double));
            if (temp1->position == NULL)
                printf("Den mporesa na dimiourgiso %d simeia\n", dimension);
            for (k = 0; k < dimension; k++) {
                fscanf(fp, "%s", buffer);
                length = strlen(buffer);
                a = 0;
                for (m = 0; m < length; m++) { //katharizo ton buffer pou einai to simeio mou ap (,) wste na meinei arithmos
                    if (buffer[m] != '(' && buffer[m] != ')' && buffer[m] != ',') {
                        number[a] = buffer[m];
                        a++;
                    }
                }
                number[a] = '\0';
                sscanf(number, "%Lf", &spot); //to simeio
                temp1[j].position[k] = spot;
            }
        }
    }

    collection->counter = *maxid + 1; //afou ksekinaei i arithmisi ap to 0 vazo +1

    return collection;
}

CurveCollectionPtr loadQueries(const char * filename, int dimension, int *qcounter, int *maxm) {
    FILE *fp;
    CurveCollectionPtr collection;
    CurvePtr* temp;
    PointPtr temp1;
    long double spot;
    int /*aktina,*/ curveid, queriescounter, plithos, max, flag, i, j, k, length, a, m;
    char buffer[100], number[50];
    flag = 0;
    fp = fopen(filename, "r");
    fscanf(fp, "%s", buffer);
    //    aktina = atoi(buffer);
    queriescounter = 0; //arithmos queries sto deftero arxeio eisodou
    while (!feof(fp)) { //proto perasma gia na vro megista simeia arxeiou query 
        queriescounter++;
        if (fscanf(fp, "%s", buffer) < 0) {
            break;
        }
        curveid = atoi(buffer);
        //printf("id=%d\n", curveid);
        fscanf(fp, "%s", buffer);
        if (queriescounter == 1) {
            max = atoi(buffer);
            flag = 1;
            plithos = max;
        }
        if (flag == 0)
            plithos = atoi(buffer);
        flag = 0;
        if (queriescounter != 1 && plithos > max)
            max = plithos;
        for (i = 0; i < dimension * plithos; i++) {
            fscanf(fp, "%s", buffer);
        }
    }
    *qcounter = queriescounter;
    *maxm = max; //pio polla simeia
    fclose(fp);
    fp = fopen(filename, "r");
    fscanf(fp, "%s", buffer);
    collection = malloc(sizeof (CurveCollection));
    if (collection == NULL)
        printf("Den mporesa na dimiourgiso struct CurveCollection");
    collection->curves = malloc(queriescounter * sizeof (struct Curve *));
    if (collection->curves == NULL)
        printf("Den mporesa na dimiourgiso struct Curve* mesa sto struct CurveCollection");
    temp = collection->curves;
    for (i = 0; i < queriescounter; i++) { //gia kathe query eisagogi stis domes mou
        fscanf(fp, "%s", buffer);
        curveid = atoi(buffer);
        temp[i] = malloc(sizeof (struct Curve));
        if (temp[i] == NULL)
            printf("Den mporesa na dimiourgiso struct Curve mesa sto struct CurveCollection");
        temp[i]->id = curveid;
        fscanf(fp, "%s", buffer);
        plithos = atoi(buffer);
        temp[i]->m = plithos;
        temp[i]->points = malloc(plithos * sizeof (struct Point));
        if (temp[i]->points == NULL)
            printf("Den mporesa na dimiourgiso struct Point mesa sto struct Curve");
        temp1 = temp[i]->points;
        for (j = 0; j < plithos; j++) {
            temp1[j].dimension = dimension;
            temp1[j].position = malloc(dimension * sizeof (long double));
            if (temp1->position == NULL)
                printf("Den mporesa na dimiourgiso %d simeia\n", dimension);
            for (k = 0; k < dimension; k++) {
                fscanf(fp, "%s", buffer);
                length = strlen(buffer);
                a = 0;
                for (m = 0; m < length; m++) {
                    if (buffer[m] != '(' && buffer[m] != ')' && buffer[m] != ',') {
                        number[a] = buffer[m];
                        a++;
                    }
                }
                number[a] = '\0';
                sscanf(number, "%Lf", &spot);
                temp1[j].position[k] = spot;
            }
        }
    }

    collection->counter = queriescounter; //exo tosa queries

    return collection;
}

GridPtr create_grid(int dimension) {
    int i;
    GridPtr temp;
    temp = malloc(sizeof (struct Grid));
    if (temp == NULL)
        printf("Den mporesa na dimiourgiso struct Grid");
    temp->delta = 0.008; //delta=4*dmin/1000;
    temp->taf = malloc(dimension * sizeof (long double));
    if (temp->taf == NULL)
        printf("Den mporesa na dimiourgiso taf\n");
    for (i = 0; i < dimension; i++) { //to taf einai dianusma me simeia osa kai i diastasi 
        temp->taf[i] = uniform_distribution(0, dimension);
    }
    return temp;
}

long double euclidean(Point p, Point q, int dimension) {
    long double distance;
    if (dimension == 2) {
        distance = sqrt(pow(p.position[0] - q.position[0], 2) + pow(p.position[1] - q.position[1], 2));
        return distance;
    } else if (dimension == 3) {
        distance = sqrt(pow(p.position[0] - q.position[0], 2) + pow(p.position[1] - q.position[1], 2) + pow(p.position[2] - q.position[2], 2));
        return distance;
    } else {
        distance = sqrt(pow(p.position[0] - q.position[0], 2) + pow(p.position[1] - q.position[1], 2) + pow(p.position[2] - q.position[2], 2) + pow(p.position[3] - q.position[3], 2));
        return distance;
    }
}

GridCurvePtr gridcurve(GridPtr g, CurvePtr p, int dimension) {
    GridCurvePtr temporary;
    int i, /*counterx, countery, counterz, counterm, */ thesi, j, k;
    long double x1, x2, y1, y2, z1, z2, m1, m2, tafx, tafy, tafz, tafm, delta, min, kapax, kapay, kapaz, kapam;
    long double* distance;
    temporary = malloc(sizeof (struct GridCurve));
    temporary->m = p->m;
    temporary->points = malloc(p->m * sizeof (struct Point));
    delta = g->delta;
    if (dimension == 2) {
        tafx = g->taf[0];
        tafy = g->taf[1];
        for (i = 0; i < p->m; i++) { //////gia kathe simeio tis kampilis
            kapax = (p->points[i].position[0] - tafx) / delta;
            kapay = (p->points[i].position[1] - tafy) / delta;
            k = kapax; //to k einai int opote edo pairno to akeraio meros tou
            if (p->points[i].position[0] <= tafx) { //an to simeio mikrotero tou tafx tote (k-1)delta+tafx<simeiox<kdelta+tafx
                x1 = (k - 1) * delta + g->taf[0];
                x2 = k * delta + g->taf[0];
            } else { //an to simeio megalutero tou tafx tote kdelta+tafx<simeiox<(k+1)delta+tafx
                x1 = k * delta + g->taf[0];
                x2 = (k + 1) * delta + g->taf[0];
            }
            k = kapay;
            if (p->points[i].position[1] <= tafy) {
                y1 = (k - 1) * delta + g->taf[1];
                y2 = k * delta + g->taf[1];
            } else {
                y1 = k * delta + g->taf[1];
                y2 = (k + 1) * delta + g->taf[1];
            }
            distance = malloc(4 * sizeof (long double)); //apostasi simeiou ap to parathuro tou grid pou upologisa pano
            distance[0] = sqrt(pow(x1 - p->points[i].position[0], 2) + pow(y1 - p->points[i].position[1], 2));
            distance[1] = sqrt(pow(x1 - p->points[i].position[0], 2) + pow(y2 - p->points[i].position[1], 2));
            distance[2] = sqrt(pow(x2 - p->points[i].position[0], 2) + pow(y1 - p->points[i].position[1], 2));
            distance[3] = sqrt(pow(x2 - p->points[i].position[0], 2) + pow(y2 - p->points[i].position[1], 2));
            min = distance[0]; //vrisko tin thesi tis mikroteris apostasis apo tis 4
            thesi = 0;
            for (j = 1; j < 4; j++) {
                if (distance[j] < min) {
                    min = distance[j];
                    thesi = j;
                }
            }
            temporary->points[i].position = malloc(dimension * sizeof (long double));
            ////eisago sto struct grid to simeio tou grid pou einai pio konta ap to simeio tis kampulis
            if (thesi == 0) {
                temporary->points[i].position[0] = x1;
                temporary->points[i].position[1] = y1;
            } else if (thesi == 1) {
                temporary->points[i].position[0] = x1;
                temporary->points[i].position[1] = y2;
            } else if (thesi == 2) {
                temporary->points[i].position[0] = x2;
                temporary->points[i].position[1] = y1;
            } else {
                temporary->points[i].position[0] = x2;
                temporary->points[i].position[1] = y2;
            }
        }
    } else if (dimension == 3) {
        ///to antistoixo gia dimension 3
        tafx = g->taf[0];
        tafy = g->taf[1];
        tafz = g->taf[2];
        for (i = 0; i < p->m; i++) { //////gia kathe simeio tis kampilis
            kapax = (p->points[i].position[0] - tafx) / delta;
            kapay = (p->points[i].position[1] - tafy) / delta;
            kapaz = (p->points[i].position[2] - tafz) / delta;
            k = kapax;
            if (p->points[i].position[0] <= tafx) {
                x1 = (k - 1) * delta + g->taf[0];
                x2 = k * delta + g->taf[0];
            } else {
                x1 = k * delta + g->taf[0];
                x2 = (k + 1) * delta + g->taf[0];
            }
            k = kapay;
            if (p->points[i].position[1] <= tafy) {
                y1 = (k - 1) * delta + g->taf[1];
                y2 = k * delta + g->taf[1];
            } else {
                y1 = k * delta + g->taf[1];
                y2 = (k + 1) * delta + g->taf[1];
            }
            k = kapaz;
            if (p->points[i].position[2] <= tafz) {
                z1 = (k - 1) * delta + g->taf[2];
                z2 = k * delta + g->taf[2];
            } else {
                z1 = k * delta + g->taf[2];
                z2 = (k + 1) * delta + g->taf[2];
            }
            distance = malloc(8 * sizeof (long double));
            distance[0] = sqrt(pow(x1 - p->points[i].position[0], 2) + pow(y1 - p->points[i].position[1], 2) + pow(z1 - p->points[i].position[2], 2));
            distance[1] = sqrt(pow(x1 - p->points[i].position[0], 2) + pow(y1 - p->points[i].position[1], 2) + pow(z2 - p->points[i].position[2], 2));
            distance[2] = sqrt(pow(x1 - p->points[i].position[0], 2) + pow(y2 - p->points[i].position[1], 2) + pow(z1 - p->points[i].position[2], 2));
            distance[3] = sqrt(pow(x1 - p->points[i].position[0], 2) + pow(y2 - p->points[i].position[1], 2) + pow(z2 - p->points[i].position[2], 2));
            distance[4] = sqrt(pow(x2 - p->points[i].position[0], 2) + pow(y1 - p->points[i].position[1], 2) + pow(z1 - p->points[i].position[2], 2));
            distance[5] = sqrt(pow(x2 - p->points[i].position[0], 2) + pow(y1 - p->points[i].position[1], 2) + pow(z2 - p->points[i].position[2], 2));
            distance[6] = sqrt(pow(x2 - p->points[i].position[0], 2) + pow(y2 - p->points[i].position[1], 2) + pow(z1 - p->points[i].position[2], 2));
            distance[7] = sqrt(pow(x2 - p->points[i].position[0], 2) + pow(y2 - p->points[i].position[1], 2) + pow(z2 - p->points[i].position[2], 2));
            min = distance[0];
            thesi = 0;
            for (j = 1; j < 8; j++) {
                if (distance[j] < min) {
                    min = distance[j];
                    thesi = j;
                }
            }
            temporary->points[i].position = malloc(dimension * sizeof (long double));
            if (thesi == 0) {
                temporary->points[i].position[0] = x1;
                temporary->points[i].position[1] = y1;
                temporary->points[i].position[2] = z1;
            } else if (thesi == 1) {
                temporary->points[i].position[0] = x1;
                temporary->points[i].position[1] = y1;
                temporary->points[i].position[2] = z2;
            } else if (thesi == 2) {
                temporary->points[i].position[0] = x1;
                temporary->points[i].position[1] = y2;
                temporary->points[i].position[2] = z1;
            } else if (thesi == 3) {
                temporary->points[i].position[0] = x1;
                temporary->points[i].position[1] = y2;
                temporary->points[i].position[2] = z2;
            } else if (thesi == 4) {
                temporary->points[i].position[0] = x2;
                temporary->points[i].position[1] = y1;
                temporary->points[i].position[2] = z1;
            } else if (thesi == 5) {
                temporary->points[i].position[0] = x2;
                temporary->points[i].position[1] = y1;
                temporary->points[i].position[2] = z2;
            } else if (thesi == 6) {
                temporary->points[i].position[0] = x2;
                temporary->points[i].position[1] = y2;
                temporary->points[i].position[2] = z1;
            } else {
                temporary->points[i].position[0] = x2;
                temporary->points[i].position[1] = y2;
                temporary->points[i].position[2] = z2;
            }
        }
    } else {
        tafx = g->taf[0];
        tafy = g->taf[1];
        tafz = g->taf[2];
        tafm = g->taf[3];
        for (i = 0; i < p->m; i++) { //////gia kathe simeio tis kampilis
            kapax = (p->points[i].position[0] - tafx) / delta;
            kapay = (p->points[i].position[1] - tafy) / delta;
            kapaz = (p->points[i].position[2] - tafz) / delta;
            kapam = (p->points[i].position[3] - tafm) / delta;
            k = kapax;
            if (p->points[i].position[0] <= tafx) {
                x1 = (k - 1) * delta + g->taf[0];
                x2 = k * delta + g->taf[0];
            } else {
                x1 = k * delta + g->taf[0];
                x2 = (k + 1) * delta + g->taf[0];
            }
            k = kapay;
            if (p->points[i].position[1] <= tafy) {
                y1 = (k - 1) * delta + g->taf[1];
                y2 = k * delta + g->taf[1];
            } else {
                y1 = k * delta + g->taf[1];
                y2 = (k + 1) * delta + g->taf[1];
            }
            k = kapaz;
            if (p->points[i].position[2] <= tafz) {
                z1 = (k - 1) * delta + g->taf[2];
                z2 = k * delta + g->taf[2];
            } else {
                z1 = k * delta + g->taf[2];
                z2 = (k + 1) * delta + g->taf[2];
            }
            k = kapam;
            if (p->points[i].position[3] <= tafm) {
                m1 = (k - 1) * delta + g->taf[3];
                m2 = k * delta + g->taf[3];
            } else {
                m1 = k * delta + g->taf[3];
                m2 = (k + 1) * delta + g->taf[3];
            }
            distance = malloc(16 * sizeof (long double));
            distance[0] = sqrt(pow(x1 - p->points[i].position[0], 2) + pow(y1 - p->points[i].position[1], 2) + pow(z1 - p->points[i].position[2], 2) + pow(m1 - p->points[i].position[3], 2));
            distance[1] = sqrt(pow(x1 - p->points[i].position[0], 2) + pow(y1 - p->points[i].position[1], 2) + pow(z1 - p->points[i].position[2], 2) + pow(m2 - p->points[i].position[3], 2));
            distance[2] = sqrt(pow(x1 - p->points[i].position[0], 2) + pow(y1 - p->points[i].position[1], 2) + pow(z2 - p->points[i].position[2], 2) + pow(m1 - p->points[i].position[3], 2));
            distance[3] = sqrt(pow(x1 - p->points[i].position[0], 2) + pow(y1 - p->points[i].position[1], 2) + pow(z2 - p->points[i].position[2], 2) + pow(m2 - p->points[i].position[3], 2));
            distance[4] = sqrt(pow(x1 - p->points[i].position[0], 2) + pow(y2 - p->points[i].position[1], 2) + pow(z1 - p->points[i].position[2], 2) + pow(m1 - p->points[i].position[3], 2));
            distance[5] = sqrt(pow(x1 - p->points[i].position[0], 2) + pow(y2 - p->points[i].position[1], 2) + pow(z1 - p->points[i].position[2], 2) + pow(m2 - p->points[i].position[3], 2));
            distance[6] = sqrt(pow(x1 - p->points[i].position[0], 2) + pow(y2 - p->points[i].position[1], 2) + pow(z2 - p->points[i].position[2], 2) + pow(m1 - p->points[i].position[3], 2));
            distance[7] = sqrt(pow(x1 - p->points[i].position[0], 2) + pow(y2 - p->points[i].position[1], 2) + pow(z2 - p->points[i].position[2], 2) + pow(m2 - p->points[i].position[3], 2));
            distance[8] = sqrt(pow(x2 - p->points[i].position[0], 2) + pow(y1 - p->points[i].position[1], 2) + pow(z1 - p->points[i].position[2], 2) + pow(m1 - p->points[i].position[3], 2));
            distance[9] = sqrt(pow(x2 - p->points[i].position[0], 2) + pow(y1 - p->points[i].position[1], 2) + pow(z1 - p->points[i].position[2], 2) + pow(m2 - p->points[i].position[3], 2));
            distance[10] = sqrt(pow(x2 - p->points[i].position[0], 2) + pow(y1 - p->points[i].position[1], 2) + pow(z2 - p->points[i].position[2], 2) + pow(m1 - p->points[i].position[3], 2));
            distance[11] = sqrt(pow(x2 - p->points[i].position[0], 2) + pow(y1 - p->points[i].position[1], 2) + pow(z2 - p->points[i].position[2], 2) + pow(m2 - p->points[i].position[3], 2));
            distance[12] = sqrt(pow(x2 - p->points[i].position[0], 2) + pow(y2 - p->points[i].position[1], 2) + pow(z1 - p->points[i].position[2], 2) + pow(m1 - p->points[i].position[3], 2));
            distance[13] = sqrt(pow(x2 - p->points[i].position[0], 2) + pow(y2 - p->points[i].position[1], 2) + pow(z1 - p->points[i].position[2], 2) + pow(m2 - p->points[i].position[3], 2));
            distance[14] = sqrt(pow(x2 - p->points[i].position[0], 2) + pow(y2 - p->points[i].position[1], 2) + pow(z2 - p->points[i].position[2], 2) + pow(m1 - p->points[i].position[3], 2));
            distance[15] = sqrt(pow(x2 - p->points[i].position[0], 2) + pow(y2 - p->points[i].position[1], 2) + pow(z2 - p->points[i].position[2], 2) + pow(m2 - p->points[i].position[3], 2));
            min = distance[0];
            thesi = 0;
            for (j = 1; j < 16; j++) {
                if (distance[j] < min) {
                    min = distance[j];
                    thesi = j;
                }
            }
            temporary->points[i].position = malloc(dimension * sizeof (long double));
            if (thesi == 0) {
                temporary->points[i].position[0] = x1;
                temporary->points[i].position[1] = y1;
                temporary->points[i].position[2] = z1;
                temporary->points[i].position[3] = m1;
            } else if (thesi == 1) {
                temporary->points[i].position[0] = x1;
                temporary->points[i].position[1] = y1;
                temporary->points[i].position[2] = z1;
                temporary->points[i].position[3] = m2;
            } else if (thesi == 2) {
                temporary->points[i].position[0] = x1;
                temporary->points[i].position[1] = y1;
                temporary->points[i].position[2] = z2;
                temporary->points[i].position[3] = m1;
            } else if (thesi == 3) {
                temporary->points[i].position[0] = x1;
                temporary->points[i].position[1] = y1;
                temporary->points[i].position[2] = z2;
                temporary->points[i].position[3] = m2;
            } else if (thesi == 4) {
                temporary->points[i].position[0] = x1;
                temporary->points[i].position[1] = y2;
                temporary->points[i].position[2] = z1;
                temporary->points[i].position[3] = m1;
            } else if (thesi == 5) {
                temporary->points[i].position[0] = x1;
                temporary->points[i].position[1] = y2;
                temporary->points[i].position[2] = z1;
                temporary->points[i].position[3] = m2;
            } else if (thesi == 6) {
                temporary->points[i].position[0] = x1;
                temporary->points[i].position[1] = y2;
                temporary->points[i].position[2] = z2;
                temporary->points[i].position[3] = m1;
            } else if (thesi == 7) {
                temporary->points[i].position[0] = x1;
                temporary->points[i].position[1] = y2;
                temporary->points[i].position[2] = z2;
                temporary->points[i].position[3] = m2;
            } else if (thesi == 8) {
                temporary->points[i].position[0] = x2;
                temporary->points[i].position[1] = y1;
                temporary->points[i].position[2] = z1;
                temporary->points[i].position[3] = m1;
            } else if (thesi == 9) {
                temporary->points[i].position[0] = x2;
                temporary->points[i].position[1] = y1;
                temporary->points[i].position[2] = z1;
                temporary->points[i].position[3] = m2;
            } else if (thesi == 10) {
                temporary->points[i].position[0] = x2;
                temporary->points[i].position[1] = y1;
                temporary->points[i].position[2] = z2;
                temporary->points[i].position[3] = m1;
            } else if (thesi == 11) {
                temporary->points[i].position[0] = x2;
                temporary->points[i].position[1] = y1;
                temporary->points[i].position[2] = z2;
                temporary->points[i].position[3] = m2;
            } else if (thesi == 12) {
                temporary->points[i].position[0] = x2;
                temporary->points[i].position[1] = y2;
                temporary->points[i].position[2] = z1;
                temporary->points[i].position[3] = m1;
            } else if (thesi == 13) {
                temporary->points[i].position[0] = x2;
                temporary->points[i].position[1] = y2;
                temporary->points[i].position[2] = z1;
                temporary->points[i].position[3] = m2;
            } else if (thesi == 14) {
                temporary->points[i].position[0] = x2;
                temporary->points[i].position[1] = y2;
                temporary->points[i].position[2] = z2;
                temporary->points[i].position[3] = m1;
            } else {
                temporary->points[i].position[0] = x2;
                temporary->points[i].position[1] = y2;
                temporary->points[i].position[2] = z2;
                temporary->points[i].position[3] = m2;
            }
        }
    }
    return temporary; //epistrefo pointer se gridcurve
}

GridCurvePtr mergecurves(GridCurvePtr g, GridCurvePtr p, int dimension) { //enono ta k gridcurves kai vgazo ta sunexomeno diplotupa 
    GridCurvePtr temporary;
    int i, j; //, metritis;
    temporary = malloc(sizeof (struct GridCurve));
    //    metritis = 0;
    temporary->m = 0;
    temporary->points = malloc(sizeof (struct Point));
    temporary->points->position = malloc(dimension * sizeof (long double));
    for (i = 0; i < dimension; i++) {
        temporary->points[0].position[i] = g->points[0].position[i];
    }
    (temporary->m)++;
    for (i = 1; i < g->m; i++) { //gia kathe stoixeio tou pinaka g
        int flag_duplicate = 0;
        int counter = 0;
        for (j = 0; j < dimension; j++) { //sugrisi simeion
            if (g->points[i].position[j] == temporary->points[temporary->m - 1].position[j])
                counter++;
        }
        if (counter == dimension) {
            flag_duplicate = 1;
        }

        if (flag_duplicate == 1) { //exoume sunexomena simeia idia 
            continue;
        }
        temporary->points = realloc(temporary->points, (temporary->m + 1) * sizeof (struct Point)); //eisago ena parapano stoixeio ston pinaka meso realloc 
        temporary->points[temporary->m].position = malloc(dimension * sizeof (long double));
        for (j = 0; j < dimension; j++) {
            temporary->points[temporary->m].position[j] = g->points[i].position[j];
        }
        (temporary->m)++; //auksano to megethos tou enomenou grid curve
    }
    //to ido me parapano gia ton deftero pinaka
    for (i = 1; i < p->m; i++) { //gia kathe stoixeio tou pinaka p
        int flag_duplicate = 0;
        int counter = 0;

        for (j = 0; j < dimension; j++) { //sugrisi simeion
            if (p->points[i].position[j] == temporary->points[temporary->m - 1].position[j])
                counter++;
        }
        if (counter == dimension) {
            flag_duplicate = 1;
            break;
        }
        if (flag_duplicate == 1)
            continue;
        temporary->points = realloc(temporary->points, (temporary->m + 1) * sizeof (struct Point));
        temporary->points[temporary->m].position = malloc(dimension * sizeof (long double));
        for (j = 0; j < dimension; j++) {
            temporary->points[temporary->m].position[j] = p->points[i].position[j];
        }
        temporary->m++;
    }
    return temporary;
}

long double frechet(CurvePtr c1, CurvePtr c2, int dimension) {
    int n = c1->m;
    int m = c2->m;
    long double array[n][m];
    long double distance1, distance2, distance3, distance4; //, min;
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (i == 0 && j == 0) {
                array[i][j] = euclidean(c1->points[i], c2->points[j], dimension);
            } else if (i == 0) {
                distance1 = euclidean(c1->points[i], c2->points[j], dimension);
                distance2 = array[i][j - 1];
                if (distance1 >= distance2)
                    array[i][j] = distance1;
                else
                    array[i][j] = distance2;
            } else if (j == 0) {
                distance1 = euclidean(c1->points[i], c2->points[j], dimension);
                distance2 = array[i - 1][j];
                if (distance1 >= distance2)
                    array[i][j] = distance1;
                else
                    array[i][j] = distance2;
            } else {
                distance1 = euclidean(c1->points[i], c2->points[j], dimension);
                distance2 = array[i - 1][j];
                distance3 = array[i][j - 1];
                distance4 = array[i - 1][j - 1];

                long double m1 = (distance2 < distance3) ? distance2 : distance3;
                long double m2 = (m1 < distance4) ? m1 : distance4;

                array[i][j] = (distance1 > m2) ? distance1 : m2;
            }
        }
    }
    return array[c1->m - 1][c2->m - 1];
}

VectorPtr onedimension(GridCurvePtr p, int dimension) { //to enomeno grid curve to anaparisto se monodiastati morfh
    VectorPtr temp;
    int i, j, counter;
    counter = 0;
    temp = malloc(sizeof (struct Vector));
    if (temp == NULL) {
        printf("Den katafera na ftiakso vector");
        exit(0);
    }
    temp->m = dimension * p->m;
    temp->components = malloc(temp->m * sizeof (long double));
    if (temp->components == NULL) {
        printf("Den katafera na ftiakso components");
        exit(0);
    }
    for (i = 0; i < p->m; i++) {
        for (j = 0; j < dimension; j++) {
            temp->components[counter] = p->points[i].position[j];
            counter++;
        }
    }
    return temp;
}

long double inner(VectorPtr a, VectorPtr b) { //upologismos esoterikou ginomenou
    int i;
    long double counter;
    counter = 0;
    if (a->m >= b->m) {
        for (i = 0; i < b->m; i++) {
            counter = counter + a->components[i] * b->components[i];
        }
    } else {
        for (i = 0; i < a->m; i++) {
            counter = counter + a->components[i] * b->components[i];
        }
    }
    return counter;
}

unsigned long int innerWithModulo(VectorPtr a, VectorPtr b) { //esoteriko ginomeno mod 2^32-5
    int i;
    long double counter = 0;
    if (a->m >= b->m) {
        for (i = 0; i < b->m; i++) {
            counter = counter + ((unsigned long int) (a->components[i] * b->components[i])) % (4294967291L);
        }
    } else {
        for (i = 0; i < a->m; i++) {
            counter = counter + ((unsigned long int) (a->components[i] * b->components[i])) % (4294967291L);
        }
    }
    return ((unsigned long int) counter) % (4294967291L);
}

ProjectionPtr create_projection(int v_length) {
    ProjectionPtr temp;
    int i;
    temp = malloc(sizeof (struct Projection));
    if (temp == NULL)
        printf("Den mporesa na dimiourgiso struct projection");
    temp->r_length = v_length; //length tou dianusmatos r
    temp->r = malloc(v_length * sizeof (long double));
    for (i = 0; i < v_length; i++)
        temp->r[i] = uniform_distribution_int(1, 10); //tuxaioi sto [0,10] se morfi int
    return temp;
}

unsigned long int Hashfunction(VectorPtr p, ProjectionPtr project) {
    VectorPtr temp;
    unsigned long int esoteriko;
    int i;
    temp = malloc(sizeof (struct Vector));
    temp->m = project->r_length;
    temp->components = malloc(temp->m * sizeof (long double));
    for (i = 0; i < temp->m; i++) {
        temp->components[i] = project->r[i];
    }
    esoteriko = innerWithModulo(temp, p);
    return (unsigned long int) (esoteriko); //to vecoru egine katharos arithmos 
}

HashTablePtr * create_hashtable(CurveCollectionPtr collection, int k, int L, int maxid, int maxm, int dimension) {
    int elements = maxid + 1;
    int M = (elements) / 2; // oi L kadoi exoun mikos oses oi kampules/2
    int i, j, n, hashnumber, h;
    VectorPtr onedim;
    HashTableNodePtr temp1, temp3;
    GridCurvePtr *provoli, provoli1;
    CurvePtr * allCurves = collection->curves;
    if (M == 0) {
        M = 1;
    }
    HashTablePtr * hashpointer = malloc(L * sizeof (HashTablePtr));
    for (i = 0; i < L; i++) {
        hashpointer[i] = NULL;
    }
    for (i = 0; i < L; i++) { //gia kathe pinaka katakermatismou
        hashpointer[i] = malloc(sizeof (struct HashTable));
        hashpointer[i]->size = M;
        hashpointer[i]->k = k;
        hashpointer[i]->nodes = malloc(M * sizeof (HashTableNodePtr)); ///prepei na to gemiso gia kathe keli tou pinaka
        for (j = 0; j < M; j++) { //gia kathe keli tou pinaka katakermatismou
            hashpointer[i]->nodes[j] = NULL;
        }
        hashpointer[i]->projection = create_projection(k * maxm * dimension);
        hashpointer[i]->grids = malloc(k * sizeof (GridPtr));
        for (j = 0; j < k; j++) {
            hashpointer[i]->grids[j] = create_grid(dimension);
        }
        for (j = 0; j < maxid; j++) { ///gia kathe kampuli
            provoli = malloc(k * sizeof (GridCurvePtr));
            for (n = 0; n < k; n++) { //k fores
                provoli[n] = gridcurve(hashpointer[i]->grids[n], allCurves[j], dimension);
            }
            for (h = 0; h < provoli[0]->m; h++) {
                // printf("SIMEIO	%d\n", h);
                //printf("X=%.20Lf\n", provoli[0]->points[h].position[0]);
                //printf("Y=%.20Lf\n", provoli[0]->points[h].position[1]);
            }
            provoli1 = mergecurves(provoli[0], provoli[1], dimension);
            if (k > 2) {
                for (n = 2; n <= k - 1; n++) {
                    provoli1 = mergecurves(provoli[n], provoli1, dimension);
                }
            }
            provoli1->id = allCurves[j]->id;
            for (h = 0; h < provoli1->m; h++) {
                //printf("x=%Lf\n", provoli1->points[h].position[0]);
                //printf("y=%Lf\n", provoli1->points[h].position[1]);
            }
            onedim = onedimension(provoli1, dimension);
            hashnumber = Hashfunction(onedim, hashpointer[i]->projection);
            hashnumber = hashnumber % hashpointer[i]->size;
            temp1 = hashpointer[i]->nodes[hashnumber];
            if (temp1 == NULL) { //eisagogi struct node gia kataskeuh kathe alusidas
                temp1 = malloc(sizeof (struct HashTableNode));
                temp1->next = NULL;
                hashpointer[i]->nodes[hashnumber] = temp1;
                temp1->curve = allCurves[j];
                temp1->gridcurve = provoli1;
                continue;
            }
            while (temp1->next != NULL)
                temp1 = temp1->next;
            temp3 = malloc(sizeof (struct HashTableNode));
            temp1->next = temp3;
            temp3->next = NULL;
            temp3->curve = allCurves[j];
            temp3->gridcurve = provoli1;
        }
    }
    return hashpointer;
}

// 1 if equal
// 0 if not equal

int compareGridCurves(GridCurvePtr g, GridCurvePtr p, int dimension) {
    int i, k;
    int hit = 0;
    if (g->m != p->m) {
        return 0;
    }
    for (i = 0; i < g->m; i++) {
        int counter = 0;
        for (k = 0; k < dimension; k++) {
            long double diff = g->points[i].position[k] - p->points[i].position[k];
            if (diff < 0) {
                diff = -diff;
            }
            if (diff < 0.0000000001) { //den mporo na kano isotita 2 double opote vazo sugrino tin diafora tous me ena e=0.000000000001
                counter++;
            }
        }
        if (counter == dimension) {
            hit++;
        }
    }
    if (hit == g->m) {
        return 1;
    } else {
        return 0;
    }
}

void solve_nn(HashTablePtr * hashtables, CurveCollectionPtr collection, CurveCollectionPtr queries, int k, int L, int maxid, int maxm, int dimension) {
    int i;

    for (i = 0; i < queries->counter; i++) {
        CurvePtr q = queries->curves[i];

        solve_nn_query(hashtables, collection, q, k, L, maxid, maxm, dimension);
    }
}

int solve_range(HashTablePtr * hashtables, CurveCollectionPtr collection, CurvePtr q, double range, int k, int L, int maxid, int maxm, int dimension) {
    int count_assignments = 0;
    count_assignments = count_assignments + solve_range_query(hashtables, collection, q, range, k, L, maxid, maxm, dimension);
    return count_assignments;
}

void solve_nn_query(HashTablePtr * hashpointer, CurveCollectionPtr collection, CurvePtr query, int k, int L, int maxid, int maxm, int dimension) {
    int i, n, hashnumber;
    GridCurvePtr *provoli, provoli1;
    VectorPtr onedim;
    HashTableNodePtr temp1;

    CurvePtr nearestNeighbor = NULL;
    long double nearestDistance = 0;

    for (i = 0; i < L; i++) {


        provoli = malloc(k * sizeof (GridCurvePtr));
        for (n = 0; n < k; n++) { //k fores
            provoli[n] = gridcurve(hashpointer[i]->grids[n], query, dimension);
        }
        provoli1 = mergecurves(provoli[0], provoli[1], dimension);
        if (k > 2) {
            for (n = 2; n <= k - 1; n++) {
                provoli1 = mergecurves(provoli[n], provoli1, dimension);
            }
        }
        provoli1->id = query->id;
        onedim = onedimension(provoli1, dimension);
        hashnumber = Hashfunction(onedim, hashpointer[i]->projection);
        hashnumber = hashnumber % hashpointer[i]->size;

        temp1 = hashpointer[i]->nodes[hashnumber];

        while (temp1 != NULL) {
            if (compareGridCurves(provoli1, temp1->gridcurve, dimension) == 1) {
                long double tempdistance = frechet(query, temp1->curve, dimension);
                if (nearestNeighbor == NULL || tempdistance < nearestDistance) {
                    nearestDistance = tempdistance;
                    nearestNeighbor = temp1->curve;
                }
            }

            temp1 = temp1->next;
        }

        if (nearestNeighbor == NULL) {
            temp1 = hashpointer[i]->nodes[hashnumber];

            while (temp1 != NULL) {
                long double tempdistance = frechet(query, temp1->curve, dimension);
                if (nearestNeighbor == NULL || tempdistance < nearestDistance) {
                    nearestDistance = tempdistance;
                    nearestNeighbor = temp1->curve;
                }

                temp1 = temp1->next;
            }
        }
    }

    if (nearestNeighbor != NULL) {
        printf("Nearest neighbor of %4d is %4d \n", query->id, nearestNeighbor->id);
    } else {
        printf("Nearest neighbor of %4d is NULL \n", query->id);
    }
}

int solve_range_query(HashTablePtr * hashpointer, CurveCollectionPtr collection, CurvePtr query, double range, int k, int L, int maxid, int maxm, int dimension) {
    int i, n, hashnumber;
    GridCurvePtr *provoli, provoli1;
    VectorPtr onedim;
    HashTableNodePtr temp1;
    int count_assignments = 0;

    for (i = 0; i < L; i++) {
        provoli = malloc(k * sizeof (GridCurvePtr));
        for (n = 0; n < k; n++) { //k fores
            provoli[n] = gridcurve(hashpointer[i]->grids[n], query, dimension);
        }
        provoli1 = mergecurves(provoli[0], provoli[1], dimension);
        if (k > 2) {
            for (n = 2; n <= k - 1; n++) {
                provoli1 = mergecurves(provoli[n], provoli1, dimension);
            }
        }
        provoli1->id = query->id;
        onedim = onedimension(provoli1, dimension);
        hashnumber = Hashfunction(onedim, hashpointer[i]->projection);
        hashnumber = hashnumber % hashpointer[i]->size;

        temp1 = hashpointer[i]->nodes[hashnumber];

        while (temp1 != NULL) {
            long double tempdistance = frechet(query, temp1->curve, dimension);
            if (tempdistance < range) {
                if (temp1->curve->best_center == NULL) {
                    temp1->curve->best_center = query;
                    temp1->curve->best_min = tempdistance;
                    count_assignments++;
                } else if (temp1->curve->best_center != query) {
                    long double tempdistance1 = frechet(query, temp1->curve, dimension);
                    long double tempdistance2 = frechet(temp1->curve->best_center, temp1->curve, dimension);

                    if (tempdistance1 < tempdistance2) {
                        temp1->curve->best_center = query;
                        temp1->curve->best_min = tempdistance1;
                        count_assignments++;
                    }
                }
            }

            temp1 = temp1->next;
        }
    }
    return count_assignments;
}

void solve_nn_true(CurveCollectionPtr collection, CurveCollectionPtr queries, int k, int L, int maxid, int maxm, int dimension) {
    int i;

    for (i = 0; i < queries->counter; i++) {
        CurvePtr q = queries->curves[i];

        solve_nn_query_true(collection, q, k, L, maxid, maxm, dimension);
    }
}

void solve_nn_query_true(CurveCollectionPtr collection, CurvePtr query, int k, int L, int maxid, int maxm, int dimension) {
    int i;
    CurvePtr nearestNeighbor = NULL;
    long double nearestDistance = 0;
    for (i = 0; i < collection->counter; i++) {
        CurvePtr t = collection->curves[i];

        long double tempdistance = frechet(query, t, dimension);
        if (nearestNeighbor == NULL || tempdistance < nearestDistance) {
            nearestDistance = tempdistance;
            nearestNeighbor = t;
        }
    }
    if (nearestNeighbor != NULL) {
        printf("Nearest neighbor of %4d is %4d \n", query->id, nearestNeighbor->id);
    } else {
        printf("Nearest neighbor of %4d is NULL \n", query->id);
    }
}

CentroidsPtr initialization_simpleapproach(CurveCollectionPtr collection, int k, int maxid, int dimension) {
    int random, i, j, q;
    CurvePtr * kampiles;
    CurvePtr * temp;
    PointPtr temp1;
    CentroidsPtr kentra;
    kampiles = collection->curves;
    kentra = malloc(sizeof (struct Centroids));
    kentra->k = k;
    kentra->curve = malloc(k * sizeof (struct Curve *));
    if (kentra->curve == NULL)
        printf("Den mporesa na dimiourgiso struct Curve* mesa sto struct Centroids");
    temp = kentra->curve;
    for (i = 0; i < k; i++) {
        random = uniform_distribution_int(0, maxid);
        temp[i] = malloc(sizeof (struct Curve));
        if (temp[i] == NULL)
            printf("Den mporesa na dimiourgiso struct Curve mesa sto struct CurveCollection");
        temp[i]->id = kampiles[random]->id;
        temp[i]->m = kampiles[random]->m;
        //temp[i]->flag=kampiles[random]->flag;
        temp[i]->best_center = kampiles[random]->best_center;
        temp[i]->second_bestcenter = kampiles[random]->second_bestcenter;
        temp[i]->points = malloc(kampiles[random]->m * sizeof (struct Point));
        if (temp[i]->points == NULL)
            printf("Den mporesa na dimiourgiso struct Point mesa sto struct Curve");
        temp1 = temp[i]->points;
        for (j = 0; j < temp[i]->m; j++) {
            temp1[j].dimension = dimension;
            temp1[j].position = malloc(dimension * sizeof (long double));
            if (temp1->position == NULL)
                printf("Den mporesa na dimiourgiso %d simeia\n", dimension);
            for (q = 0; q < dimension; q++)
                temp1[j].position[q] = kampiles[random]->points[j].position[q];
        }
    }
    return kentra;
}

//CentroidsPtr initialization_dummyapproach(CurveCollectionPtr collection, int k, int maxid, int dimension) {
//    int random, i, j, q;
//    CurvePtr * kampiles;
//    CurvePtr * temp;
//    PointPtr temp1;
//    CentroidsPtr kentra;
//    kampiles = collection->curves;
//    kentra = malloc(sizeof (struct Centroids));
//    kentra->k = k;
//    kentra->curve = malloc(k * sizeof (struct Curve *));
//    if (kentra->curve == NULL)
//        printf("Den mporesa na dimiourgiso struct Curve* mesa sto struct Centroids");
//    temp = kentra->curve;
//    for (i = 0; i < k; i++) {
//        random = i; //uniform_distribution_int(0, maxid);
//        temp[i] = malloc(sizeof (struct Curve));
//        if (temp[i] == NULL)
//            printf("Den mporesa na dimiourgiso struct Curve mesa sto struct CurveCollection");
//        temp[i]->id = kampiles[random]->id;
//        temp[i]->m = kampiles[random]->m;
//        //temp[i]->flag=kampiles[random]->flag;
//        temp[i]->best_center = kampiles[random]->best_center;
//        temp[i]->second_bestcenter = kampiles[random]->second_bestcenter;
//        temp[i]->points = malloc(kampiles[random]->m * sizeof (struct Point));
//        if (temp[i]->points == NULL)
//            printf("Den mporesa na dimiourgiso struct Point mesa sto struct Curve");
//        temp1 = temp[i]->points;
//        for (j = 0; j < temp[i]->m; j++) {
//            temp1[j].dimension = dimension;
//            temp1[j].position = malloc(dimension * sizeof (long double));
//            if (temp1->position == NULL)
//                printf("Den mporesa na dimiourgiso %d simeia\n", dimension);
//            for (q = 0; q < dimension; q++)
//                temp1[j].position[q] = kampiles[random]->points[j].position[q];
//        }
//    }
//    return kentra;
//}

CentroidsPtr initialization_kmeanspp(CurveCollectionPtr collection, int k, int maxid, int dimension) {
    int random, i, j, q, t, v;
    long double * mincenter;
    long double * D;
    long double sum, f, min, max;
    CurvePtr * kampiles;
    CurvePtr * temp;
    PointPtr temp1;
    CentroidsPtr kentra;
    t = 0;
    kampiles = collection->curves;
    kentra = malloc(sizeof (struct Centroids));
    kentra->k = k;
    kentra->curve = malloc(k * sizeof (struct Curve *));
    if (kentra->curve == NULL)
        printf("Den mporesa na dimiourgiso struct Curve* mesa sto struct Centroids");
    temp = kentra->curve;
    random = uniform_distribution_int(0, maxid);
    temp[0] = malloc(sizeof (struct Curve));
    if (temp[0] == NULL)
        printf("Den mporesa na dimiourgiso struct Curve mesa sto struct CurveCollection");
    temp[0]->id = kampiles[random]->id;
    temp[0]->m = kampiles[random]->m;
    temp[0]->best_center = kampiles[random]->best_center;
    temp[0]->second_bestcenter = kampiles[random]->second_bestcenter;
    temp[0]->points = malloc(kampiles[random]->m * sizeof (struct Point));
    if (temp[0]->points == NULL)
        printf("Den mporesa na dimiourgiso struct Point mesa sto struct Curve");
    temp1 = temp[0]->points;
    for (j = 0; j < temp[0]->m; j++) {
        temp1[j].dimension = dimension;
        temp1[j].position = malloc(dimension * sizeof (long double));
        if (temp1->position == NULL)
            printf("Den mporesa na dimiourgiso %d simeia\n", dimension);
        for (q = 0; q < dimension; q++)
            temp1[j].position[q] = kampiles[random]->points[j].position[q];
    }
    t++; //plithos kentron mexri tora
    kampiles[random]->flag = 1; //vazo simadi sta kentra pou exo idi sto struct Centroids
    D = malloc((maxid + 1) * sizeof (long double));
    for (i = 0; i <= maxid; i++)
        D[i] = 0;
    for (t = 1; t < k; t++) {
        for (v = 0; v <= maxid; v++) { //gia kathe kampili tou dataset
            if (kampiles[v]->flag == 1) {
                D[v] = -1;
                continue;
            }
            mincenter = malloc(t * sizeof (long double));
            for (i = 0; i < t; i++) { //gia kathe kentroeides
                mincenter[i] = frechet(temp[i], kampiles[v], dimension);
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
        for (i = 0; i <= maxid; i++) {
            if (D[i] == -1)
                continue;
            sum = sum + D[i];
            D[i] = sum;
        }
        max = D[0];
        for (i = 1; i <= maxid; i++) {
            if (D[i] > max)
                max = D[i];
        }
        //printf("max=%Lf\n", max);
        f = (long double) rand() / RAND_MAX;
        f = 0 + f * (max);
        //printf("f=%Lf\n", f);
        for (i = 0; i <= maxid; i++) {
            if (f < D[i])
                break;
        }
        //printf("i=%d\n", i);
        random = i;
        temp[t] = malloc(sizeof (struct Curve));
        if (temp[t] == NULL)
            printf("Den mporesa na dimiourgiso struct Curve mesa sto struct CurveCollection");
        temp[t]->id = kampiles[random]->id;
        temp[t]->m = kampiles[random]->m;
        temp[t]->best_center = kampiles[random]->best_center;
        temp[t]->second_bestcenter = kampiles[random]->second_bestcenter;
        temp[t]->points = malloc(kampiles[random]->m * sizeof (struct Point));
        if (temp[t]->points == NULL)
            printf("Den mporesa na dimiourgiso struct Point mesa sto struct Curve");
        temp1 = temp[t]->points;
        for (j = 0; j < temp[t]->m; j++) {
            temp1[j].dimension = dimension;
            temp1[j].position = malloc(dimension * sizeof (long double));
            if (temp1->position == NULL)
                printf("Den mporesa na dimiourgiso %d simeia\n", dimension);
            for (q = 0; q < dimension; q++)
                temp1[j].position[q] = kampiles[random]->points[j].position[q];
        }
    }
    free(D);
    return kentra;
}

ClusterArrayPtr assignment_lloyd(CurveCollectionPtr collection, CentroidsPtr kentra, int maxid, int dimension) {
    int i, j, thesi, secthesi;
    long double min, secmin;
    long double * tempdistance;
    ClusterArrayPtr all_clusters;
    CurveNodePtr komvos;
    CurveListPtr lista;
    CurvePtr * kentroeidi;
    CurvePtr * temp;
    kentroeidi = kentra->curve;
    temp = collection->curves;

    // k = 1 ???

    all_clusters = malloc(sizeof (struct ClusterArray));
    if (all_clusters == NULL)
        printf("Den mporesa na dimiourgiso ClusterArray");
    all_clusters->k = kentra->k;
    all_clusters->clusters = malloc(all_clusters->k * sizeof (struct Cluster));
    for (i = 0; i < all_clusters->k; i++) {
        all_clusters->clusters[i].center = kentroeidi[i];
        all_clusters->clusters[i].memberList = malloc(sizeof (struct CurveList));
        all_clusters->clusters[i].memberList->counter = 0;
        all_clusters->clusters[i].memberList->head = NULL;
    }
    tempdistance = malloc(all_clusters->k * sizeof (long double));
    for (i = 0; i <= maxid; i++) {
        //tempdistance=malloc(all_clusters->k*sizeof(long double));
        for (j = 0; j < all_clusters->k; j++)
            tempdistance[j] = frechet(temp[i], kentroeidi[j], dimension);
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

        komvos = malloc(sizeof (struct CurveNode));
        komvos->next = lista->head;
        komvos->curve = temp[i/*thesi*/];
        lista->head = komvos;
        lista->counter++;
    }
    free(tempdistance);
    return all_clusters;
}

ClusterArrayPtr assignment_lsh(CurveCollectionPtr collection, CentroidsPtr kentra, int maxid, int dimension, HashTablePtr * hashtables, int k, int L, int maxM) {
    int i, j, thesi, secthesi;
    long double * tempdistance;
    long double min, secmin;
    double range = 1;
    int count_assignments = 0;
    CurvePtr * kentroeidi;
    CurvePtr * temp;
    kentroeidi = kentra->curve;
    temp = collection->curves;
    ClusterArrayPtr all_clusters;
    CurveNodePtr komvos;
    CurveListPtr lista;

    for (i = 0; i <= maxid; i++) {
        collection->curves[i]->best_center = NULL;
        collection->curves[i]->best_min = 0;
        collection->curves[i]->second_bestcenter = NULL;
        collection->curves[i]->second_bestmin = 0;
    }

    all_clusters = malloc(sizeof (struct ClusterArray));
    if (all_clusters == NULL)
        printf("Den mporesa na dimiourgiso ClusterArray");
    all_clusters->k = kentra->k;
    all_clusters->clusters = malloc(all_clusters->k * sizeof (struct Cluster));
    for (i = 0; i < all_clusters->k; i++) {
        all_clusters->clusters[i].center = kentroeidi[i];
        all_clusters->clusters[i].memberList = malloc(sizeof (struct CurveList));
        all_clusters->clusters[i].memberList->counter = 0;
        all_clusters->clusters[i].memberList->head = NULL;
    }

    min = frechet(kentra->curve[0], kentra->curve[1], dimension);

    for (i = 0; i < kentra->k; i++) {
        for (j = 0; j < kentra->k; j++) {
            if (i != j) {
                double temp = frechet(kentra->curve[i], kentra->curve[j], dimension);
                if (temp < min) {
                    min = temp;
                }
            }
        }
    }

    range = min / 2;

    do {
        count_assignments = 0;
        for (j = 0; j < kentra->k; j++) {
            count_assignments = count_assignments + solve_range(hashtables, collection, kentra->curve[j], range, k, L, maxid, maxM, dimension);
        }
        range = range * 2;
        printf("count assignments : %d \n", count_assignments);
    } while (count_assignments > 0); // may change to a percent of maxid (total curves)

    // all items have been assigned to centroids

    tempdistance = malloc(kentra->k * sizeof (long double));
    for (i = 0; i <= maxid; i++) {
        for (j = 0; j < kentra->k; j++)
            tempdistance[j] = frechet(temp[i], kentroeidi[j], dimension);

        if (collection->curves[i]->best_center == NULL) {
            // Lloyd for unassigned items

            min = tempdistance[0];
            thesi = 0;
            for (j = 1; j < kentra->k; j++) {
                if (tempdistance[j] < min) {
                    min = tempdistance[j];
                    thesi = j;
                }
            }
            temp[i]->best_center = kentroeidi[thesi];
            temp[i]->best_min = min;
        }
        min = temp[i]->best_min;
        secmin = tempdistance[0];
        secthesi = 0;
        for (j = 1; j < kentra->k; j++) {
            if (tempdistance[j] > min && tempdistance[j] < secmin) {
                secmin = tempdistance[j];
                secthesi = j;
            }
        }

        temp[i]->second_bestcenter = kentroeidi[secthesi];

        // add it to cluster
        for (j = 0; j < kentra->k; j++) {
            if (all_clusters->clusters[j].center == temp[i]->best_center) {
                lista = all_clusters->clusters[j].memberList;

                komvos = malloc(sizeof (struct CurveNode));
                komvos->next = lista->head;
                komvos->curve = temp[i];
                lista->head = komvos;
                lista->counter++;
            }
        }

    }

    return all_clusters;
}

CurvePtr frechet_curve(CurvePtr c1, CurvePtr c2, int dimension) {
    SpotListPtr lista;
    SpotNodePtr komvos, temp, temp1;
    CurvePtr kampili;
    int minldx;
    int n = c1->m;
    int m = c2->m;
    long double array[n][m];
    long double distance1, distance2, distance3, distance4; //, min;
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (i == 0 && j == 0) {
                array[i][j] = euclidean(c1->points[i], c2->points[j], dimension);
            } else if (i == 0) {
                distance1 = euclidean(c1->points[i], c2->points[j], dimension);
                distance2 = array[i][j - 1];
                if (distance1 >= distance2)
                    array[i][j] = distance1;
                else
                    array[i][j] = distance2;
            } else if (j == 0) {
                distance1 = euclidean(c1->points[i], c2->points[j], dimension);
                distance2 = array[i - 1][j];
                if (distance1 >= distance2)
                    array[i][j] = distance1;
                else
                    array[i][j] = distance2;
            } else {
                distance1 = euclidean(c1->points[i], c2->points[j], dimension);
                distance2 = array[i - 1][j];
                distance3 = array[i][j - 1];
                distance4 = array[i - 1][j - 1];

                long double m1 = (distance2 < distance3) ? distance2 : distance3;
                long double m2 = (m1 < distance4) ? m1 : distance4;

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
    komvos->point = malloc(sizeof (struct Point));
    komvos->point->position = malloc(dimension * sizeof (long double));
    for (i = 0; i < dimension; i++) {
        komvos->point->position[i] = (c1->points[pi].position[i] + c2->points[qi].position[i]) / 2;
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
        temp->point = malloc(sizeof (struct Point));
        temp->point->position = malloc(dimension * sizeof (long double));
        for (i = 0; i < dimension; i++) {
            temp->point->position[i] = (c1->points[pi].position[i] + c2->points[qi].position[i]) / 2;
        }
        temp->next = lista->head;
        lista->head = temp;
        lista->counter++;
    }
    while (pi != 0) {
        --pi;
        temp = malloc(sizeof (struct SpotNode));
        temp->point = malloc(sizeof (struct Point));
        temp->point->position = malloc(dimension * sizeof (long double));
        for (i = 0; i < dimension; i++) {
            temp->point->position[i] = (c1->points[pi].position[i] + c2->points[qi].position[i]) / 2;
        }
        temp->next = lista->head;
        lista->head = temp;
        lista->counter++;
    }
    while (qi != 0) {
        --qi;
        temp = malloc(sizeof (struct SpotNode));
        temp->point = malloc(sizeof (struct Point));
        temp->point->position = malloc(dimension * sizeof (long double));
        for (i = 0; i < dimension; i++) {
            temp->point->position[i] = (c1->points[pi].position[i] + c2->points[qi].position[i]) / 2;
        }
        temp->next = lista->head;
        lista->head = temp;
        lista->counter++;
    }
    temp1 = lista->head;

    //////////kampili epistrofis/////////
    kampili = malloc(sizeof (struct Curve));
    kampili->m = lista->counter;
    kampili->points = malloc(kampili->m * sizeof (struct Point));
    for (i = 0; i < kampili->m; i++) {
        kampili->points[i].position = malloc(sizeof(long double)*dimension);
        for (j = 0; j < dimension; j++)
            kampili->points[i].position[j] = temp1->point->position[j];
        temp1 = temp1->next;
    }
    /////////////////////////////////////
    return kampili;
}

CentroidsPtr update_mdfd(ClusterArrayPtr all_clusters, int dimension) {
    int i, j, number_of_leaves, temp, number_of_all_nodes, m;
    CurveNodePtr lista;

    CentroidsPtr centers = malloc(sizeof (Centroids));
    centers->k = all_clusters->k;
    centers->curve = malloc(centers->k * sizeof (CurvePtr));

    for (i = 0; i < all_clusters->k; i++) { //gia kathe cluster
        centers->curve[i] = NULL;
    }
    for (i = 0; i < all_clusters->k; i++) { //gia kathe cluster
        number_of_leaves = all_clusters->clusters[i].memberList->counter; //poses curves exei to cluster
        lista = all_clusters->clusters[i].memberList->head;
        number_of_all_nodes = number_of_leaves;
        temp = number_of_leaves;
        if (temp == 0) {
            return NULL;
        }
        number_of_all_nodes = number_of_leaves*2-1;

        CurvePtr * tree = malloc(sizeof (CurvePtr)*(1 + number_of_all_nodes));
        tree[0] = NULL;
		
        // initialize leaves
        for (j = 0; j < number_of_leaves; j++) {
            tree[number_of_all_nodes - j] = lista->curve;
            lista = lista->next;
        }
        // for each inner node
        for (j = number_of_all_nodes / 2; j >= 1; j--) {
            int left = j * 2;
            int right = j * 2 + 1;

            if (left <= number_of_all_nodes && right <= number_of_all_nodes) { // 2 children
                CurvePtr leftcurve = tree[left];
                CurvePtr rightcurve = tree[right];
                CurvePtr mdfc = frechet_curve(leftcurve, rightcurve, dimension);
                tree[j] = mdfc;
            } else if (left <= number_of_all_nodes) { // 1 child
                tree[j] = tree[left];
            } else { // no children (error)
                printf("oime kai tris ali \n");
                exit(0);
            }
        }

        centers->curve[i] = tree[1];
    }
    return centers;
}

TreePtr newItem() {
    TreePtr pn = malloc(sizeof (struct Tree));
    pn->deiktis = NULL;
    pn->left = NULL;
    pn->right = NULL;
    return pn;
}

TreePtr insertTree(TreePtr pn) {
    if (pn == NULL)
        return newItem();
    else {
        if (pn->left == NULL)
            pn->left = insertTree(pn->left);
        else
            pn->right = insertTree(pn->right);
    }
    return pn;
}

unsigned int getLeaf(TreePtr pn, CurveNodePtr lista) {
    //    if (pn == NULL)
    //        return 0;
    //    if (pn->left == NULL && pn->right == NULL) {
    //
    //        return 1;
    //    } else {
    ////        return getLeafCount(node->left) + getLeafCount(node->right);
    //    }
    return 0;
}
