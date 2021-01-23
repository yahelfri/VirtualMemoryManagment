#include "initMemory.h"



int objectsCounter=0;
int currentIndex = -1;

void initRAM(char input_Path[] ,char output_Path[], int ramSize,int flag)
{
   
    FILE *fp;
    fp = fopen(input_Path,"r");
    if (fp == NULL)
        exit(0);

    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    char** memory;
    
    FILE *fout;
    fout = fopen(output_Path,"w+");
        if (fout == NULL)
            exit(0);

    int size=ramSize;
    createRAM(size,flag);
    while ((read = getline(&line, &len, fp)) != -1) {
        char *pch= NULL;
        pch = strtok(line," "); // first flag
        const char *flags[4];
        flags[0] = "write";
        flags[1] = "read";
        flags[2] = "print";
        flags[3] = "print\n";

        int key;
        char* value;
        
        
        if(strcmp(pch,flags[0])==0) // writing
        {
            pch = strtok(NULL," ");
            key= atoi(pch);
            pch = strtok(NULL," ");
            value=pch;
           
            char* myValue;
            myValue = strtok(value,"\n");
            
            insertToRAM(key,myValue,flag);
             
            
        }

        else if (strcmp(pch,flags[1])==0) // reading
        {
            pch = strtok(NULL," ");
            key= atoi(pch);
            readFromRam(key,flag);
            

        }
        else if (strstr(pch,"print") != NULL) // print
        {
            fprintf(fout,"%s","secondaryMemory=[");

            for (int i = 0; i < romsize; i++)
            {
                fprintf(fout,"%s",rom_Array[i]);
                if(i<romsize-1)
                    fprintf(fout,"%s",",");
            }
            fprintf(fout,"%s","]\n");


        } 
    }


    fclose(fp);
    fclose(fout);
    if (line)
        free(line);
}




void readFromRam(int key,int flag)
{
    int keyIndex = checkKeyExistence(key);

    if(keyIndex ==-1)  //key not in ram
    {
        char* value = (char*)malloc(sizeof(rom_Array[key])+1);
        strcpy(value,rom_Array[key]);
        if (objectsCounter>=ramsize) // ram is full
        {
           if(flag==1)
           {
                currentIndex = find_index_LRU();
           }
           else
           {
                currentIndex = find_index(ramsize);
           }
           rom_Array[ram[currentIndex].key] = (char*)malloc(sizeof(ram[currentIndex].value));
           strcpy(rom_Array[ram[currentIndex].key],ram[currentIndex].value);
           ram[currentIndex].key = key;
           ram[currentIndex].value = (char*)malloc(sizeof(rom_Array[key])+1);
           strcpy(ram[currentIndex].value,rom_Array[key]);
        }
        else                        // ram has free space
        {
          
            currentIndex++;
            if(flag==1)
            {
                insert_page_LRU(currentIndex);
            }
            ram[currentIndex].key=key;

            ram[currentIndex].value = (char*)malloc(sizeof(value));
            strcpy(ram[currentIndex].value,value);
        }
        objectsCounter++;
    }
    else                // key in ram
    {
        if(flag==1)
        {
            insert_page_LRU(keyIndex);
        }
        else
        {
            bitArr[keyIndex] = 0; //need to by 1
        }
    }
}



void insertToRAM(int key, char* value,int flag)
{
    int keyIndex = checkKeyExistence(key);

    if(keyIndex ==-1)  //key not in ram
    {
        
        if (objectsCounter>=ramsize) // ram is full
        {

            if(flag==1)
            {
                currentIndex = find_index_LRU();
            }
            else
            {
                currentIndex = find_index(ramsize);
            }

            int index_by_key = ram[currentIndex].key;

            rom_Array[index_by_key] = (char*)malloc(sizeof(ram[currentIndex].value)+1);
            strcpy(rom_Array[ram[currentIndex].key],ram[currentIndex].value);

            ram[currentIndex].key = key;
            ram[currentIndex].value = (char*)malloc(sizeof(value));
            strcpy(ram[currentIndex].value,value);
        }
        else                        // ram has free space
        {
            
            currentIndex++;
            if(flag==1){
                insert_page_LRU(currentIndex);
            }
            ram[currentIndex].key=key;

            if( ram[currentIndex].value !=   NULL && ram[currentIndex].value != "") // key allredy in ram
            {
                
                ram[currentIndex].value = (char*)malloc(sizeof(value)+1);
                strcpy(ram[currentIndex].value,value);
            }
            else{
                ram[currentIndex].key=key;
                *ram[currentIndex].value = *value;
                
            }
        }
        objectsCounter++;
    }
    else                // key in ram
    {
        
        if(flag==1)
        {
            insert_page_LRU(keyIndex);
        }
        else
        {
            bitArr[keyIndex]=0; //need to by 1
        }
        strcat(ram[keyIndex].value,value);
    }
}

int find_index_LRU() {
	int count_zero = 0;
	int index = -1;
	int max_zero = -1;
	for (int i = 0; i < ramsize; i++) {
		for (int j = 0; j < ramsize; j++) {
			if (matrix_LRU[i][j] == 0)
				count_zero++;
		}
		if (max_zero < count_zero) {
			max_zero = count_zero;
			index = i;
		}
		count_zero = 0;
	}
    insert_page_LRU(index);
	return index;
}

void insert_page_LRU(int index) {
	for (int i = 0; i < ramsize; i++)
	{

		matrix_LRU[index][i] = 1;
		matrix_LRU[i][index] = 0;
	}
}

void update_time(int index) {
	timeArr[index] = ramsize - 1;
	for (int i = index + 1; i < ramsize; i++) {

		timeArr[i]--;
	}
}


int find_index(int size) {
	int time = ramsize;
	int new_index = -1;
	
	for (int i = 0; i < size; i++) {
		if (bitArr[i] == 1)
			continue;
		else
		{
			if (time > timeArr[i])
			{
				time = timeArr[i];
				new_index = i;
			}
		}
	}
	if (new_index == -1) {
		for (int i = 0; i < size; i++) {
			if (timeArr[i] == 0) {
				new_index = i;
				bitArr[i] = 0;
				break;
			}
		}
	}
	else {
		for (int i = 0; i < new_index; i++) {
			bitArr[i] = 0;
			
		}
	}
	update_time(new_index);
	return new_index;
}


int checkKeyExistence(int key)
{
    for(int i=0;i<ramsize;i++)
    {
        if(ram[i].key==key)
        {
            return i;
        }
    }
    return -1;
}