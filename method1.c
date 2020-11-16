#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include "header.h"

int *ans;
int *mA;
int *mB;
int numberOfColA;
int numberOfColB;
int rowIndex=0;

void *solve_row(void* arg){
    int *id = (int *)arg; //index of the row which the thread hold
    int *current_elementC = (int *)(ans+((*id)*numberOfColB)); //current element in matrix c 
    int *current_elementA = (int *)(mA+((*id)*numberOfColA)); //current element in matrix a
    int *current_elementB;
    int j=0,i=0,m=0,k,l;
    for(j;j<numberOfColB;j++){
        k=0;
        l=0;
        current_elementB = (int *)(mB+j+(k*numberOfColB));
        for(i;i<numberOfColA;i++){
            current_elementC = (*current_elementC)+(*current_elementA)*(*current_elementB);
            l++;
            k++;
            current_elementA = (int *)(mA+((*id)*numberOfColA)+l);
            current_elementB = (int *)(mB+j+(k*numberOfColB));
        }
        current_elementC = (int *)(ans+((*id)*numberOfColB)+j+1);
    }
    pthread_exit(0);
}

int method1(int *m1,int *m2,int r1,int c1,int r2,int c2){
    int answer[r1][c2];
    int i,j;
    for(i=0;i<r1;i++){
        for(j=0;j<c2;j++){
            answer[i][j] = 0;
        }
    }
    printf("meth\n");
    ans = &answer[0][0];
    mA = m1;
    mB = m2;
    numberOfColA = c1;
    numberOfColB = c2;
    pthread_t tids[r1];
    i=0;
    for(i; i<r1 ; i++){
        pthread_create(&tids[i],NULL,solve_row,&i);
    }
    i=0;
    for(i;i<r1;i++){
        pthread_join(&tids[i],NULL);
    }
    for(i=0;i<r1;i++){
        for(j=0;j<c2;j++){
            printf("%d ",answer[i][j]);
        }
        printf("\n");
    }
}