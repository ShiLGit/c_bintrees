#include "common.h"

void get_column(char* line, char** copyInto, int col, int lineSize){
  int i = 0;
  int index = 0;
  int tabCount = 0;
  char* buffer = malloc(lineSize);

  /*traverse to tab before column*/
  if(col != 1){
    do{
      if(line[index] == '\t'){
        tabCount++;
        if(tabCount == col - 1){
          index++;
          break;
        }
      }
      index++;
    }while(line[index] != '\0');
  }

  /*copy string into buffer that will be copied into cpyinto*/
  do{
    /*edge case non-entry in this column.*/
    if(line[index] == '\t'){
      break;
    }

    buffer[i++] = line[index++];
  }while(line[index] != '\t' && line[index] != '\n');
  buffer[i] = '\0';

  /*allocate memory for copyInto*/
  *copyInto = malloc(strlen(buffer) + 1);
  strcpy(*copyInto, buffer);
}

void reverse(char* str){
  int end = strlen(str) - 1;
  int start = 0;

  char* rstr = malloc(strlen(str) + 1);

  do{
    rstr[start] = str[end];
    end--;
    start++;
  }while(end > -1);
  rstr[strlen(str)] = '\0';
  strcpy(str, rstr);
  free(rstr);
}
