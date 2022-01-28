#ifndef frame_h
#define frame_h

typedef struct Frame{
 int time;
 int referenceBit;
 int pageStored;
}Frame;

Frame* createFrame();

int getFrameTime(Frame*);

int getFrameReferenceBit(Frame*);

void updateFrameTime(Frame*, int);

void updateFrameReferenceBit(Frame*, int);

void updateFrameStoredPage(Frame*, int);

#endif