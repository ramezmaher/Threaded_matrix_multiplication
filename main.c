#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "header.h"



int main(){
    struct timeval stop,start;
    int ar1[2][3];
    int ar2[3][2];

    ar1[0][0] = 1;
    ar1[0][1] = 2;
    ar1[0][2] = 3;
    ar1[1][0] = 4;
    ar1[1][1] = 5;
    ar1[1][2] = 6;

    ar2[0][0] = 10;
    ar2[0][1] = 11;
    ar2[1][0] = 20;
    ar2[1][1] = 21;
    ar2[2][0] = 30;
    ar2[2][1] = 31;

    //Using method1 to calculate
    gettimeofday(&start,NULL);
    method1((int *)ar1,(int *)ar2,2,3,3,2);
    gettimeofday(&stop,NULL);
    printf("Seconds token for method 1 : %lu micro-second\n",stop.tv_usec - start.tv_usec);    

    //Using method2 to calculate
    gettimeofday(&start,NULL);
    //method2();
    gettimeofday(&stop,NULL);
    printf("Seconds token for method 2 : %lu micro-second\n",stop.tv_usec - start.tv_usec);    
    return 0;
}