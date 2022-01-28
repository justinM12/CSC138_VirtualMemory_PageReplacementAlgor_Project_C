#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <string.h>
#include <ctype.h> 

#include "frame.h"

Frame *createFrame(){
 Frame *f = malloc(sizeof(Frame));
 f->time = 0;
 f->referenceBit = 0;
 f->pageStored = -1;
 return f;
}

int getFrameTime(Frame* frame){
 return frame->time;
}

int getFrameReferenceBit(Frame* frame){
 return frame->referenceBit;	
}

void updateFrameTime(Frame* frame, int val){
 frame->time = val;
}

void updateFrameReferenceBit(Frame* frame, int val){ 
 frame->referenceBit = val;
}

void updateFrameStoredPage(Frame* frame, int val){ 
 frame->pageStored = val;
}
