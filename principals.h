/*
Name: Lilian Shi
ID: 1048355
email: lshi02@uoguelph.ca
*/
#ifndef principalsh
#define principalsh
#include "common.h"
struct title_principals{
  char* tconst;
  char *nconst;
  char* characters;
};
typedef struct title_principals titlep;

struct principals_array{
  int nelements;
  titlep* array;
  treenode* tree_nconst;
  treenode* tree_tconst;
};
typedef struct principals_array parray;

struct principals_array get_principals(char*);
void build_tree_nconstP(struct principals_array*);
void build_tree_tconstP(struct principals_array*);
struct title_principals* find_consts(char*, struct tree_node*);
#endif
