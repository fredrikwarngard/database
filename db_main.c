#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef listan
#include "list_module.h"
#else
#include "tree_module.h"
#endif


void readline(char *dest, int n, FILE *source) {
  fgets(dest, n, source);
  int len = strlen(dest);
  if(dest[len-1] == '\n')
    dest[len-1] = '\0';
}


void database_print_opening(char *filename) {
  puts("Welcome to");
  puts(" ____    ____       ");
  puts("/\\  _`\\ /\\  _`\\     ");
  puts("\\ \\ \\/\\ \\ \\ \\L\\ \\   ");
  puts(" \\ \\ \\ \\ \\ \\  _ <\\ ");
  puts("  \\ \\ \\_\\ \\ \\ \\L\\ \\ ");
  puts("   \\ \\____/\\ \\____/ ");
  puts("    \\/___/  \\/___/  ");
  puts("");
  printf("Loading database \"%s\"...\n\n", filename);
}


void* construct_database(char *filename) {
  Node list = NULL;
  char key [128];
  char value [128];
  FILE *input_database = fopen(filename, "r");
  while(!(feof(input_database))) {
    readline(key, 128, input_database);
    readline(value, 128, input_database);
    void* newNode = new_node(key, value);
    list = (Node) (insert(&list, newNode));
  }
  return list;
}


void* database_startup(char *filename) {
  Node starting_element_of_database;
  database_print_opening(filename);
  starting_element_of_database = construct_database(filename);
  return starting_element_of_database;
}


void print_choices(void) {
  puts("Please choose an operation");
  puts("1. Query a key");
  puts("2. Update an entry");
  puts("3. New entry");
  puts("4. Remove entry");
  puts("5. Print database");
  puts("0. Exit database");
  printf("? : ");
}


int read_choices(void) {
  int choice = -1;
  scanf("%d", &choice);
  while(getchar() != '\n');
  return choice;
}


void print_result(char* query_str, Node match) {
  if (match != NULL) {
    printf("Found entry:\nKey: %s\tValue: %s\n", match->key, match->value); 
  } else {
    printf("Could not find an entry matching key \"%s\"!\n", query_str);
  }
}


int main(int argc, char *argv[]) {
  char *filename = argv[1];
  if (argc < 2) {
    puts("Usage: db [FILE]");
    return -1;
  }
  
  Node db = database_startup(filename);
  int choice = -1;
  while(choice != 0) {
    Node result = NULL;
    char buffer[128];
    char new_value[128];
    print_choices();
    choice = read_choices();
    switch(choice) {
      
    case 1:
      printf("Enter key: ");
      readline(buffer, 128, stdin);
      puts("Searching database...\n");
      result = (Node) query(db, buffer);
      print_result(buffer, result);
      break;
      
    case 2:
      printf("Enter the name of the element you want to alter: ");
      readline(buffer, 128, stdin);
      puts("Searching database...\n");
      result = (Node) query(db, buffer);
      print_result(buffer, result);
      if (result == NULL) {
	break;
      }
      printf("Enter new value: ");
      readline(new_value, 128, stdin);
      update(result, new_value);
      printf("New value, fresh node update: \nKey: %s\tValue: %s", result->key, result->value);
      result = NULL;
      break;
      
    case 3: 
      printf("Enter new key: ");
      readline(buffer, 128, stdin);
      puts("Searching database...\n");
      result = (Node) query(db, buffer);
      if (result != NULL) {
	printf("%s already exist in the DB\n", result->key);
	break;
      }
      printf("Enter new desired value: ");
      readline(new_value, 128, stdin);
      db = (Node) (insert(&db, new_node(buffer, new_value)));
      printf("New node successfully inserted\nKey: %s\tValue: %s\n", buffer, new_value);
      break;

    case 4:
      printf("Enter key to be deleted: ");
      readline(buffer, 128, stdin);
      puts("Searching database...\n");
      result = (Node) query(db, buffer);
      if (result == NULL) {
	printf("%s can not be deleted as it do not exist in the DB\n", buffer);
	break;
      }
      char* key = result->key;
      char* value = result->value;
      db = delete(&db, result);
      printf("Successfully deleted the following entry:\nkey: %s\nvalue: %s\n", key, value);
      break;
      
    case 5:
      printf("%s\t\t%s\n", "KEY", "VALUE");
      print(db);
      break;
      
    case 0:
      break;
      
    default:
      puts("Could not parse choice! Please try again");
    }
    puts("");
  }
  return 0;
}
