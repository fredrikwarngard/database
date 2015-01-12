#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list_module.h"
#include "db_main.h"


void* new_node(char* new_node_key, void* new_node_value) {
  Node newNode = malloc(sizeof(struct database));
  newNode->key = malloc(strlen(new_node_key) + 1);
  strcpy(newNode->key, new_node_key);
  newNode->value = malloc(strlen(new_node_value) + 1);
  strcpy(newNode->value, new_node_value);
  newNode->next = NULL;
  return newNode;
}


void* return_element(Node db, char* element_to_be_found){
  int found = 0;
  while(!found && db != NULL) {              
    if(strcmp(element_to_be_found, db->key) == 0) {       
      found = 1;
      return db;
    } else {
      db = db->next;                              
    }
  }
  return db;
}

/*
void* query_recursive(Node db, char* query_string) {
  if (db == NULL) {
    return db;
  }
  if (strcmp(query_string, db->key) == 0) {
    return db;
  } else {
    query_recursive(db->next, query_string);
  }
  return NULL;
}
*/

void* query(Node db, char* query_string) {
  //  Node element = query_recursive(db, query_string);
  Node element = return_element(db, query_string);
  return element;
}


void update (Node node_to_be_updated, void* new_value) {
  strcpy(node_to_be_updated->value, new_value);
  return;
}
  

void* get_insertion_spot(Node db) {
  while (db->next != NULL) {
    db = db->next;
  }
  return db;
}


void* insert(Node* db, Node new_node) {
  if (*db == NULL) {
    new_node->next = NULL;
    return new_node;
  }
  Node last = get_insertion_spot(*db);
  new_node->next = NULL;
  last->next = new_node;
  return *db;
}  


void* find_previous_node(Node db, Node node){
  printf("nu kollar vi: %s\n", db->key);
  if (strcmp(db->key, node->key) == 0) return NULL;
  while (strcmp((db->next)->key, node->key) != 0) {
    printf("nu kollar vi: %s\n", db->next->key);
    db = db->next;
  }
  return db;
}

/*
void* delete_first(Node* pointer_to_pointer) {
  Node db = *pointer_to_pointer;
  Node element = db;
  if (db->next != NULL) {
    printf("pointer_to_pointer = %s\n", (*pointer_to_pointer)->key);
    pointer_to_pointer = &(db->next);
    printf("pointer_to_pointer = %s\n", (*pointer_to_pointer)->key);
    db = NULL;
    free(element);
    return *pointer_to_pointer;
  } else {
    *pointer_to_pointer = NULL;
    free(element);
    return *pointer_to_pointer;
  }
}
*/

void* delete(Node* db, Node node_to_be_deleted) {
  Node prev_node = find_previous_node(*db, node_to_be_deleted);
  if (prev_node == NULL) {
    Node temp = *db;
    db = &((*db)->next);
    free(temp->key);
    free(temp->value);
    free(temp);
    // *db = delete_first(db);
    return *db;
  }
  prev_node->next = node_to_be_deleted->next;
  free(node_to_be_deleted->key);
  free(node_to_be_deleted->value);
  free(node_to_be_deleted);
  return *db;
}


void print(Node db) {              
  printf("Keys\t\tValues\n");
  while(db != NULL) {
    printf("%s\t\t", db->key);
    printf("%s\n", db->value);
    db = db->next;
  }
}
