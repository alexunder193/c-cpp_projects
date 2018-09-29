#include <stdio.h>
#include <stdlib.h>
#include <windows.h>                /* for Windows APIs */

/* Resolution Milli-Seconds */
int main()
{
    LARGE_INTEGER frequency;        /* ticks per second */
    LARGE_INTEGER t1, t2;           /* ticks */
    double elapsedTime;

    /* get ticks per second */
    QueryPerformanceFrequency(&frequency);

    /* start timer */
    QueryPerformanceCounter(&t1);

    /* do something */
    int i,j=0,k=0;
    for (i=1;i<=10000;++i)
    { j = i*i;
      k = i*i*i;
      /* printf("%3d %5d %8d\n",i, j, k); */
     }

    /* stop timer */
    QueryPerformanceCounter(&t2);

    /* compute and print the elapsed time in millisec */
    elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
    printf("elapsedTime=%g msec\n", elapsedTime);
    
    getchar();
    return 0;
}
