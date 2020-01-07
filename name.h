/*
Name: Lilian Shi
ID: 1048355
email: lshi02@uoguelph.ca
*/
#ifndef nameh
#define nameh
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "common.h"

struct name_basics{
  char* nconst;
  char* primaryName;
};
typedef struct name_basics namebasics;

struct name_array{
  int nelements;
  namebasics* array;
  treenode* tree_const;
  treenode* tree_name;
};
typedef struct name_array namearray;
namearray get_name(char*);
void build_tree_name(struct name_array*);
void build_tree_nconst(struct name_array*);
struct name_basics* find_primary_name(char*, struct tree_node*);
struct name_basics* find_nconst(char*, struct tree_node*);
#endif
