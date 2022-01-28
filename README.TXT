
How to Compile and Run:
 1st method: 
  Run the command 'make' 
  in the command line without the '' in the directory with all the .c files 
  and the Makefile.
  EX: [account@ecs-pa-coding1 directory]$ make

  Then ./executable [-CLOCK/-LRU]

 2nd method:
  gcc -c frame.c
  gcc -c main.c
  gcc -c frameArray.c
  gcc -c readFileFunctions.c
  gcc main.o frame.o frameArray.o readFileFunctions.o
  Then ./executable [-CLOCK/-LRU]

Program Notes:
 - All the paramaters (# of pages, # of frames, # of page requests) in file must be a value greater than 0, 
 else the program will return an error notification and will not run. 
