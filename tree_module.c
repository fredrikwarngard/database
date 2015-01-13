#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree_module.h"
#include "db_main.h"


void* new_node(char* new_node_key, void* new_node_value) {
  Node newNode = malloc(sizeof(struct database));
  newNode->key = malloc(strlen(new_node_key) + 1);
  strcpy(newNode->key, new_node_key);
  newNode->value = malloc(strlen(new_node_value) + 1);
  strcpy(newNode->value, new_node_value);
  newNode->leftChild = NULL;
  newNode->rightChild = NULL;
  newNode->parent = NULL;
  return newNode;
}


void* return_element(Node db, char* element_to_be_found){
  int found = 0;
  while(!found && db != NULL) {              
    if (strcmp(element_to_be_found, db->key) == 0) {       
      found = 1;
      return db;
    } else if (strcmp(element_to_be_found, db->key) < 0) {
      db = db->leftChild;
    } else {
      db = db->rightChild;
    }
  }
  return db;
}


void* query(Node db, char* query_string) {
  Node element = return_element(db, query_string);
  return element;
}


void update (Node node_to_be_updated, void* new_value) {
  strcpy(node_to_be_updated->value, new_value);
  return;
}
  

void* put_node_in_tree (Node db, Node new_node) {
  while (db != NULL) {
    if (strcmp((db->key), (new_node->key)) > 0) {
      if (db->leftChild != NULL) {
	db = db->leftChild;
      } else {
	db->leftChild = new_node;
	new_node->parent = db;
	return new_node;
      }
    } else {
      if (db->rightChild != NULL) {
	db = db->rightChild;
      } else {
	db->rightChild = new_node;
	new_node->parent = db;
	return new_node;
      }
    }
  }
  return 0;
}


void* insert(Node* db, Node new_node) {
  Node root = *db;
  if (*db == NULL) {
    return new_node;
  }
  *db = put_node_in_tree (*db, new_node);
  return root;
}


void* maximum(Node bst) {
  while (bst->rightChild != NULL) {
    bst = bst->rightChild;
  }
  return bst;
}

void free_node(Node x) {
  free(x->key);
  free(x->value);
  free(x);
}


void* delete (Node* db, Node node_to_be_deleted) {
  Node root = *db;
  Node parent = node_to_be_deleted->parent;
  printf("%s heter noden som skall tas bort\n", node_to_be_deleted->key);
 
  //IF NODE IS A LEAF
  if (node_to_be_deleted->leftChild == NULL && node_to_be_deleted->rightChild == NULL) {
    if (parent == NULL) {
      free_node(node_to_be_deleted);
      return NULL;
    }
    if (parent->leftChild == node_to_be_deleted) {
      parent->leftChild = NULL;
      free_node(node_to_be_deleted);
    }
    if (parent->rightChild == node_to_be_deleted) {
      parent->rightChild = NULL;
      free_node(node_to_be_deleted);
    }
  }

  // IF NODE ONLY HAVE ONE CHILD
  else if (node_to_be_deleted->leftChild == NULL) {
    if (parent == NULL) {
      puts("boyaaa!");
      root = node_to_be_deleted->rightChild;
      puts("Still OK?");
      root->parent = NULL;
      puts("Still... OK?");
      free_node(node_to_be_deleted);
      puts("Freed?");
    }
    else if (parent->leftChild == node_to_be_deleted) {
      parent->leftChild = node_to_be_deleted->rightChild;
      node_to_be_deleted->rightChild->parent = parent;
      free_node(node_to_be_deleted);
    }
    else if (parent->rightChild == node_to_be_deleted) {
      parent->rightChild = node_to_be_deleted->rightChild;
      node_to_be_deleted->rightChild->parent = parent;
      free_node(node_to_be_deleted);
    }
  }
  
  else if (node_to_be_deleted->rightChild == NULL) {
    if (parent == NULL) {
      puts("cool school!");
      root = node_to_be_deleted->leftChild;
      root->parent = NULL;
      free_node(node_to_be_deleted);
    }
    else if (parent->leftChild == node_to_be_deleted) {
      parent->leftChild = node_to_be_deleted->leftChild;
      node_to_be_deleted->leftChild->parent = parent;
      free_node(node_to_be_deleted);
    }
    else if (parent->rightChild == node_to_be_deleted) {
      parent->rightChild = node_to_be_deleted->leftChild;
      node_to_be_deleted->leftChild->parent = parent;
      free_node(node_to_be_deleted);
    }
  }  
  
  //IF THERE ARE TWO CHILDREN
  else if (node_to_be_deleted->leftChild != NULL && node_to_be_deleted->rightChild != NULL) {
    Node max = maximum(node_to_be_deleted->leftChild);
    node_to_be_deleted->key = max->key;
    node_to_be_deleted->value = max->value;
    if (node_to_be_deleted->leftChild->leftChild == NULL && node_to_be_deleted->leftChild->rightChild == NULL) {
      Node temp = node_to_be_deleted->leftChild;
      node_to_be_deleted->leftChild = NULL;
      free_node(temp);
    } else {
      node_to_be_deleted->leftChild = delete(&(node_to_be_deleted->leftChild), max);
    }
  }
  else {
    puts("Something went wrong!");
  }
  return root;
}

void print(Node db) {
  if (db != NULL) {
    print(db->leftChild);
    printf("%s\t\t", db->key);
    printf("%s\n", db->value);    
    print(db->rightChild);
  }
}
