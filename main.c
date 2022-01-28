#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <string.h>
#include <ctype.h> 

#include "frameArray.h"
#include "readFileFunctions.h"

void initIntArray(int *array, int initVal, int size){
 int i;
 for(i=0;i<size;i++){
  array[i] = initVal;
 }	 
}

void getParamatersLineFromFile(char *fileName, char *buffer){
 int LINE_FOR_PARAMATER = 1;
 putLineFromFileIntoBufferUsingLine(fileName, buffer, LINE_FOR_PARAMATER);
}

void setRequestSequenceArray(int* array, int numRequest, char* fileName){
 int LINE_START_REQUEST = 2;
 int i;
 char lineStr[20] = {};
 for(i=0;i<numRequest;i++){
  putLineFromFileIntoBufferUsingLine(fileName, lineStr, LINE_START_REQUEST+i);
  //printf("%s\n", lineStr);
  array[i] = atoi(lineStr);  
 }
}

char* setAlgorParamString(char* string, char* buffer){
 char temp[20] = {};
 if (sscanf(string, "%c%s", temp, buffer) == 0){
  printf("ERROR: algorParam string cannot be read\n");
  exit(0);
 }
 if(strcmp(temp, "-") != 0){
  printf("ERROR: algor flag must have -, Like: -CLOCK or -LRU\n");
  exit(0);
 }
}

void LRU_handlePageRequests(int* requestArr, int numRequests){ // References function defined in frameArray.c
 int requestsProcessed = 0;
 while(requestsProcessed < numRequests){
  LRU_RequestPageFromFrameArray(requestArr[requestsProcessed]);
  requestsProcessed++;
 }
}

void CLOCK_handlePageRequests(int* requestArr, int numRequests){ // References function defined in frameArray.c
 int requestsProcessed = 0;
 while(requestsProcessed < numRequests){
  SecondChance_RequestPageFromFrameArray(requestArr[requestsProcessed]);
  requestsProcessed++;
 }
}


int main(int argc, char *argv[]){
 //printf("adfasdfzzzzzzzzzzzzadsf3456ssfg\n");
 
  if(argc != 3){
   perror("ERROR: main requires 2 paramaters\n");
   exit(1);
  }
 char *fileName = argv[1];
 char algorParamStr[20] = {};
 char paramLineBuffer[30] = {};
 char param1[30] = {};
 char param2[30] = {};
 char param3[30] = {};
 char delim[10] = " "; 
 setAlgorParamString(argv[2], algorParamStr);
 getParamatersLineFromFile(fileName, paramLineBuffer); 
 splitStringIntoTokensAndPutNTokenIntoBuffer(paramLineBuffer, param1, delim, 1);
 splitStringIntoTokensAndPutNTokenIntoBuffer(paramLineBuffer, param2, delim, 2);
 splitStringIntoTokensAndPutNTokenIntoBuffer(paramLineBuffer, param3, delim, 3);
 
 int numberOfPages = atoi(param1);
 int numberOfFrames = atoi(param2);
 int numberOfPageRequests = atoi(param3);
 
 if(0 >= numberOfPages || 0 >= numberOfFrames || 0 >= numberOfPageRequests){
  printf("ERROR: Invalid paramater values. Paramaters in file must be greater than 0");
  exit(0);
 }
 
 int pageRequestSequenceArr[numberOfPageRequests];
 
 initIntArray(pageRequestSequenceArr, -1, numberOfFrames);
 setRequestSequenceArray(pageRequestSequenceArr, numberOfPageRequests, fileName);
 //printf("%d %d %d\n", numberOfPages, numberOfFrames, numberOfPageRequests);
 
 initializeFrameArray(numberOfFrames); // calls function in frameArray.c
 
 if (strcmp(algorParamStr, "LRU") == 0){
  printf("Simulating Page Request using LRU\n");
  LRU_handlePageRequests(pageRequestSequenceArr, numberOfPageRequests);
  printf("%d page faults\n", getPageFaultCount()); // getPageFaultCount() is defined in frameArray.c
 }
 else if(strcmp(algorParamStr, "CLOCK") == 0){
  printf("Simulating Page Request using CLOCK\n");
  CLOCK_handlePageRequests(pageRequestSequenceArr, numberOfPageRequests);
  printf("%d page faults\n", getPageFaultCount()); // getPageFaultCount() is defined in frameArray.c 
 }
 else {
  printf("ERROR: algorithm param must be -LRU or -CLOCK, received: -%s\n", algorParamStr);
  exit(0);
 }
 
 printf("End of program\n");
}
