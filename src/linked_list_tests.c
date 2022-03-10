#include <string.h>
#include "linked_list.h"
#include <stdbool.h>
#include <stdlib.h>
#include <CUnit/Basic.h>

#include <ctype.h>
#include <stdio.h>
#include <time.h>

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



void test_prepend(void)
{
  ioopm_list_t *ls = ioopm_linked_list_create(intcomp);
  CU_ASSERT(ioopm_linked_list_is_empty(ls) == true);
  ioopm_linked_list_prepend_int(ls, 6);
  CU_ASSERT(ioopm_linked_list_is_empty(ls) == false);
  ioopm_linked_list_prepend_int(ls, 9);
  CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 2);
  ioopm_linked_list_prepend_int(ls, 34);
  CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 3);
  ioopm_linked_list_prepend_int(ls, 63);
  CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 4);
  ioopm_linked_list_prepend_int(ls, 65);
  CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 5);
  elem_t head_value = (ls->head->value);
  CU_ASSERT(head_value.i == 65);
  elem_t snd_value = (ls->head->next->value);
  CU_ASSERT(snd_value.i == 63);
  elem_t thd_value = (ls->head->next->next->value);
  CU_ASSERT(thd_value.i == 34);
  elem_t last_value = (ls->last->value);
  CU_ASSERT(last_value.i == 6);  
  ioopm_linked_list_destroy(ls);


	
}

void test_append(void)
{
  ioopm_list_t *ls = ioopm_linked_list_create(intcomp);
  CU_ASSERT(ioopm_linked_list_is_empty(ls) == true);
  ioopm_linked_list_append_int(ls, 6);
  CU_ASSERT(ioopm_linked_list_is_empty(ls) == false);
  ioopm_linked_list_append_int(ls, 9);
  CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 2);
  ioopm_linked_list_append_int(ls, 34);
  CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 3);
  ioopm_linked_list_append_int(ls, 63);
  CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 4);
  ioopm_linked_list_append_int(ls, 65);
  CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 5);
  elem_t last_value = (ls->last->value);
  CU_ASSERT(last_value.i == 65);

  CU_ASSERT(ls->head->value.i == 6);
  CU_ASSERT(ls->head->next->value.i == 9);
  CU_ASSERT(ls->head->next->next->value.i == 34);
  CU_ASSERT(ls->head->next->next->next->value.i == 63);
  CU_ASSERT(ls->head->next->next->next->next->value.i == ls->last->value.i);


  
  ioopm_linked_list_destroy(ls);

}


void test_insert(void)
{
	for (int i = 0; i < 1; i++)
		{
			ioopm_list_t *ls = ioopm_linked_list_create(intcomp);
			CU_ASSERT(ioopm_linked_list_is_empty(ls) == true);
			// Insert values with valid index and assert that the size increases.
			ioopm_int_linked_list_insert(ls, 0+i,6);
			CU_ASSERT(ioopm_linked_list_is_empty(ls) == false);
			ioopm_int_linked_list_insert(ls, 1+i,9);
			CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 2);
			ioopm_int_linked_list_insert(ls, 1+i,34);
			CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 3);
			ioopm_int_linked_list_insert(ls, 2+i,63);
			CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 4);
			ioopm_int_linked_list_insert(ls, 4+i,65);
			CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 5);

			// Head's value should be 6; the first insert
			CU_ASSERT(ls->head->value.i == 6);
			CU_ASSERT(ls->head->next->value.i == 34);
			CU_ASSERT(ls->head->next->next->value.i == 63);
			// Last's value should be 65; the last insert
			CU_ASSERT(ls->last->value.i == 65);
			ioopm_linked_list_destroy(ls);
		}

}



void test_clear(void)
{
  ioopm_list_t *ls = ioopm_linked_list_create(intcomp);
  CU_ASSERT(ioopm_linked_list_is_empty(ls) == true);
  ioopm_linked_list_append_int(ls, 6);
  CU_ASSERT(ioopm_linked_list_is_empty(ls) == false);
  ioopm_linked_list_append_int(ls, 9);
  CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 2);
  ioopm_linked_list_append_int(ls, 34);
  CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 3);
  ioopm_linked_list_append_int(ls, 63);
  CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 4);
  ioopm_linked_list_append_int(ls, 65);
  CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 5);
  ioopm_linked_list_clear(ls);
  CU_ASSERT(ioopm_linked_list_is_empty(ls) == true);
  ioopm_linked_list_append_int(ls, 6);
  CU_ASSERT(ioopm_linked_list_is_empty(ls) == false);
  ioopm_linked_list_append_int(ls, 3);
  CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 2);
  ioopm_linked_list_append_int(ls, 43);
  CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 3);
  ioopm_linked_list_append_int(ls, 42);
  CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 4);
  ioopm_linked_list_append_int(ls, 632);
  CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 5);
  ioopm_linked_list_clear(ls);
  CU_ASSERT(ioopm_linked_list_is_empty(ls) == true); 
  ioopm_linked_list_destroy(ls);
}

bool int_checker(elem_t value, void *extra)
{
  if (10 > value.i)
  {
    return true;
  }
  else
  { 
    return false;
  }
}

void test_all(void)
{
	int test = 1;	
	int *pekare = &test;
	ioopm_list_t *ls = ioopm_linked_list_create(intcomp);
	CU_ASSERT(ioopm_linked_list_is_empty(ls) == true);
	ioopm_linked_list_append_int(ls, 6);
	CU_ASSERT(ioopm_linked_list_is_empty(ls) == false);
	ioopm_linked_list_append_int(ls, 9);
	CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 2);
	CU_ASSERT_TRUE(ioopm_linked_list_all(ls, int_checker, pekare));
	ioopm_linked_list_append_int(ls, 34);
	CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 3);
	ioopm_linked_list_append_int(ls, 63);
	CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 4);
	ioopm_linked_list_append_int(ls, 65);
	CU_ASSERT_FALSE(ioopm_linked_list_all(ls, int_checker, pekare));
	CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 5);
	ioopm_linked_list_destroy(ls);
}


void test_any(void)
{
	int test = 1;	
	int *pekare = &test;
	ioopm_list_t *ls = ioopm_linked_list_create(intcomp);
	CU_ASSERT(ioopm_linked_list_is_empty(ls) == true);
	ioopm_linked_list_append_int(ls, 6);
	CU_ASSERT(ioopm_linked_list_is_empty(ls) == false);
	ioopm_linked_list_append_int(ls, 9);
	CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 2);
	CU_ASSERT_TRUE(ioopm_linked_list_all(ls, int_checker, pekare));
	CU_ASSERT_TRUE(ioopm_linked_list_any(ls, int_checker, pekare));
	ioopm_linked_list_append_int(ls, 34);
	CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 3);
	ioopm_linked_list_append_int(ls, 63);
	CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 4);
	ioopm_linked_list_append_int(ls, 65);
	CU_ASSERT_FALSE(ioopm_linked_list_all(ls, int_checker, pekare));
	CU_ASSERT_TRUE(ioopm_linked_list_any(ls, int_checker, pekare));
	CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 5);
	ioopm_linked_list_destroy(ls);
}


void increase_value (int *value, void *extra)
{
	*value=*value+10;
	*(int*)extra = *(int*)extra+*value;
}

/* 
void test_apply_to_all(void)
{
	int test = 0;	
	int *pekare = &test;
	int sum = 0;
	ioopm_list_t *ls = ioopm_linked_list_create();
	CU_ASSERT(ioopm_linked_list_is_empty(ls) == true);
	ioopm_linked_list_append_int(ls, 6);
	sum+=6;
	CU_ASSERT(ioopm_linked_list_is_empty(ls) == false);
	ioopm_linked_list_append_int(ls, 9);
	sum+=9;
	CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 2);
	CU_ASSERT_TRUE(ioopm_linked_list_all(ls, int_checker, pekare));
	CU_ASSERT_TRUE(ioopm_linked_list_any(ls, int_checker, pekare));
	ioopm_linked_list_append_int(ls, 34);
	sum+=34;
	CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 3);
	ioopm_linked_list_append_int(ls, 63);
	sum+=63;
	CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 4);
	ioopm_linked_list_append_int(ls, 65);
	sum+=65;
	CU_ASSERT_FALSE(ioopm_linked_list_all(ls, int_checker, pekare));
	CU_ASSERT_TRUE(ioopm_linked_list_any(ls, int_checker, pekare));
	CU_ASSERT_TRUE(ioopm_linked_list_size(ls) == 5);

	
	CU_ASSERT(ls->last->value = 65);
	int *amount = &test;
	ioopm_linked_apply_to_all(ls,increase_value,amount);
	CU_ASSERT(*amount == (sum+50));
	sum+=50;
	int average = *amount / ioopm_linked_list_size(ls);
	CU_ASSERT(average == 45);
	CU_ASSERT(ls->last->value = 75);
	ioopm_linked_apply_to_all(ls,increase_value,amount);
	CU_ASSERT(ls->last->value = 85);

	
	ioopm_linked_list_destroy(ls);
} 
*/

int main()
{
  CU_pSuite test_suite1 = NULL;

  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  test_suite1 = CU_add_suite("Linked list tests", init_suite, clean_suite);
  if (NULL == test_suite1)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }
    
  if (  
	  // (NULL == CU_add_test(test_suite1, "test_lookup1", test_lookup1)) 			||
	  (NULL == CU_add_test(test_suite1, "test_prepend", test_prepend))          ||
	  (NULL == CU_add_test(test_suite1, "test_append", test_append))            || 
	  (NULL == CU_add_test(test_suite1, "test_insert", test_insert))            ||
	  (NULL == CU_add_test(test_suite1, "test_clear", test_clear))              ||
	  (NULL == CU_add_test(test_suite1, "test_all", test_all))                  ||
	  (NULL == CU_add_test(test_suite1, "test_any", test_any))                /*   ||
																				   (NULL == CU_add_test(test_suite1, "test_apply_to_all", test_apply_to_all)) */ 
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
