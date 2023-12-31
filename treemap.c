#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;

struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}

TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int(*lt)(void* key1,void* key2)){
    TreeMap *map = (TreeMap *)malloc(sizeof(TreeMap));
    if (map == NULL) {
        return NULL;
    }
    map->root = NULL;
    map->current = NULL;
    map->lower_than=lt;
    return map;
}

void insertTreeMap(TreeMap * tree, void* key, void * value){
  TreeNode* current=tree->root;
  TreeNode* newNode=createTreeNode(key,value);

  while(current!=NULL){
    if(is_equal(tree,key,current->pair->key)){
      return;
    }else if(tree->lower_than(key,current->pair->key)){
      if(current->left==NULL){
        current->left=newNode;
        newNode->parent=current;
        tree->current=newNode;
        return;
      }else{
        current=current->left;
      }
    }else{
      if (current->right==NULL){
        current->right=newNode;
        newNode->parent=current;
        tree->current=newNode;
        return;
      }else{
        current=current->right;
      }
    }
  }
}

TreeNode * minimum(TreeNode * x){
  if (x == NULL){
        return NULL;
    }
    while (x->left != NULL){
        x = x->left;
    }
    return x;
}

void removeNode(TreeMap * tree, TreeNode* node){
    if(tree == NULL || node == NULL || tree->root == NULL){
        return;
    }

    if(node->left == NULL && node->right == NULL){
        TreeNode *parent = node->parent;

        if(parent == NULL){
            tree->root = NULL;
        }else if(parent->left == node){
            parent->left = NULL;
        }else{
            parent->right = NULL;
        }

        free(node->pair);
        free(node);
    }
    else if(node->left == NULL || node->right == NULL){
        TreeNode *child = (node->left != NULL) ? node->left : node->right;
        TreeNode *parent = node->parent;

        if(parent == NULL){
            tree->root = child;
            child->parent = NULL;
        }else if(parent->left == node){
            parent->left = child;
            child->parent = parent;
        }else{
            parent->right = child;
            child->parent = parent;
        }

        free(node->pair);
        free(node);
    }
    else{
        TreeNode *minRight = minimum(node->right);
        node->pair->key = minRight->pair->key;
        node->pair->value = minRight->pair->value;
        removeNode(tree, minRight);
    }
}
   
void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}

Pair * searchTreeMap(TreeMap * tree, void* key){
  if (tree==NULL || tree->root==NULL){
    return NULL;
  }
  TreeNode* current=tree->root;
  while (current!=NULL){
    if (is_equal(tree, key, current->pair->key)){
      tree->current=current;
      return tree->current->pair; 
    } else if(tree->lower_than(key, current->pair->key)){
      current=current->left;
    } else{
      current=current->right;
    }
  }
  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    if(tree == NULL || tree->root == NULL || key == NULL){
        return NULL;
    }
    TreeNode *currentNode = tree->root;
    TreeNode *ub_node = NULL;

    while(currentNode != NULL){
        int compare_result = tree->lower_than(key, currentNode->pair->key);
        if(compare_result == 0){
            tree->current = currentNode;
            return currentNode->pair;
        }else if(compare_result < 0){
            ub_node = currentNode;
            currentNode = currentNode->left;
        }else{
            currentNode = currentNode->right;
        }
    }
    if(ub_node != NULL){
        tree->current = ub_node;
        return ub_node->pair;
    }
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    if (tree == NULL || tree->root == NULL) {
        return NULL; 
    }
    TreeNode *minNode = minimum(tree->root);
    if (minNode != NULL) {
        tree->current = minNode;
        return minNode->pair;
    }

    return NULL;
}

Pair * nextTreeMap(TreeMap * tree){
  if(tree == NULL || tree->current == NULL){
      return NULL; 
    }
    TreeNode *currentNode = tree->current;
    if(currentNode->right != NULL){
        TreeNode *minNode = minimum(currentNode->right);
        tree->current = minNode;
        return minNode->pair;
    }
    TreeNode *parent = currentNode->parent;
    while(parent != NULL && currentNode == parent->right){
        currentNode = parent;
        parent = parent->parent;
    }
    tree->current = parent;
    if(parent != NULL){
      return parent->pair;
    } else {
        return NULL; 
    }
    return NULL;
}
