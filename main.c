#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "header.h"

int main(){
    struct timeval stop,start;
    
    //Using method1 to calculate
    gettimeofday(&start,NULL);
    //method1();
    gettimeofday(&stop,NULL);
    printf("Seconds token for method 1 : %lu\n",stop.tv_sec - start.tv_sec);    

    //Using method2 to calculate
    gettimeofday(&start,NULL);
    //method2();
    gettimeofday(&stop,NULL);
    printf("Seconds token for method 2 : %lu\n",stop.tv_sec - start.tv_sec);    
    return 0;
}