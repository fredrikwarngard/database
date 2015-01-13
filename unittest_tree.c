#include <string.h>
#include <CUnit/Basic.h>
//#include "db_main.h"
//#include "db_main_list.h"
//#include "list_module.h" 
#include "tree_module.h"
#include <stdlib.h>

int init_suite_1(void)
{
  return 0;
}

int clean_suite_1(void)
{
  return 0;
}


//make node
void testNEW_NODE() {
  char* x = "Hello, world!";
  void* y = "237";
  Node hello = new_node(x, y);
  CU_ASSERT(strcmp(x, (hello->key)) == 0);
  CU_ASSERT(strcmp(y, ((char*)hello->value)) == 0);
}


//make a node with the previous node as the element to the second node. The last assert compare that the pointers on the key element are the same, which they should be since they are the same.
void testNEW_NODE2() {
  char* x = "Hello, world!";
  void* y = "237";
  Node hello = new_node(x, y);
  Node noob  = new_node("Noob", hello);
  CU_ASSERT(strcmp("Noob", (noob->key)) == 0);
  CU_ASSERT(strcmp("noob", (noob->key)) != 0);
  CU_ASSERT((((Node)(noob->value))->key) == (hello->key));
}


//return the node with the fitting key from a structure, if it contains the node. In the second case the node with the "Hello, world!" keyword is stored as an element, not in the linked list. Therefor it won't be checked.
void testRETURN_ELEMENT(void) {
  char* x = "Hello, world!";
  void* y = "237";
  Node hello = new_node(x, y);
  Node noob  = new_node("Noob", hello);
  CU_ASSERT(return_element(noob, "Noob") != NULL);
  CU_ASSERT(return_element(noob, "Hello, world!") == NULL);
}


//basically just a call on the function above. SAME TEST!
void testQUERY(void) {
  char* x = "Hello, world!";
  void* y = "237";
  Node hello = new_node(x, y);
  Node noob  = new_node("Noob", hello);
  CU_ASSERT(return_element(noob, "Noob") != NULL);
  CU_ASSERT(return_element(noob, "Hello, world!") == NULL);
}

//change the value in a node. first example tries to put in a node that already contains the node it is about to be inserted in. node noob->(value)node hello->(value)node noob
void testUPDATE(void) {
  char* x = "Hello, world!";
  void* y = "237";
  Node hello = new_node(x, y);
  Node noob  = new_node("Noob", hello);
  update(hello, noob);    // borde inte funka att stoppa in dem i varandras values
  CU_ASSERT((atoi(hello->value)) != 237);
  update(hello, "Santa Maria");
  CU_ASSERT(strcmp("Santa Maria", (hello->value)) == 0);
}


//
void testPUT_NODE_IN_TREE(void) {
  char* x = "Hello, world!";
  void* y = "237";
  Node hello = new_node(x, y);
  char* a = "Goodbye, cruel world";
  void* b = "ingenting";
  Node byebye = new_node(a, b);
  put_node_in_tree(hello, byebye);
  CU_ASSERT((hello->leftChild) == byebye);
  CU_ASSERT(((Node)byebye->parent) == hello);
  
}


//insert a new node into the structure at the right spot given by the function above
void testINSERT(void) {
  char* x = "Hello, world!";
  void* y = "237";
  Node hello = new_node(x, y);
  char* a = "Goodbye, cruel world";
  void* b = "ingenting";
  Node byebye = new_node(a, b);
  char* new_x = "Grim";
  void* new_y = "Node to be inputted";
  Node new_guy = new_node(new_x, new_y);
  insert(NULL, hello);
  insert(&hello, byebye);  
  CU_ASSERT(hello->leftChild == byebye);
  insert(&hello, new_guy);  
  CU_ASSERT(hello->leftChild->rightChild == new_guy);
}


void testMAXIMUM() {
  char* x = "Hello, world!";
  void* y = "237";
  Node hello = new_node(x, y);
  char* a = "Goodbye, cruel world";
  void* b = "ingenting";
  Node byebye = new_node(a, b);
  char* new_x = "Grim";
  void* new_y = "Node to be inputted";
  Node new_guy = new_node(new_x, new_y);
  insert(NULL, new_guy);
  insert(&new_guy, hello);
  insert(&new_guy, byebye);
  CU_ASSERT(maximum(new_guy) == hello);
}



//first ASSERT delete controls that the first node in the list has been replaced by the second node 
void testDELETE(void) {
  char* x = "Hello, world!";
  void* y = "237";
  Node hello = new_node(x, y);
  char* a = "Goodbye, cruel world";
  void* b = "ingenting";
  Node byebye = new_node(a, b);
  insert(&hello, byebye);
  CU_ASSERT(delete(&hello, hello)   == byebye);
  CU_ASSERT(delete(&byebye, byebye) == NULL);
}

int main()
{
  CU_pSuite pSuite1 = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suites to the registry */
  pSuite1 = CU_add_suite("Basic Functions Suite", init_suite_1, clean_suite_1);
  if (NULL == pSuite1)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }


  /* add the tests to the suites */
  if (
    (NULL == CU_add_test(pSuite1, "test of new_node(char*, void*)", testNEW_NODE)) ||
    (NULL == CU_add_test(pSuite1, "test of new_node(char*, void*)", testNEW_NODE2)) ||
    (NULL == CU_add_test(pSuite1, "test of return_element(Node, char*)", testRETURN_ELEMENT)) ||
    (NULL == CU_add_test(pSuite1, "test of query(Node, char*)", testQUERY)) ||
    (NULL == CU_add_test(pSuite1, "test of update(Node, void*)", testUPDATE)) ||
    (NULL == CU_add_test(pSuite1, "test of put_node_in_tree(Node, Node)", testPUT_NODE_IN_TREE)) ||
    (NULL == CU_add_test(pSuite1, "test of insert(Node*, Node)", testINSERT)) ||
    (NULL == CU_add_test(pSuite1, "test of maximum(Node, Node)", testMAXIMUM)) ||
    (NULL == CU_add_test(pSuite1, "test of delete(Node*, Node)", testDELETE))
  )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }


  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
