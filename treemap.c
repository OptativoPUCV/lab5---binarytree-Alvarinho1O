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
if (tree == NULL || key == NULL || value == NULL) {
        return; 
    }
  
    Pair *existingPair = searchTreeMap(tree, key);
    if (existingPair != NULL) {
        return; 
    }

    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        return;
    }

    newNode->pair = (Pair *)malloc(sizeof(Pair));
    if (newNode->pair == NULL) {
        free(newNode);
        return; 
    }

    newNode->pair->key = key;
    newNode->pair->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;

    if (tree->root == NULL) {
        tree->root = newNode;
        tree->current = newNode;
    } else {
        TreeNode *currentNode = tree->root;

        while (1) {
            int compare_result = tree->lower_than(key, currentNode->pair->key);

            if (compare_result < 0) {
                if (currentNode->left == NULL) {
                    currentNode->left = newNode;
                    newNode->parent = currentNode;
                    tree->current = newNode;
                    break;
                } else {
                    currentNode = currentNode->left;
                }
            } else {
                if (currentNode->right == NULL) {
                    currentNode->right = newNode;
                    newNode->parent = currentNode;
                    tree->current = newNode;
                    break;
                } else {
                    currentNode = currentNode->right;
                }
            }
        }
    }

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    return;
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
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
