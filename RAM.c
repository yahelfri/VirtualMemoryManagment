#include "RAM.h"



void createRAM(int Size,int flag)
{
    ram = (pair*) malloc(sizeof(struct keyValuePair)* Size);
    ramsize = Size;
    if(flag==1){
        matrix_LRU = (int**) malloc(sizeof(int*)*Size);
        for(int i=0;i<Size;i++){
            matrix_LRU[i] = (int*) malloc(sizeof(int)*Size);
        }
    }
    else{
        bitArr = (int*) malloc(Size * sizeof(int));
        timeArr = (int*) malloc(Size * sizeof(int));
        
        for(int i=0; i<Size;i++)
        {
            bitArr[i]=0;
            timeArr[i] =0;
        }
    }
    for(int i=0; i<Size;i++)
    {
            ram[i].key=-1;
            ram[i].value="";
    }
}


