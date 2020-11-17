#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "header.h"

int *ans2;
int *mA2;
int *mB2;
int numberOfColA2;
int numberOfColB2;

struct row_col{
    int row;
    int col;
};

void *solve_row2(void* arg){
    struct row_col *element = (struct row_col *)arg;
    int row = element->row;
    int col = element->col;
    int *current_elementA = (int *)(mA2+(row*numberOfColA2));
    int *current_elementB = (int *)(mB2+col);
    int *current_elementC = (int *)(ans2+(row*numberOfColB2)+col);
    int i,l=0,k=0;
    for(i=0 ; i<numberOfColA2 ;i++){
        *current_elementC = (*current_elementC)+((*current_elementA)*(*current_elementB));
        l++;
        k++;
        current_elementA = (int *)(mA2+(row*numberOfColA2)+l);
        current_elementB = (int *)(mB2+(k*numberOfColB2)+col);
    }
}

int method2(int *m1,int *m2,int r1,int c1,int r2,int c2){
    int i=0,j=0;
    mA2 = m1;
    mB2 = m2;
    int answer2[r1][c2];
    for(i=0;i<r1;i++){
        for(j=0;j<c2;j++){
            answer2[i][j] = 0;
        }
    }
    ans2 = &answer2[0][0];
    numberOfColA2 = c1;
    numberOfColB2 = c2;
    struct row_col array_of_elements[r1*c2];

    pthread_t tids[r1*c2];
    for(i=0;i<r1;i++){
        for(j=0;j<c2;j++){
            array_of_elements[(i*c2)+j].row = i;
            array_of_elements[(i*c2)+j].col = j;
            pthread_create(&tids[(i*c2)+j],NULL,solve_row2,&array_of_elements[(i*c2)+j]);
        }
    }

    for(i=0 ; i<r1 ; i++){
        for(j=0 ;j<c2 ; j++){
            pthread_join(tids[(i*c2)+j],NULL);
        }
    }

    for(i=0;i<r1;i++){
        for(j=0;j<c2;j++){
            printf("%d ",answer2[i][j]);
        }
        printf("\n");
    }

}