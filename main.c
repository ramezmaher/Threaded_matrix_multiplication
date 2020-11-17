#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <string.h>
#include "header.h"

FILE * matA;
FILE * matB;
FILE * matC;

int* matrixA;
int* matrixB;
int* matrixC;
int rowA;
int rowB;
int colA;
int colB;
int v=0;

struct file_req{
    char *file_name;
    char type;
};

void* read_array(void* arg){
    struct file_req *f = (struct file_req *)arg;
    int h,g,d;
    if(f->type == 'a'){
        matA = fopen(f->file_name,"r");
        fscanf(matA,"row=%d col=%d",&d,&d);
        for(h=0;h<rowA;h++){
            for(g=0;g<colA;g++){
                if(fscanf(matA,"%d",matrixA+g+(h*colA)) == 1){
                    perror("Error occured while parsing values!");
                    fclose(matA);
                    v=1;
                    return NULL;
                }
            }
        }
        fclose(matA);
    }
    else if(f->type == 'b'){
        matB = fopen(f->file_name,"r");
        fscanf(matB,"row=%d col=%d",&d,&d);
        for(h=0;h<rowA;h++){
            for(g=0;g<colA;g++){
                if(fscanf(matB,"%d",matrixB+g+(h*colB)) == 1){
                    perror("Error occured while parsing values!");
                    fclose(matB);
                    v=1;
                    return NULL;
                }    
            }
        }
        fclose(matB);
    }
    else{
        perror("Error occurred!");
        v=1;
        return NULL;
    }
    return NULL;
}

void* read_size(void* s){
    struct file_req *f = (struct file_req *)s;
    if(f->type == 'a'){
        matA = fopen(f->file_name,"r");
        if(fscanf(matA,"row=%d col=%d",&rowA,&colA) == 1){
            perror("An error occurred while reading parameters!");
            fclose(matA);
            v=1;
            return NULL;
        }
        fclose(matA);
    }
    else if(f->type == 'b'){
        matB = fopen(f->file_name,"r");
        if(fscanf(matB,"row=%d col=%d",&rowB,&colB) == 1){
            perror("An error occurred while reading parameters!");
            fclose(matB);
            v=1;
            return NULL;
        }
        fclose(matB);
    }
    else{
        perror("Error occurred!");
        v=1;
        return NULL;
    }
    return NULL;
}


int main(int argc,char* argv[]){
    struct timeval stop,start;
    struct file_req fa,fb,fc;
    switch(argc){
        case 1:{
            fa.file_name = "a.txt";
            fa.type = 'a';
            fb.file_name = "b.txt";
            fb.type = 'b';
            fc.file_name = "c.out";
            fc.type = 'c';
            break;
        }
        case 2:{
            fa.file_name = argv[1];
            fa.type = 'a';
            fb.file_name = "b.txt";
            fb.type = 'b';
            fc.file_name = "c.out";
            fc.type = 'c';
            break;
        }
        case 3:{
            fa.file_name = argv[1];
            fa.type = 'a';
            fb.file_name = argv[2];
            fb.type = 'b';
            fc.file_name = "c.out";
            fc.type = 'c';
            break;
        }
        case 4:{
            fa.file_name = argv[1];
            fa.type = 'a';
            fb.file_name = argv[2];
            fb.type = 'b';
            fc.file_name = argv[3];
            fc.type = 'c';
            break;
        }
        default:{
            perror("Invalid input!");
            return 0;
        }       

    }

    pthread_t t1,t2;
    //threads to read the sizes of matrices
    pthread_create(&t1,NULL,read_size,&fa);
    pthread_create(&t2,NULL,read_size,&fb);

    //wait till threads finish
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    if(v == 1){
        perror("Error in the input files");
        return 0;
    }
    printf("rowA =%d colA=%d\n",rowA,colA);
    int ma[rowA][colA];
    int mb[rowB][colB];

    matrixA = &ma[0][0];
    matrixB = &mb[0][0];

    //threads to read the values in matrices
    pthread_create(&t1,NULL,read_array,&fa);
    pthread_create(&t2,NULL,read_array,&fb);

    //wait till threads finish
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    if(v == 1){
        perror("Error in the input files");
        return 0;
    }
    int i,j;
    for(i=0;i<rowA;i++){
        for(j=0;j<colA;j++){
            printf("%d ",ma[i][j]);
        }
        printf("\n");
    }

    //Using method1 to calculate
    gettimeofday(&start,NULL);
    method1(matrixA,matrixB,rowA,colA,rowB,colB);
    gettimeofday(&stop,NULL);
    printf("Seconds token for method 1 : %lu micro-second\n",stop.tv_usec - start.tv_usec);    

    //Using method2 to calculate
    gettimeofday(&start,NULL);
    method2((int *) matrixA,(int *)matrixB,rowA,colA,rowB,colB);
    gettimeofday(&stop,NULL);
    printf("Seconds token for method 2 : %lu micro-second\n",stop.tv_usec - start.tv_usec);    
    return 0;
}