#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "frameArray.h"

Frame* frameArray = NULL;

int frameArraySize = 0;
int pageFaultCount = 0;

void initializeFrameArray(int size){
 frameArray = malloc(sizeof(Frame)*size);
 int i;
 for(i=0;i<size;i++){
  frameArray[i] = *createFrame();
 }
 frameArraySize = size; 
}

int count = 0;

void LRU_RequestPageFromFrameArray(int pageNumber){
 if(frameArray == NULL){
  printf("ERROR: initalizeFrameArray() needs to be called before Requests functions can be called\n");
  exit(0);
 }
 // run LRU replacement algorithm
 
 // Increment the time of all frames
 int isFrameInPageTable = 0; // 0 = false, 1 = true
 int indexOfTbWithPage = -1;
 int i;
 for(i=0;i<frameArraySize;i++){
  if(frameArray[i].pageStored != -1){
   frameArray[i].time = frameArray[i].time + 1;
   // check if page is stored in frameArray
   if(frameArray[i].pageStored == pageNumber){
    isFrameInPageTable = 1;
    indexOfTbWithPage = i;
   }
  }
 }
 if(isFrameInPageTable){
  // If page in frame array, update frame time to 0
  frameArray[indexOfTbWithPage].time = 0;
  printf("Page %d already in  Frame %d\n", pageNumber, indexOfTbWithPage);  
 }
 else{
  // If not all frames have been filled, then load page into empty frames
  if(count != frameArraySize){
   pageFaultCount++;
   frameArray[count].pageStored = pageNumber;
   printf("Page %d loaded into Frame %d\n", pageNumber, count);
   count++;
   return;
  }
  // If page not in frame array, find frame with longest time and replace it
  pageFaultCount++;
  int idexOfPageToRemove = -1;
  int max = -1;
  for(i=0;i<frameArraySize;i++){
   if(frameArray[i].time > max){
    max = frameArray[i].time;
	idexOfPageToRemove = i;
   }
  }
  if(idexOfPageToRemove == -1){
   printf("ERROR: idexOfPageToRemove is -1, frameArray.c\n");
   exit(1);   
  }
  
  printf("Page %d unloaded from Frame %d, Page %d loaded into Frame %d\n", frameArray[idexOfPageToRemove].pageStored, idexOfPageToRemove, pageNumber, idexOfPageToRemove);
  frameArray[idexOfPageToRemove].pageStored = pageNumber;
  frameArray[idexOfPageToRemove].time = 0;
 }
  
}

int tracker = 0; // keep track of which frame is the oldest frame and which frame to try and remove

void SecondChance_RequestPageFromFrameArray(int pageNumber){
 if(frameArray == NULL){
  printf("ERROR: initalizeFrameArray() needs to be called before Requests functions can be called\n");
  exit(0);
 }
 
 // run SecondChance replacement algorithm
 // check if page is stored in frameArray
 int isFrameInPageTable = 0; // 0 = false, 1 = true
 int indexOfTbWithPage = -1;
 int i;
 for(i=0;i<frameArraySize;i++){
  if(frameArray[i].pageStored != -1){
   if(frameArray[i].pageStored == pageNumber){
    isFrameInPageTable = 1;
    indexOfTbWithPage = i;
   }
  }
 }
 if(isFrameInPageTable){
  // If page in frame array, set referenceBit to 1 and increment tracker;
  frameArray[indexOfTbWithPage].referenceBit = 1;
  printf("Page %d already in Frame %d\n", pageNumber, indexOfTbWithPage);  
 }
 else{
  // If not all frames have been filled, then load page into empty frames
  if(count != frameArraySize){
   pageFaultCount++;
   frameArray[count].pageStored = pageNumber;
   printf("Page %d loaded into Frame %d\n", pageNumber, count);
   count++;
   return;
  }
  // If page not in frame array
  pageFaultCount++;  
  int isFrameToReplaceFound = 0;
  while(isFrameToReplaceFound != 1){
   if(frameArray[tracker].referenceBit == 1){ // check if frame at index 'tracker' has referenceBit set, if referenceBit is set then set to 0, increment tracker and check next frame
    frameArray[tracker].referenceBit = 0;
	
	tracker++;
    tracker = tracker % frameArraySize;
   }
   else if(frameArray[tracker].referenceBit == 0){ // if current frame's reference bit is not set, replace pageStored and increment tracker
    printf("Page %d unloaded from Frame %d, Page %d loaded into Frame %d\n", frameArray[tracker].pageStored, tracker, pageNumber, tracker);
    frameArray[tracker].pageStored = pageNumber;
	
	tracker++;
    tracker = tracker % frameArraySize;
	
    isFrameToReplaceFound = 1;	
   }
   else {
    printf("ERROR: code should not be able to reach here in Clock handle, frameArray.c\n");
	exit(0);
   }
  }	  
 }
 
}

void printFrameArray(){

}

int getPageFaultCount(){
 return pageFaultCount;
}