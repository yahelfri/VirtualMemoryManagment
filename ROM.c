#include "ROM.h"



void initROM(int Size)
{
    rom_Array = (char**)malloc(Size * sizeof(char*));
    romsize = Size;
    for(int i=0; i<Size;i++)
    {
        rom_Array[i] = "";
    }
}
