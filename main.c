#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "header.h"



int main(){
    struct timeval stop,start;
    int ar1[4][4] ={{3,7,3,6},{9,2,0,3},{0,2,1,7},{2,2,7,9}};
    int ar2[4][4] ={{6,5,5,2},{1,7,9,6},{6,6,8,9},{0,3,5,2}};

    //Using method1 to calculate
    gettimeofday(&start,NULL);
    method1((int *)ar1,(int *)ar2,4,4,4,4);
    gettimeofday(&stop,NULL);
    printf("Seconds token for method 1 : %lu micro-second\n",stop.tv_usec - start.tv_usec);    

    //Using method2 to calculate
    gettimeofday(&start,NULL);
    method2((int *)ar1,(int *)ar2,4,4,4,4);
    gettimeofday(&stop,NULL);
    printf("Seconds token for method 2 : %lu micro-second\n",stop.tv_usec - start.tv_usec);    
    return 0;
}