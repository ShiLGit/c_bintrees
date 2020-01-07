/*
Name: Lilian Shi
ID: 1048355
email: lshi02@uoguelph.ca
*/
#include "principals.h"
#include "common.h"
#include "binary.h"
#define LINE_SIZE 500

parray get_principals(char* path){
  char *fullpath = malloc(500);
  char buffer[LINE_SIZE];
  char *col;

  int numP = 0;
  FILE* fp;
  int i = 0;
  int rIndex = 0;
  titlep* tprincipals;
  parray toReturn;


  strcpy(fullpath, path);
  strcat(fullpath, "/title.principals.tsv");
  fp = fopen(fullpath, "r");
  free(fullpath);

  do{
    fgets(buffer, LINE_SIZE, fp);

    if(i == 1412549){ /*skip weird line...?*/
      fgets(buffer, LINE_SIZE, fp);
    }
    get_column(buffer, &col, 4, LINE_SIZE);
    if(strstr(col, "actor") != NULL || strstr(col, "actress") != NULL){
      numP++;
    }
    i++;
  }while(!feof(fp));

  /*read in array*/
  fseek(fp, 0, SEEK_SET);
  tprincipals = malloc(sizeof(titlep) * numP);
  do{

    fgets(buffer, LINE_SIZE, fp);
    if(i == 1412549){ /*skip weird line...?*/
      fgets(buffer, LINE_SIZE, fp);
    }

    get_column(buffer, &col, 4, LINE_SIZE);
    if(strstr(col, "actor") != NULL || strstr(col, "actress") != NULL){
      get_column(buffer, &tprincipals[rIndex].tconst, 1, LINE_SIZE);
      get_column(buffer, &tprincipals[rIndex].nconst, 3, LINE_SIZE);
      get_column(buffer, &tprincipals[rIndex].characters, 6, LINE_SIZE);
      reverse(tprincipals[rIndex].tconst);
      reverse(tprincipals[rIndex].nconst);

      rIndex++;
    }
    i++;
  }while(!feof(fp));
  fclose(fp);

  toReturn.nelements = numP;
  toReturn.array = tprincipals;
  toReturn.tree_nconst = NULL;
  toReturn.tree_tconst = NULL;
  return toReturn;
}
void build_tree_nconstP(struct principals_array* prarray){
  int i;
  for(i = 0; i < prarray->nelements; i++){
    add_node(&(prarray->tree_nconst), prarray->array[i].nconst, &prarray->array[i]);
  }
}
void build_tree_tconstP(struct principals_array* prarray){
  int i;
  for(i = 0; i < prarray->nelements; i++){
    add_node(&(prarray->tree_tconst), prarray->array[i].tconst, &prarray->array[i]);
  }
}
struct title_principals* find_consts(char* key, struct tree_node *tree){

  treenode* found;
  found = (treenode*)find_node(tree, key);
  if(found == NULL){
    printf("\nNot found.");
    return NULL;
  }
  return (struct title_principals*)(found->data);
}
