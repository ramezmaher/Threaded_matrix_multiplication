#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include "header.h"

int *ans;
int *mA;
int *mB;
int numberOfColA;
int numberOfColB;

void *solve_row(void* arg){
    int *id = (int *)arg; //index of the row which the thread hold
    int *current_elementC = (int *)(ans+((*id)*numberOfColB));
    int *current_elementA ; 
    int *current_elementB;
    int j,i,k,l;
    for(j=0;j<numberOfColB;j++){
        k=0;
        l=0; 
        current_elementA = (int *)(mA+((*id)*numberOfColA)); 
        current_elementB = (int *)(mB+j+(k*numberOfColB));
        for(i=0;i<numberOfColA;i++){
            *current_elementC = (*current_elementC)+(*current_elementA)*(*current_elementB);
            l++;
            k++;
            current_elementA = (int *)(mA+((*id)*numberOfColA)+l);
            current_elementB = (int *)(mB+j+(k*numberOfColB));
        }
        current_elementC = (int *)(ans+((*id)*numberOfColB)+j+1);
    }

}

int method1(int *m1,int *m2,int r1,int c1,int r2,int c2,int *m3){
    int i=0,j=0;
    mA = m1;
    mB = m2;
    ans = m3;
    numberOfColA = c1;
    numberOfColB = c2;
    int array_of_ind[r1];
    pthread_t tids[r1];
    i=0;
    for(i; i<r1 ; i++){
        array_of_ind[i] = i;
        pthread_create(&tids[i],NULL,solve_row,&array_of_ind[i]);
    }
    for(i=0;i<r1;i++){
        pthread_join(tids[i],NULL);
    }
}