#ifndef new_module
#define new_module

//typedef struct database *Node;

void readline(char*, int, FILE*);
void database_print_opening(char* filename);
void construct_database(char* filename);
void database_startup(char* filename);
void print_choices(void);
int read_choices(void);
void print_result(char*, Node);
int main(int argc, char* argv);

#endif
