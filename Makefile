all : db_list db_tree

.SILENT:
db_tree : db_main.o tree_module.o
	gcc -g db_main.o tree_module.o -o db_tree
	echo db_tree kompilerad och färdiglänkad
db_main.o : db_main.c tree_module.h
	gcc -c -g -Wall -ggdb -std=c99 db_main.c
tree_module.o : tree_module.c db_main.h
	gcc -c -g -Wall -ggdb -std=c99 tree_module.c
db_list : db_main.o list_module.o
	@gcc -g -Dlistan db_main.o list_module.o -o db_list
	echo db_list kompilerad och färdiglänkad
list_module.o : list_module.c db_main.h
	@gcc -c -g -Wall -ggdb -std=c99 list_module.c
clean : 
	rm *.o
	rm db_list
	rm db_tree
