#ifndef commonh
#define commonh

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct tree_node{
  char* key;
  void *data;
  struct tree_node* left_child;
  struct tree_node* right_child;
};
typedef struct tree_node treenode;
void get_column(char*, char**, int, int);
void reverse(char*);

#endif
