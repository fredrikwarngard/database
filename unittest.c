#include <string.h>
#include <CUnit/Basic.h>
#include "db_main.h"
#include "db_main_list.h"
#include "list_module.h"
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

int init_suite_2(void)
{
  return 0;
}

int clean_suite_2(void)
{
  return 0;
}

//make node
void test_NEW_NODE() {
  char* x = "Hello, world!";
  void* y = (int) 237;
  Node hello = new_node(x, y);
  CU_ASSERT(strcmp(x, *(hello->key)) == 0);
  CU_ASSERT(y == *(hello->value));
}


//make a node with the previous node as the element to the second node
void test_NEWNODE2() {
  char* x = "Hello, world!";
  void* y = (int)237;
  Node hello = new_node(x, y);
  Node noob  = new_node("Noob", hello);
  CU_ASSERT(strcmp("Noob", *(noob->key)) == 0);
  CU_ASSERT(strcmp("noob", *(noob->key)) != 0);
  CU_ASSERT(noob->value == hello);
}


//return the node with the fitting key from a structure, if it contains the node. In the second case the node with the "Hello, world!" keyword is stored as an element, not in the linked list. Therefor it won't be checked.
void testRETURN_ELEMENT(void) {
  char* x = "Hello, world!";
  void* y = (int)237;
  Node hello = new_node(x, y);
  Node noob  = new_node("Noob", hello);
  CU_ASSERT(return_element(noob, "Noob") != NULL);
  CU_ASSERT(return_element(noob, "Hello, world!") == NULL);
}


//basically just a call on the function above. SAME TEST!
void testQUERY(void) {
  char* x = "Hello, world!";
  void* y = (int)237;
  Node hello = new_node(x, y);
  Node noob  = new_node("Noob", hello);
  CU_ASSERT(return_element(noob, "Noob") != NULL);
  CU_ASSERT(return_element(noob, "Hello, world!") == NULL);
}

//change the value in a node. first example tries to put in a node that already contains the node it is about to be inserted in. node noob->(value)node hello->(value)node noob
void testUPDATE(void) {
  char* x = "Hello, world!";
  void* y = (int)237;
  Node hello = new_node(x, y);
  Node noob  = new_node("Noob", hello);
  update(hello, noob);    // borde inte funka att stoppa in dem i varandras values
  CU_ASSERT((int)*(hello->value) != 237);
  update(hello, "Santa Maria");
  CU_ASSERT(strcmp("Santa Maria", *(hello->value)) == 0);
}

//checks if second argument has a like in name among the nodes in the list. return that node if that's the case. returns NULL otherwise
void testGET_INSERTION_SPOT() {
  char* x = "Hello, world!";
  void* y = (int)237;
  Node hello = new_node(x, y);
  char* a = "Goodbye, cruel world";
  void* b = "ingenting";
  Node byebye = new_node(a, b);
  hello->next = byebye;
  CU_ASSERT(get_insertion_spot(hello, "Goodbye, cruel world!") != NULL);
  CU_ASSERT(get_insertion_spot(byebye, "Goodbye, cruel world!") != NULL);
}

//insert a new node into the structure at the right spot given by the function above
void testINSERT(void) {
  char* x = "Hello, world!";
  void* y = (int)237;
  Node hello = new_node(x, y);
  char* a = "Goodbye, cruel world";
  void* b = "ingenting";
  Node byebye = new_node(a, b);
  char* new_x = "Grim";
  void* new_y = "Node to be inputted";
  Node new_guy = new_node(new_x, new_y);
  insert(&hello, byebye);  
  CU_ASSERT(hello->next == byebye);
  insert(&hello, new_guy);  
  CU_ASSERT(hello->next->next == new_guy);
}


//basically returns the parent node instead of using a parent pointer. test case finds the parent node to the second node in a list of two, which is the pointer to the database. second test case insert another node and find its parent.
void testFIND_PREVIOUS_NODE(void) {
  char* x = "Hello, world!";
  void* y = (int)237;
  Node hello = new_node(x, y);
  char* a = "Goodbye, cruel world";
  void* b = "ingenting";
  Node byebye = new_node(a, b);
  char* new_x = "Grim";
  void* new_y = "Node to be inputted";
  Node new_guy = new_node(new_x, new_y);
  insert(&hello, byebye);
  CU_ASSERT(find_previous_node(hello, byebye) == hello);
  insert(&hello, new_guy);
  CU_ASSERT(find_previous_node(hello, new_guy) == byebye);
}


//first ASSERT delete controls that the first node in the list has been replaced by the second node 
void testDELETE(void) {
  char* x = "Hello, world!";
  void* y = (int)237;
  Node hello = new_node(x, y);
  char* a = "Goodbye, cruel world";
  void* b = "ingenting";
  Node byebye = new_node(a, b);
  insert(&hello, byebye);
  CU_ASSERT(delete(&hello, hello)   == byebye);
  CU_ASSERT(delete(&byebye, byebye) == NULL);)
}


//not sure i should have a test_PRINT????





 -------------============== PREVIOUS CODE STUFF ================-------------




  /*  char *str1 = istring_mk(NULL);
  CU_ASSERT(str1 == NULL);
  char str2[] = "foo";
  char *str3 = istring_mk(str2);
  CU_ASSERT(strlen(str3) == strlen(str2));
  CU_ASSERT(strcmp(str2, str3)  == 0);
  CU_ASSERT(str3[0]  == 'f');
  CU_ASSERT(str3[1]  == 'o');
  CU_ASSERT(str3[2]  == 'o');
  CU_ASSERT(str3[3]  == '\0');
  str3[0]  = 'F';
  CU_ASSERT(strcmp(str2, str3) > 0);
  istring_rm(str1);
  istring_rm(str3);*/


void testISTRING_RM(void)
{
  istring_rm(istring_mk("test"));
}

void testISTRLEN(void)
{
  char *str1 = istring_mk("spam");
  char *str2 = istring_mk("ekieki");
  CU_ASSERT(istrlen(str1) == 4);
  CU_ASSERT(istrlen(str2) == 6);
  START(str2)->length = 3;
  CU_ASSERT(istrlen(str2) == 3);
  CU_ASSERT(strlen(str2) == 6);
  istring_rm(str1);
  istring_rm(str2);
}

void testISTRING_TO_STRING(void)
{
  char *str1 = istring_mk("spam");
  char *str2 = NULL;
  str2 = istring_to_string(str1);
  CU_ASSERT(strcmp(str2, "spam") == 0);
  istring_rm(str1);
  if (str2 != NULL) free(str2);
}


void testISTRCAT(void)
{
  // You must implement you own!
  CU_FAIL("Test not implemented yet");
}

void testISTRNCAT(void)
{
  // You must implement you own!
  CU_FAIL("Test not implemented yet");
}

void testISTRCHR(void)
{
  char *str = istring_mk("spam spam bacon spam");
  CU_ASSERT(istrchr(str, 's') == str);
  CU_ASSERT(istrchr(str, 'b') == str + 10);
  CU_ASSERT(istrchr(str, 'c') == str + 12);
  CU_ASSERT(istrchr(str, 's') == str);
  CU_ASSERT(istrchr(str, '\0') == str + 20);
  CU_ASSERT(istrchr(str, 'x') == NULL);
  istring_rm(str);
}

void testISTRRCHR(void)
{
  char *str = istring_mk("spam spam bacon spam");
  CU_ASSERT(istrrchr(str, 's') == str + 16);
  CU_ASSERT(istrrchr(str, 'b') == str + 10);
  CU_ASSERT(istrrchr(str, 'c') == str + 12);
  CU_ASSERT(istrrchr(str, 's') == str + 16);
  CU_ASSERT(istrrchr(str, '\0') == str + 20);
  CU_ASSERT(istrrchr(str, 'x') == NULL);
  istring_rm(str);
}

void testISTRCMP(void)
{
  char *str1 = istring_mk("spam");
  char *str2 = istring_mk("spam");
  char *str3 = istring_mk("Spam");
  CU_ASSERT(istrcmp(str1, str1) == 0);
  CU_ASSERT(istrcmp(str1, str2) == 0);
  CU_ASSERT(istrcmp(str2, str3) > 0);
  CU_ASSERT(istrcmp(str3, str2) < 0);
  istring_rm(str1);
  istring_rm(str2);
  istring_rm(str3);
}

void testISTRNCMP(void)
{
  char *str1 = istring_mk("spam ");
  char *str2 = istring_mk("spam");
  char *str3 = istring_mk("Spam");
  CU_ASSERT(istrncmp(str1, str2, 4) == 0);
  CU_ASSERT(istrncmp(str1, str2, 5) > 0);
  CU_ASSERT(istrncmp(str2, str3, 4) > 0);
  CU_ASSERT(istrncmp(str3, str2, 4) < 0);
  istring_rm(str1);
  istring_rm(str2);
  istring_rm(str3);
}

void testISTRCPY(void)
{
  // You must implement your own!
  CU_FAIL("Test not implemented yet");
}

void testISTRNCPY(void)
{
  // You must implement your own!
  CU_FAIL("Test not implemented yet");
}

int main()
{
  CU_pSuite pSuite1 = NULL;
  CU_pSuite pSuite2 = NULL;

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
  pSuite2 = CU_add_suite("Advanced Functions Suite", init_suite_2, clean_suite_2);
  if (NULL == pSuite2)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  /* add the tests to the suites */
  if (
    (NULL == CU_add_test(pSuite1, "test of istring_mk()", testISTRING_MK)) ||
    (NULL == CU_add_test(pSuite1, "test of istring_rm()", testISTRING_RM)) ||
    (NULL == CU_add_test(pSuite1, "test of istring_to_string()", testISTRING_TO_STRING)) ||
    (NULL == CU_add_test(pSuite1, "test of istrlen()", testISTRLEN))
  )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if (
    (NULL == CU_add_test(pSuite2, "test of istrcat()", testISTRCAT)) ||
    (NULL == CU_add_test(pSuite2, "test of istrncat()", testISTRNCAT)) ||
    (NULL == CU_add_test(pSuite2, "test of istrchr()", testISTRCHR)) ||
    (NULL == CU_add_test(pSuite2, "test of istrrchr()", testISTRRCHR)) ||
    (NULL == CU_add_test(pSuite2, "test of istrcmp()", testISTRCMP)) ||
    (NULL == CU_add_test(pSuite2, "test of istrncmp()", testISTRNCMP)) ||
    (NULL == CU_add_test(pSuite2, "test of istrcpy()", testISTRCPY)) ||
    (NULL == CU_add_test(pSuite2, "test of istrncpy()", testISTRNCPY))
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
