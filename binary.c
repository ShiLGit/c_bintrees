#include "binary.h"
#include "title.h"

void add_node(treenode** root, char* key, void* ele){
  if(*root){
    if(strcmp(key, (*root)->key) < 0) { /*node goes in left child if node's key < root key*/
      add_node(&((*root)->left_child), key, ele);
    }else{
      add_node(&(*root)->right_child, key, ele);
    }
  }else{ /*node goes in right child if >= root's key*/
/*    printf("\nMaking new node for key = %s", key);
*/    (*root) = malloc(sizeof(treenode));
    (*root)->data = ele;
    (*root)->left_child = NULL;
    (*root)->right_child = NULL;
    (*root)->key = key;
  }
}
void* find_node(treenode* root, char* key){
  if(root){
    /*printf("\nstrcmp(%s, %s) = %d", key, root->key, strcmp(key, root->key));
   */if(strcmp(key, root->key) == 0){
      return root;
    }
    if(strcmp(key, root->key) < 0){
      return find_node(root->left_child, key);
    }else{
      return find_node(root->right_child, key);
    }
  }else{
    return NULL;
  }
}
void free_tree(treenode* root )
{
  if (root)
  {
    free_tree( root->right_child );
    free_tree( root->left_child );
    free( root );
  }
}
