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
int* matrixC1;
int* matrixC2;
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
        if(matA == NULL){
            printf("No such file!\n");
            v=1;
            return NULL;
        }
        fscanf(matA,"row=%d col=%d",&d,&d);
        for(h=0;h<rowA;h++){
            for(g=0;g<colA;g++){
                if(fscanf(matA,"%d ",matrixA+g+(h*colA)) < 1){
                    printf("Error occured while parsing values! in A at i=%d j=%d\n",h,g);
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
        if(matB == NULL){
            printf("No such file!\n");
            v=1;
            return NULL;
        }
        fscanf(matB,"row=%d col=%d",&d,&d);
        for(h=0;h<rowA;h++){
            for(g=0;g<colA;g++){
                if(fscanf(matB,"%d ",matrixB+g+(h*colB)) < 1){
                    printf("Error occured while parsing values! in B at i=%d j=%d\n",h,g);
                    fclose(matB);
                    v=1;
                    return NULL;
                }    
            }
        }
        fclose(matB);
    }
    else{
        printf("Error occurred!");
        v=1;
        return NULL;
    }
    return NULL;
}

void* read_size(void* s){
    struct file_req *f = (struct file_req *)s;
    if(f->type == 'a'){
        matA = fopen(f->file_name,"r");
        if(matA == NULL){
            printf("No such file!\n");
            v=1;
            return NULL;
        }        
        if(fscanf(matA,"row=%d col=%d",&rowA,&colA) < 1){
            printf("An error occurred while reading parameters!");
            fclose(matA);
            v=1;
            return NULL;
        }
        fclose(matA);
    }
    else if(f->type == 'b'){
        matB = fopen(f->file_name,"r");
        if(matB == NULL){
            printf("No such file!\n");
            v=1;
            return NULL;
        }        
        if(fscanf(matB,"row=%d col=%d",&rowB,&colB) < 1){
            printf("An error occurred while reading parameters!");
            fclose(matB);
            v=1;
            return NULL;
        }
        fclose(matB);
    }
    else{
        printf("Error occurred!");
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
        printf("Error in the input files\n");
        return 0;
    }
    int ma[rowA][colA];
    int mb[rowB][colB];
    int mc1[rowA][colB];
    int mc2[rowA][colB];

    matrixA = &ma[0][0];
    matrixB = &mb[0][0];

    matC = fopen(fc.file_name,"w");
    if(matC == NULL){
        printf("output file does not exist!");
        return 0;
    }
    fprintf(matC,"Output file:\n");
    fprintf(matC,"\n");
    fclose(matC);

    //threads to read the values in matrices
    pthread_create(&t1,NULL,read_array,&fa);
    pthread_create(&t2,NULL,read_array,&fb);

    //wait till threads finish
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    if(v == 1){
        printf("Error in the input files\n");
        return 0;
    }

    int p,q;

    //initialize values in ans array for method 1
    for(p=0;p<rowA;p++){
        for(q=0;q<colB;q++){
            mc1[p][q] = 0;
        }
    }
    //initialize values in ans array for method 2
    for(p=0;p<rowA;p++){
        for(q=0;q<colB;q++){
            mc2[p][q] = 0;
        }
    }

    matrixC1 = &mc1[0][0];
    matrixC2 = &mc2[0][0];
    
    long time1,time2;

    //Using method1 to calculate
    gettimeofday(&start,NULL);
    method1(matrixA,matrixB,rowA,colA,rowB,colB,matrixC1);
    gettimeofday(&stop,NULL);
    time1 = stop.tv_usec - start.tv_usec;
    printf("Seconds token for method 1 : %lu micro-second\n",time1);

    //Using method2 to calculate
    gettimeofday(&start,NULL);
    method2(matrixA,matrixB,rowA,colA,rowB,colB,matrixC2);
    gettimeofday(&stop,NULL);
    time2 = stop.tv_usec - start.tv_usec;
    printf("Seconds token for method 2 : %lu micro-second\n",time2);

    matC = fopen(fc.file_name,"a+");
    fprintf(matC,"Method 1 output:\n");
    fprintf(matC,"\n");    
    for(p=0;p<rowA;p++){
        for(q=0;q<colB;q++){
            fprintf(matC,"%d ",mc1[p][q]);
        }
        fprintf(matC,"\n");
    }
    fprintf(matC,"\n");    
    fprintf(matC,"Time token in micro-seconds: %lu\n",time1);
    fprintf(matC,"\n");
    fprintf(matC,"******************************************************\n");    
    fprintf(matC,"Method 2 output:\n");
    fprintf(matC,"\n");    
    for(p=0;p<rowA;p++){
        for(q=0;q<colB;q++){
            fprintf(matC,"%d ",mc2[p][q]);
        }
        fprintf(matC,"\n");
    }
    fprintf(matC,"\n");    
    fprintf(matC,"Time token in micro-seconds: %lu\n",time2);
    fprintf(matC,"\n");
    fprintf(matC,"******************************************************\n");
    fclose(matC);
    return 0;
}