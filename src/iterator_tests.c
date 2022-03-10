#include <string.h>
#include "iterator.h"
#include "structs.h"
#include "linked_list.h"
#include <stdbool.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <ctype.h>
#include <stdio.h>
#include <time.h>
#include "linked_list.h"
  
#define int_elem(x) (elem_t) { .i=(x) }
#define ptr_elem(x) (elem_t) { .p=(x) }
#define string_elem(x) (elem_t) { .s=(x) } 

#define ioopm_linked_list_prepend_int(list, value) \
  ioopm_linked_list_prepend(list, int_elem(value))

#define ioopm_linked_list_append_int(list, value) \
  ioopm_linked_list_append(list, int_elem(value))

#define ioopm_int_linked_list_insert(list, index, value) \
	ioopm_linked_list_insert(list, index, int_elem(value))

#define ioopm_string_linked_list_insert(list, index, value) \
	ioopm_linked_list_insert(list, index, string_elem(value))

#define ioopm_int_checker(value, extra) \
  int_checker(int_elem(value), extra)

typedef struct iter ioopm_list_iterator_t;
typedef struct list ioopm_list_t; 



bool intcomp(elem_t value1, elem_t value2)
{	
	if(value1.i == value2.i)
		{
			return true;
		}
	else
		{
			return false;
		}
}


int init_suite(void)
{
  return 0;
}

int clean_suite(void)
{
  return 0;
}


void test_iter_current_and_next_and_has_next(void)
{
  ioopm_list_t *ls = ioopm_linked_list_create(intcomp);
  ioopm_int_linked_list_insert(ls, 0,0);
  ioopm_int_linked_list_insert(ls, 1,5);
  ioopm_int_linked_list_insert(ls, 2,100);
  ioopm_int_linked_list_insert(ls, 3,3);
  ioopm_int_linked_list_insert(ls, 4,666);
  ioopm_int_linked_list_insert(ls, 5,123);
  ioopm_int_linked_list_insert(ls, 6,312);
  ioopm_int_linked_list_insert(ls, 7,1241);
  ioopm_int_linked_list_insert(ls, 8,8131);
  ioopm_list_iterator_t *iterator = ioopm_list_iterator(ls);
  CU_ASSERT(ioopm_iterator_current(iterator).i==(0));
  ioopm_iterator_next(iterator);
  CU_ASSERT(ioopm_iterator_current(iterator).i==(5));
  ioopm_iterator_next(iterator);
  CU_ASSERT(ioopm_iterator_current(iterator).i==(100));
  ioopm_iterator_next(iterator);
  ioopm_iterator_next(iterator);
  CU_ASSERT(ioopm_iterator_current(iterator).i==(666));
  ioopm_iterator_next(iterator);
  ioopm_iterator_next(iterator);
  ioopm_iterator_next(iterator);
  CU_ASSERT(ioopm_iterator_has_next(iterator) == (true));
  ioopm_iterator_next(iterator);
  CU_ASSERT(ioopm_iterator_has_next(iterator) == (false));
  ioopm_iterator_reset(iterator);
  ioopm_iterator_destroy(iterator);
  ioopm_linked_list_destroy(ls);

}



void test_iter(void)
{
ioopm_list_t *ls = ioopm_linked_list_create(intcomp);
 for (int i = 0; i < 15; i++)
	 {
		 int value = i + 5;
		 ioopm_int_linked_list_insert(ls, i, value);
	 }

 ioopm_list_iterator_t *iterator = ioopm_list_iterator(ls);
 CU_ASSERT_TRUE(ioopm_iterator_has_next(iterator));
 ioopm_iterator_next(iterator);
 CU_ASSERT_TRUE(ioopm_iterator_has_next(iterator));
 ioopm_iterator_reset(iterator);
 for (int k = 0; k < 15; k++)
	 {
		 int num = k+5;
		 CU_ASSERT(ioopm_iterator_current(iterator).i == (num));
		 ioopm_iterator_next(iterator);
	 }
CU_ASSERT_FALSE(ioopm_iterator_has_next(iterator));

ioopm_iterator_destroy(iterator);
ioopm_linked_list_destroy(ls);
}




int main()
{
  CU_pSuite test_suite1 = NULL;

  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  test_suite1 = CU_add_suite("Test Suite 1", init_suite, clean_suite);
  if (NULL == test_suite1)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }
    
  if (  
   // (NULL == CU_add_test(test_suite1, "test_lookup1", test_lookup1)) 			                          ||
  (NULL == CU_add_test(test_suite1, "test_iter", test_iter))                         ||
   (NULL == CU_add_test(test_suite1, "test_iter_current_and_next_and_has_next", test_iter_current_and_next_and_has_next))
  	)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
