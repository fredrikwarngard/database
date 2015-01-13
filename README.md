# database
db with list- and tree structure

Create the program

Compile program with make db_list for creating the db_list, or make db_tree to create the db_tree respectively. You can also type make, or make all to create both programs at once. The db_list and db_tree works the same, but it's data structures are different. db_lists' database is represented as a list, whereas db_trees' database is implemented as a tree. All their key funtions are called the same, and although the are implemented differently, the call from either of the structures from the main method will extract the same result.

Run the program

After compiling, you can type either db_list, or db_tree, followed with the path to a database as an argument. If your database is called, say "database.db" and is located in the same folder as your program file, you simply just type ./db_list ./database.db to start the program with the database "database.db" as its input (if you want to implement the database as a list structure). The file with the input has two demends, however. The first one is that every odd line [1, 3, 5, ...] must be readable as a string (char*). This is because this is the key for the node that will be created. This string will be the searching term for the node in the database later, and with it we can find the element we want to store in the node. The elemented is declared on the next line (i.e. every even line [2, 4, 6, ...]). As a result of that, the second demand for the input file is that it has an even number of lines. Otherwise we won't be able to create complete nodes althrough the database.
