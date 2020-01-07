/*
Name: Lilian Shi
ID: 1048355
email: lshi02@uoguelph.ca
*/
#include "name.h"
#include "common.h"
#include "binary.h"
#define LINE_SIZE 256

/*HELPER FUNCTION TO COUNT NUMBER OF ACTORS*/
int getNumActors(FILE* fp){
  char* buffer = malloc(LINE_SIZE);
  int numA = 0;

  fgets(buffer, LINE_SIZE, fp); /*read in the category names to not screw up alignment*/
  do{
    char* col;
    fgets(buffer, LINE_SIZE, fp);
    get_column(buffer, &col, 5, LINE_SIZE);
    if(strstr(col, "actress") != NULL || strstr(col, "actor") != NULL)
      numA++;

    free(col);
  }while(!feof(fp));

  free(buffer);
  return numA;
}
/*REtURN PTR TO START OF WHOLE NAMEBASICS ARRAY*/
namearray get_name(char* path){
  char* fullpath = malloc(500);
  FILE* fp;
  char* buffer = malloc(LINE_SIZE);
  namebasics* nbasics;
  namearray toReturn;

  int numA = 0;
  int i = 0;

  strcpy(fullpath, path);
  strcat(fullpath, "/name.basics.tsv");

  fp = fopen(fullpath, "r");
  numA = getNumActors(fp);

  toReturn.nelements = numA;
  nbasics = malloc(toReturn.nelements*(sizeof(namebasics)));
  fseek(fp, 0, SEEK_SET);


  /*read in array*/
  do{
    char* col;
    fgets(buffer, LINE_SIZE, fp);

    get_column(buffer, &col, 5, LINE_SIZE);
    if(strstr(col, "actress") != NULL || strstr(col, "actor") != NULL){
      get_column(buffer, &nbasics[i].nconst, 1, LINE_SIZE);
      get_column(buffer, &nbasics[i].primaryName, 2, LINE_SIZE);
      reverse(nbasics[i].nconst);
      i++;
    }

    free(col);
  }while(!feof(fp));
  fclose(fp);

  toReturn.array = nbasics;
  toReturn.tree_name = NULL;
  toReturn.tree_const = NULL;
  return toReturn;
}

void build_tree_name(struct name_array* narray){
  int i;
  for(i = 0; i < narray->nelements; i++){
    add_node(&(narray->tree_name), narray->array[i].primaryName, &narray->array[i]);
  }
}

void build_tree_nconst(struct name_array* narray){
  int i;
  for(i = 0; i < narray->nelements; i++){
    add_node(&(narray->tree_const),narray->array[i].nconst, &narray->array[i]);
  }
}

struct name_basics* find_primary_name(char* key, struct tree_node* tree){
  treenode* found;
  found = (treenode*)find_node(tree, key);
  if(found == NULL){
    printf("\nNot found.");
    return NULL;
  }
  return (struct name_basics*)(found->data);
}

struct name_basics* find_nconst(char* key, struct tree_node* tree){

 treenode* found = (treenode*)find_node(tree, key);
  if(found == NULL){
    printf("\nNot found.");
    return NULL;
  }
  return (struct name_basics*)(found->data);
}
