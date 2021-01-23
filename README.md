# VirtualMemoryManagment

																		operating systems homework 5 re
this program is made to simulate operating system's virtual memory.
the idea is to manage virtual page and allow writing and reading.



instructioons:    
	1)  create youre input file and locate it at th same folder youre gonna run the code in.

	2) compile our code using:
																	
					gcc -o MemoryManagement MemoryManagement.c initMemory.c initMemory.h RAM.c RAM.h ROM.c ROM.h 
													
	3)  then run it using :
										
					./MemoryManagement  [flag]  [input file name] [output file name]  [rom size]  [ram size].

					when:   if [flag] = 1 we will use LRU algorithm.
						if [flag] > 1 we will use second chance FIFO  algorithm									   
						[input file name] is the name of the input file you created.
																
													
													
										
					
					
