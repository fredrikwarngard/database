// #include <stdio.h>
#ifndef new_module
#define new_module


typedef struct database {
  char *key;
  char *value;
  struct database *next;
} *Node;


void* new_node(char*, void*);
void* return_element(Node, char*);
void* query(Node, char*);
void update(Node, void*);
void* get_insertion_spot(Node);
void* insert(Node*, Node);
void* find_previous_node(Node, Node);
//void* delete_first(Node*);
void* delete(Node*, Node);
void print(Node);

#endif
