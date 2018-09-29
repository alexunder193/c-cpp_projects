#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
 main()
{
int child;
 child=fork();
if(child==0)
    printf("Hello from the child");
  
else
   printf("Greetings from the parent");
}
