/*
Name: Lilian Shi
ID: 1048355
email: lshi02@uoguelph.ca
*/
#ifndef titleh
#define titleh
#include "common.h"

struct title_basics{
  char* tconst;
  char* primaryTitle;
};
typedef struct title_basics titlebasics;

struct title_array{
  int nelements;
  titlebasics* array;
  treenode* tree_const;
  treenode* tree_title;
};
typedef struct title_array titlearray;
titlearray get_title(char*);
void build_tree_title(struct title_array*);
void build_tree_tconst(struct title_array*);
struct title_basics* find_primary_title(char*, struct tree_node*);
struct title_basics* find_tconst(char*, struct tree_node*);
#endif
