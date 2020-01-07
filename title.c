/*
Name: Lilian Shi
ID: 1048355
email: lshi02@uoguelph.ca
*/
#include "title.h"
#include "common.h"
#include "binary.h"
#define LINE_SIZE 900

titlearray get_title(char* path){
  char* fullpath = malloc(500);
  FILE* fp;
  char* buffer = malloc(LINE_SIZE);
  int numT = 0;
  int i = 0;
  char *col2, *col5;
  titlebasics* tbasics;
  titlearray toReturn;

  strcpy(fullpath, path);
  strcat(fullpath, "/title.basics.tsv");
  fp = fopen(fullpath, "r");

  /*count array size*/
  do{
    i++;
    fgets(buffer, LINE_SIZE, fp);
    get_column(buffer, &col5, 5, LINE_SIZE);
    get_column(buffer,&col2, 2,LINE_SIZE);

    if(strstr(col5, "0") != NULL&&strstr(col2, "movie") != NULL){
      numT++;
    }
  }while(!feof(fp));

  toReturn.nelements = numT;
  tbasics = malloc(sizeof(titlebasics)*toReturn.nelements);
  fseek(fp, 0, SEEK_SET);

  i = 0;
  /*read in array */
  do{
    fgets(buffer, LINE_SIZE, fp);
    get_column(buffer, &col5, 5, LINE_SIZE);
    get_column(buffer,&col2, 2,LINE_SIZE);

    if(strstr(col5, "0") != NULL&&strstr(col2, "movie") != NULL){
      get_column(buffer, &tbasics[i].tconst, 1, LINE_SIZE);
      get_column(buffer, &tbasics[i].primaryTitle, 3, LINE_SIZE);
      reverse(tbasics[i].tconst);
      i++;
    }
  }while(!feof(fp) );
  fclose(fp);

  toReturn.array = tbasics;
  toReturn.tree_const = NULL;
  toReturn.tree_title = NULL;
  return toReturn;
}

void build_tree_title(struct title_array* tarray){
  int i;
  for(i = 0; i < tarray->nelements; i++){
    add_node(&(tarray->tree_title), tarray->array[i].primaryTitle, &tarray->array[i]);
  }
}
void build_tree_tconst(struct title_array* tarray){
  int i;
  for(i = 0; i < tarray->nelements; i++){
    add_node(&(tarray->tree_const), tarray->array[i].tconst, &tarray->array[i]);
  }
}

struct title_basics* find_primary_title(char* key, struct tree_node* tree){
  treenode* found;
  found  = (treenode*)find_node(tree, key);
  if(found == NULL){
    printf("\nNot found.");
    return NULL;
  }
  return (struct title_basics*)(found->data);
}
struct title_basics* find_tconst(char* key, struct tree_node* tree){

 treenode* found = (treenode*)find_node(tree, key);
  if(found == NULL){
    printf("\nNot found.");
    return NULL;
  }
  return (struct title_basics*)(found->data);
}
