#ifndef frameArr_h
#define frameArr_h

#include "frame.h"

extern Frame* frameArray;

void initializeFrameArray(int);

void LRU_RequestPageFromFrameArray(int);

void SecondChance_RequestPageFromFrameArray(int);

void printFrameArray();

int getPageFaultCount();

#endif



