#include <unistd.h>
#include <stdio.h> 
#include <sys/types.h>
#include <malloc.h>



typedef struct keyValuePair{
    int key;
    char** value;
}pair;

pair *ram;
int* bitArr;
int* timeArr;
int** matrix_LRU;

int ramsize;

void createRAM(int,int);