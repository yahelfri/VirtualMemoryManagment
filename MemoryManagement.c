#include "initMemory.h"
#include <string.h>

int main(int argc, char *argv[])
{
               // printf("in = %s   out= %s",argv[2],argv[3]);


    
    if(argc<5)
    {
       char* input = "./myinput.txt";
       char* output = "./output.txt";
       initROM(1000);
       initRAM(input,output,50,1);
    }
    else
    {
        char* path= "./";
        char input[1024] ;
        char output[1024];
        sprintf(input,"%s%s",path,argv[2]);
        sprintf(output,"%s%s",path,argv[3]);
        int ramSize = atoi(argv[5]);   // main memory size
        int romSize = atoi(argv[4]);   // secondary memory size
        int flag = atoi(argv[1]);   
        initROM(romSize);
        initRAM(input,output,ramSize,flag);
            
        
    }
    
    
    
}

