#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void replaceNewLineWithNullChar(char* string){
  char *ptr = strchr(string, '\n');
  if(ptr != NULL){
   *ptr = '\0'; 
  }
 }
 
void putLineFromFileIntoBufferUsingLine(char* filePath, char* buffer, int lineNumber){
 char *fileLineBuffer = NULL;
 size_t bufferSize = 0;
 FILE *file;

 file = fopen(filePath, "r");
 if(file == NULL){
  printf("ERROR: could not open file\n");
  exit(1);
 }
 fseek(file, 0, SEEK_SET);

 int i;
 for(i = 0; i < lineNumber; i++){
 ssize_t  result = getline(&fileLineBuffer, &bufferSize, file);
 //printf("%s\n", fileLineBuffer);
  if(result == -1){
   printf("Error: could not read line\n");
   exit(1);
  }
 } 
 fclose(file);
 int len = strlen(fileLineBuffer);
 replaceNewLineWithNullChar(fileLineBuffer);
 strncpy(buffer, fileLineBuffer, strlen(fileLineBuffer));
 free(fileLineBuffer);
}

void splitStringIntoTokensAndPutNTokenIntoBuffer(char* string, char* buffer, char* delim, int tokenNum){
 char* temp = strdup(string);
 char* token = strtok(temp, delim);
 if(tokenNum == 1){
  strcpy(buffer, token);
  return;
 }
 int i = 1;
 while(i < tokenNum){
  token = strtok(NULL, delim);
  i++;
 }
 strcpy(buffer, token);
 free(temp);
 }