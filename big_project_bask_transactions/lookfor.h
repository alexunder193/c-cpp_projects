void lookup(int,dkorifis*,char*,int);
void triangle(int,dkorifis*,int,float);
void conn(int,int,dkorifis*,int);
void traceflow(int,dkorifis*,int,int);
void eisagogi(int,dclosed*);                      //eisagei stin arxi mias sundedemenis listas tous komvous pou exoun episkeftei h conn kai h traceflow
int anazitisi(int,dclosed);                       //elegxei an enas komvos einai mesa stin sundedemeni litsa
int monopati(dkorifis a, dkorifis b, dclosed* arxi);             //h anadromiki sunartisi pou xrisimopoiei h conn gia episkepsi kombon
void path(dkorifis a,int trexonvathos, dclosed* arxi,int depth);    //anadromiki sunartisi pou xrisimopoiei h traceflow gia episkepsi kombon
