// #include <stdio.h>
#ifndef new_module
#define new_module


typedef struct database {
  char *key;
  char *value;
  struct database *parent;
  struct database *leftChild;
  struct database *rightChild;
} *Node;


void* new_node(char*, void*);
void* return_element(Node, char*);
void* query(Node, char*);
void update(Node, void*);
void* put_node_in_tree (Node, Node);
void* insert(Node*, Node);
void* maximum(Node);
//void* delete_first(Node*);
void free_node(Node);
void* delete(Node*, Node);
void print(Node);

#endif
