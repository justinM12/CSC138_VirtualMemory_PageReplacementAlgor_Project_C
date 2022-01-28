#ifndef readFile_h
#define readFile_h

void replaceNewLineWithNullChar(char*);

void putLineFromFileIntoBufferUsingLine(char*, char*, int);

void splitStringIntoTokensAndPutNTokenIntoBuffer(char*, char*, char*, int);
#endif