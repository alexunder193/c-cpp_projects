int	bluecapacity;
int	pinkcapacity;

void printhashtable(dbluebucket* Hash, int hashtablesize);
void bucketscapacity(int sbytes);
struct bluebucket* createbluebucket();
dpinkbucket createpinkbucket();
void insertpink(dpink p, char* uniqid,char* caller,char* callee,sdate date,stime init_time,int duration,int type,int tarrif,int fault_condition);
void insertnewblue(dblue b, char* tel, char* uniqid,char* caller,char* callee,sdate date,stime init_time,int duration,int type,int tarrif,int fault_condition);
dblue searchblue(dbluebucket bb, char* tel);
void printallblue(dbluebucket bb);
dblue searchfreeblue(dbluebucket bb);
void printallpink(dpinkbucket pb);
dpink searchfreepink(dpinkbucket pb);
void inserthashtable(dbluebucket* Hash,int hashtablesize,char* tel, char* uniqid,char* caller,char* callee,sdate date,stime init_time,int duration,int type,int tarrif,int fault_condition);
void Insert(dbluebucket* Hash1,int hashtable1size,dbluebucket* Hash2,int hashtable2size, char* uniqid,char* caller,char* callee,sdate date,stime init_time,int duration,int type,int tarrif,int fault_condition);
void delete(dbluebucket* Hash,int hashtablesize,char* uniqid,char* caller);
void bye(dbluebucket* Hash1,int hashtable1size,dbluebucket* Hash2,int hashtable2size);
