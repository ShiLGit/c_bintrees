/*
Name: Lilian Shi
ID: 1048355
email: lshi02@uoguelph.ca
*/

#include "binary.h"
#include "common.h"
#include "name.h"
#include "principals.h"
#include  "title.h"

struct argument{
  int operation;
  char* key;
};
struct argument promptAndTrim(){
  struct argument argument;
  char buffer[50];
  char* cmd;
  char* arg;
  int i;
  int endIndex;
  arg = malloc(50);
  printf("\n> ");
  fgets(buffer, 50, stdin);

  i = 0;
  cmd = buffer;
  do{
    if(*cmd != ' '){
      do{
        arg[i] = *cmd;
        i++;
        cmd++;
      }while(*cmd != ' ' && *cmd != '\0');
    }
    i++;
    cmd++;
  }while(*cmd == ' ');
  arg[--i] = '\0';
  if(strcmp(arg, "name") == 0 || strcmp(arg, "name\n") == 0)
    argument.operation = 1;
  else if(strcmp(arg, "title") == 0 || strcmp(arg, "title\n"))
    argument.operation = 2;
  else if(strcmp(arg, "exit") == 0 ||strcmp(arg, "exit\n"))
    argument.operation = 0;

  i = 0;
  strcpy(arg, "");
  endIndex = strlen(buffer) - 1;
  for(;buffer[endIndex] == ' '; endIndex--){}
  buffer[endIndex + 1] = '\0';

  do{
    arg[i] = *cmd;
    cmd++;
    i++;
    if(*cmd == '\n' || *cmd == '\0'){
      arg[i] = '\0';
      break;
    }
  }while(*cmd != '\0');
  arg[++i] = '\0';

  argument.key = arg;
  return argument;
}

int main(int argc, char* argv[]){
  int flag = 1;
  char* key;
  struct argument cmd;
  struct principals_array p_array;
  struct name_array n_array;
  struct title_array t_array;
  struct name_basics* dummyN;
  struct title_principals* dummyP;
  struct title_basics* dummyT;
  treenode* treeExplorer;
  p_array = get_principals(argv[1]);
  n_array = get_name(argv[1]);
  t_array = get_title(argv[1]);

  build_tree_nconstP(&p_array);
  build_tree_tconstP(&p_array);
  build_tree_nconst(&n_array);
  build_tree_name(&n_array);
  build_tree_title(&t_array);
  build_tree_tconst(&t_array);

  cmd = promptAndTrim();
  key = malloc(200);

  do{
    do{
      if(cmd.operation == 1){ /*Carry out operation 1) */
        dummyN = find_primary_name(cmd.key, n_array.tree_name);
        if(dummyN ==NULL){
          break;
        }

        treeExplorer = p_array.tree_nconst;
      do{
          strcpy(key, dummyN->nconst);
          treeExplorer = find_node(treeExplorer, key);
          dummyP = find_consts(key, treeExplorer);
          if(dummyP == NULL){
            break;
          }
          strcpy(key, dummyP->tconst);
          reverse(key);
          dummyT = find_primary_title(dummyP->tconst, t_array.tree_const);
          if(dummyT == NULL){
            break;
          }

          printf("\n%s : %s", dummyT->primaryTitle, dummyP->characters);
          treeExplorer = treeExplorer->right_child;
        }while(treeExplorer);
        break;
      }else if(cmd.operation == 2){ /*Operation 2 */

        dummyT = find_primary_title(cmd.key, t_array.tree_title);
        if(dummyT == NULL)
          break;

        treeExplorer = p_array.tree_tconst;
        do{
          dummyP = find_consts(dummyT->tconst, treeExplorer);
          if(dummyP == NULL)
            break;

          dummyN = find_nconst(dummyP->nconst, n_array.tree_const);
          if(dummyN == NULL)
            break;

          printf("\n%s : %s", dummyN->primaryName, dummyP->characters);
          treeExplorer = treeExplorer->right_child;
        }while(treeExplorer);
        break;
      }else if(cmd.operation == 0){
        flag = 0;
        break;
      }else{
	break;
      }
    }while(flag);
    if(flag == 0)
      break;
    cmd = promptAndTrim();
  }while(flag);

  free(cmd.key);
  free_tree(t_array.tree_const);
  free_tree(t_array.tree_title);
  free_tree(n_array.tree_const);
  free_tree(n_array.tree_name);
  free_tree(p_array.tree_nconst);
  free_tree(p_array.tree_tconst);

  free(cmd.key);
  free(key);

  return 0;
}
