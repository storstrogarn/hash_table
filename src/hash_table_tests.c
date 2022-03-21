#include <string.h>
#include "hash_table.h"
#include <stdbool.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "structs.h"
#include "linked_list.h"
// Define a macro 'BUCKS' for the maximum num. of buckets in 'buckets'.
#define BUCKS 17

#define Success(v)      (ioopm_option_t) { .success = true, .value = v };
#define Failure()       (ioopm_option_t) { .success = false };
#define Successful(o)   (o.success == true)
#define Unsuccessful(o) (o.success == false)

#define _XOPEN_SOURCE 700

#define int_elem(x) (elem_t) { .i=(x) }
#define ptr_elem(x) (elem_t) { .p=(x) }
#define string_elem(x) (elem_t) { .s=(x) }

#define ioopm_int_str_ht_insert(ht, i, s) \
   ioopm_hash_table_insert(ht, int_elem(i), ptr_elem(s)) //Se hit

#define ioopm_int_key_lookup(ht, key) \
	ioopm_hash_table_lookup(ht, int_elem(key))

#define ioopm_int_key_remove(ht, key) \
	ioopm_hash_table_remove(ht, int_elem(key))

#define ioopm_int_key_has_key(ht, key) \
	ioopm_hash_table_has_key(ht, int_elem(key))

#define ioopm_strcomp(value1, value2) \
	strcomp(string_elem(value1), string_elem(value2))


#define ioopm_string_value_has_value(ht, value, eqfun) \
	ioopm_hash_table_has_value(ht, ptr_elem(value), eqfun) //Är pointer elem samma som string_elem???  förmodligen ja! se given rad 19?

#define ioopm_string_lenght_checker(key, value, extra) \
	lenght_checker(int_elem(key), string_elem(value), extra)

#define ioopm_string_modify(key, value, extra) \
	modify_string(int_elem(key), string_elem(value), extra)

#define ioopm_string_is_overload(key, value, extra) \
	is_overload(int_elem(key), string_elem(value), extra)

#define ioopm_int_linked_list_get(list, index) \
	ioopm_linked_list_get(list, int)

#define ioopm_int_linked_list_contains(list, element) \
	ioopm_linked_list_contains(list, int_elem(element))

#define ioopm_string_linked_list_contains(list, element) \
	ioopm_linked_list_contains(list, string_elem(element))

#define ioopm_int_linked_list_insert(list, index, value) \
	ioopm_linked_list_insert(list, index, int_elem(value))

#define ioopm_string_linked_list_insert(list, index, value) \
	ioopm_linked_list_insert(list, index, string_elem(value))

struct hash_table
{
    entry_t *buckets;
    size_t size;
    hashfun_t hash_function;
    size_t bucks;
};



int init_suite(void)
{
    return 0;
}

int clean_suite(void)
{
    return 0;
}

static int hash_key(elem_t key)
{
    return key.i;
}

//A way to hash strings
/*
unsigned long string_knr_hash(const char *str)
{
  unsigned long result = 0;
  do
    {
      result = result * 31 + *str;
    }
  while (*++str != '\0');
  return result;
}
 */


ioopm_hash_table_t *make_a_cool_ht(void)
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_key);
    ioopm_int_str_ht_insert(ht,1,"first value");
    ioopm_int_str_ht_insert(ht,2,"second value");
    ioopm_int_str_ht_insert(ht,3,"third value");
    ioopm_int_str_ht_insert(ht,4,"fourth value");
    ioopm_int_str_ht_insert(ht,5,"fifth value");
    ioopm_int_str_ht_insert(ht,6,"sex");
    ioopm_int_str_ht_insert(ht,7,"sju");
    ioopm_int_str_ht_insert(ht,8,"åtta");
    ioopm_int_str_ht_insert(ht,9,"nio");
    ioopm_int_str_ht_insert(ht,10,"tio");
    ioopm_int_str_ht_insert(ht,11,"elva");
    ioopm_int_str_ht_insert(ht,12,"tolv");
    ioopm_int_str_ht_insert(ht,13,"treton");
    ioopm_int_str_ht_insert(ht,14,"fjorton");
    ioopm_int_str_ht_insert(ht,15,"femton");
    ioopm_int_str_ht_insert(ht,16,"sexton");
    ioopm_int_str_ht_insert(ht,17,"sjuton");
    ioopm_int_str_ht_insert(ht,18,"arton");
    ioopm_int_str_ht_insert(ht,19,"nitton");
    ioopm_int_str_ht_insert(ht,20,"tjugo");
    return(ht);
}




void test_lookup1(void)
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_key);

    // -17 since we enable the possibily for negative keys.
    for (int key = -BUCKS; key < BUCKS; key++)
        {
            CU_ASSERT((ioopm_int_key_lookup(ht,key)).success == false);
        }

    ioopm_hash_table_destroy(ht);
}

// Test with a fresh key
void test_insert1(void)
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_key);
    int key = 1;
    char *value = "tester";
    // Test with a fresh key
    CU_ASSERT((ioopm_int_key_lookup(ht,key)).success == false);
    ioopm_int_str_ht_insert(ht, key, value);
    ioopm_option_t lookup_result = (ioopm_int_key_lookup(ht,key));
    CU_ASSERT(lookup_result.success == true);
    CU_ASSERT(lookup_result.value.s == value);
    ioopm_hash_table_destroy(ht);
}

void test_insert2(void)
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_key);
    int key = 3;
    int key2 = 20;
    char *value = "tester";
    char *value2 = "hsdadadad";
    // Test with a fresh key
    CU_ASSERT((ioopm_int_key_lookup(ht,key)).success == false);
    ioopm_int_str_ht_insert(ht, key, value);
    ioopm_int_str_ht_insert(ht, key2, value2);
    ioopm_option_t lookup_result = (ioopm_int_key_lookup(ht,key));
    CU_ASSERT(lookup_result.success == true);
    CU_ASSERT(lookup_result.value.s == value);
    // Insert a new value at the same key
    ioopm_int_str_ht_insert(ht, key, value2);
    lookup_result = (ioopm_int_key_lookup(ht,key));
    CU_ASSERT(lookup_result.success == true);
    CU_ASSERT(lookup_result.value.s == value2);
    ioopm_hash_table_destroy(ht);
}
void test_insert3(void)
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_key);

    for (int key = -10; key < 50; key++)
        {
            char *value = "tester";
            // Test with a fresh key
            CU_ASSERT((ioopm_int_key_lookup(ht,key)).success == false);
            ioopm_int_str_ht_insert(ht, key, value);
            ioopm_option_t lookup_result = (ioopm_int_key_lookup(ht,key));
            CU_ASSERT(lookup_result.success == true);
            CU_ASSERT(lookup_result.value.s == value);
            // Insert a new value at the same key
            value = "new tester";
            ioopm_int_str_ht_insert(ht, key, value);
            lookup_result = (ioopm_int_key_lookup(ht,key));
            CU_ASSERT(lookup_result.success == true);
            CU_ASSERT(lookup_result.value.s == value);
        }

    ioopm_hash_table_destroy(ht);
}
void test_remove1(void)
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_key);

    for (int key = -10; key < 10; key++)
        {
            char *value = "tester";
            // Test with a fresh key
            CU_ASSERT((ioopm_int_key_lookup(ht,key)).success == false);
            ioopm_int_str_ht_insert(ht, key, value);
            ioopm_option_t lookup_result = (ioopm_int_key_lookup(ht,key));
            CU_ASSERT(lookup_result.success == true);
            CU_ASSERT(lookup_result.value.s == value);
            // Remove the key
            elem_t removed_value = ioopm_int_key_remove(ht,key);
            lookup_result = (ioopm_int_key_lookup(ht,key));
            CU_ASSERT(lookup_result.success == false);
            CU_ASSERT(removed_value.s == value);
        }

    ioopm_hash_table_destroy(ht);
}

void test_remove2(void)
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_key);

    for (int key = 1; key < 200; key++)
        {
            char *value = "tester";
            // Test with a fresh key
            CU_ASSERT((ioopm_int_key_lookup(ht,key)).success == false);
            ioopm_int_str_ht_insert(ht, key, value);
            ioopm_option_t lookup_result = (ioopm_int_key_lookup(ht,key));
            CU_ASSERT(lookup_result.success == true);
            CU_ASSERT(lookup_result.value.s == value);
            // Remove the NON-existing key
            elem_t removed_value = ioopm_int_key_remove(ht,(key+1));
            CU_ASSERT_TRUE(strcmp(removed_value.s, "NO") == 0);
            lookup_result = (ioopm_int_key_lookup(ht,key+1));
            CU_ASSERT(lookup_result.success == false);
        }

    ioopm_hash_table_destroy(ht);
}



void test_size(void)
{
    int i = 1;
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_key);

    for (i = 1; i < 10; i++)
        {
            char *value = "size me!";
            ioopm_int_str_ht_insert(ht,i,value);
        }

    ioopm_int_key_remove(ht,i);
    CU_ASSERT(ioopm_hash_table_size(ht) == (i-1));
    ioopm_hash_table_destroy(ht);
}





void test_emty(void)
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_key);
    CU_ASSERT(ioopm_hash_table_is_empty(ht) == (true))
    ioopm_int_str_ht_insert(ht,3,"emty me!");
    ioopm_int_str_ht_insert(ht,4,"emty me!");
    CU_ASSERT(ioopm_hash_table_is_empty(ht) == (false))
    ioopm_hash_table_destroy(ht);
}



void test_clear(void)
{
    int i = 1;
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_key);

    for (i = 1; i < 10; i++)
        {
            char *value = "clear all of us!";
            ioopm_int_str_ht_insert(ht,i,value);
        }

    CU_ASSERT(ioopm_hash_table_is_empty(ht) == (false));
    ioopm_hash_table_clear(ht);
    CU_ASSERT(ioopm_hash_table_is_empty(ht) == (true));
    ioopm_hash_table_destroy(ht);
}

void test_clear2(void)
{
    int i = 0;
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_key);
    CU_ASSERT(ioopm_hash_table_is_empty(ht));

    for (i = -10; i < 10; i++)
        {
            char *value = "clear all of us!";
            ioopm_int_str_ht_insert(ht,i,value);
        }

    CU_ASSERT(ioopm_hash_table_size(ht) == (20));

    for(int k = -10; k < 10; k++)
        {
            ioopm_hash_table_clear(ht);
            CU_ASSERT(ioopm_hash_table_is_empty(ht) == (true));
            ioopm_int_str_ht_insert(ht, k, "YES");
            CU_ASSERT(ioopm_hash_table_is_empty(ht) == (false));
        }

    ioopm_hash_table_clear(ht);
    ioopm_hash_table_destroy(ht);
}



void test_keys(void)
{
    int i = 0;
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_key);

    for (i = 1; i <= 10; i++)
        {
            char *value = "gimmi duh keys!";
            ioopm_int_str_ht_insert(ht,i,value);
        }

    int expected[]= {1,2,3,4,5,6,7,8,9,10};
    ioopm_list_t *keys = (ioopm_hash_table_keys(ht));

    for (int k = -1; k < ioopm_hash_table_size(ht)-2; k++)
        {
            CU_ASSERT((ioopm_linked_list_get(keys, k).i) == (expected[k]));
        }

    ioopm_linked_list_destroy(keys);
    ioopm_hash_table_destroy(ht);
}




void test_values(void)
{
    int i = 0;
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_key);

    for (i = 1; i <= 10; i++)
        {
            char *value = "Ape";
            ioopm_int_str_ht_insert(ht,i,value);
        }

    char *expected[]= {"Ape","Ape","Ape","Ape","Ape"};
    ioopm_list_t *values = (ioopm_hash_table_values(ht));

    for (int k = 0; k < 5; k++)
        {
            CU_ASSERT((ioopm_linked_list_get(values, k).s) == (expected[k]));
        }

    ioopm_linked_list_destroy(values);
    ioopm_hash_table_destroy(ht);
}



void test_has_key(void)
{
    int i = 0;
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_key);

    for (i = -50; i <= 50; i++)
        {
            char *value = "Ape";
            ioopm_int_str_ht_insert(ht,i,value);
        }

    for (int i = 1; i<=(ioopm_hash_table_size(ht)-51); i++)
        {
            CU_ASSERT_TRUE(ioopm_int_key_has_key(ht,i));
        }

    ioopm_hash_table_destroy(ht);
}




bool strcomp(elem_t value1, elem_t value2)
{
    if(strcmp(value1.s, value2.s)==0)
        {
            return true;
        }
    else
        {
            return false;
        }
}



void test_has_value(void)
{
    ioopm_hash_table_t *ht = make_a_cool_ht();
    CU_ASSERT_TRUE(ioopm_string_value_has_value(ht, "first value",strcomp));
    CU_ASSERT_TRUE(ioopm_string_value_has_value(ht, "third value",strcomp));
    CU_ASSERT_TRUE(ioopm_string_value_has_value(ht, "second value",strcomp));
    CU_ASSERT_FALSE(ioopm_string_value_has_value(ht, "fake value",strcomp));
    ioopm_int_str_ht_insert(ht,29,"new value");
    ioopm_int_str_ht_insert(ht,30,"new value");
    CU_ASSERT_TRUE(ioopm_string_value_has_value(ht, "new value",strcomp));
    ioopm_int_str_ht_insert(ht,31,"H");
    CU_ASSERT_TRUE(ioopm_string_value_has_value(ht, "H",strcomp));
    CU_ASSERT_FALSE(ioopm_string_value_has_value(ht, "h",strcomp));
    ioopm_hash_table_destroy(ht);
}


bool lenght_checker(elem_t key, elem_t value, void *extra)
{
    if (key.i < 10 && strlen(value.s) < 10)
        {
            return true;
        }
    else
        {
            return false;
        }
}

void modify_string(elem_t key, elem_t *value, void *extra)
{
    value->s = "overload";
}



bool is_overload(elem_t key, elem_t value, void *extra)
{
    if(strcmp(value.s, "overload")==0)
        {
            return true;
        }
    else
        {
            return false;
        }
}



void test_any_and_all(void)
{
    // Extracting keys with a negative key causes issues.
    for (int i = -100; i < 5 ; i++)
        {
            ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_key);
            int test = 1;
            int *pekare = &test;
            ioopm_int_str_ht_insert(ht,1+i,"hej");
            ioopm_int_str_ht_insert(ht,2+i,"ape");
            ioopm_int_str_ht_insert(ht,3+i,"dejt");
            ioopm_int_str_ht_insert(ht,4+i,"slate");
            ioopm_int_str_ht_insert(ht,5+i,"great");
            CU_ASSERT_TRUE(ioopm_hash_table_all(ht, (lenght_checker), pekare));
            CU_ASSERT_TRUE(ioopm_hash_table_any(ht, (lenght_checker), pekare));
            ioopm_int_str_ht_insert(ht,11,"slate");
            CU_ASSERT_TRUE(ioopm_hash_table_any(ht, (lenght_checker), pekare));
            ioopm_int_str_ht_insert(ht,4,"slaterwrwrwrwrwrwrwr");
            CU_ASSERT_FALSE(ioopm_hash_table_all(ht, (lenght_checker), pekare));
            ioopm_hash_table_destroy(ht);
        }
}

void test_apply_to_all(void)
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_key);
    int test = 1;
    int *pekare = &test;
    ioopm_int_str_ht_insert(ht,1,"hej");
    ioopm_int_str_ht_insert(ht,2,"ape");
    ioopm_int_str_ht_insert(ht,3,"dejt");
    ioopm_int_str_ht_insert(ht,4,"slate");
    ioopm_int_str_ht_insert(ht,5,"great");
    CU_ASSERT_FALSE(ioopm_hash_table_all(ht, (is_overload), pekare));
    ioopm_hash_table_apply_to_all(ht, (modify_string), pekare);
    CU_ASSERT_TRUE(ioopm_hash_table_all(ht, (is_overload), pekare));
    ioopm_hash_table_destroy(ht);
}




void test_resize(void)
{
    ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_key);
    CU_ASSERT(ht->bucks == 17);

    for (int key = 0; key < 8; key++)
        {
            char *value = "tester";
            // Test with a fresh key
            CU_ASSERT((ioopm_int_key_lookup(ht,key)).success == false);
            ioopm_int_str_ht_insert(ht, key, value);
            ioopm_option_t lookup_result = (ioopm_int_key_lookup(ht,key));
            CU_ASSERT(lookup_result.success == true);
            CU_ASSERT(lookup_result.value.s == value);
            // Insert a new value at the same key
            value = "new tester";
            ioopm_int_str_ht_insert(ht, key, value);
            lookup_result = (ioopm_int_key_lookup(ht,key));
            CU_ASSERT(lookup_result.success == true);
            CU_ASSERT(lookup_result.value.s == value);
            CU_ASSERT(ht->bucks == 17);
        }

    ioopm_int_str_ht_insert(ht, 62, "Klara");
    CU_ASSERT(ht->bucks == 31);
    ioopm_hash_table_destroy(ht);
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
        (NULL == CU_add_test(test_suite1, "test_lookup1", test_lookup1)) 			||
        (NULL == CU_add_test(test_suite1, "test_insert1", test_insert1)) 			||
        (NULL == CU_add_test(test_suite1, "test_insert2", test_insert2)) 			||
        (NULL == CU_add_test(test_suite1, "test_insert3", test_insert3)) 			||
        (NULL == CU_add_test(test_suite1, "test_remove1", test_remove1)) 			||
        (NULL == CU_add_test(test_suite1, "test_remove2", test_remove2)) 			||
        (NULL == CU_add_test(test_suite1, "test_size", test_size)) 		 			||
        (NULL == CU_add_test(test_suite1, "test_emty", test_emty))		 			||
        (NULL == CU_add_test(test_suite1, "test_clear", test_clear))     			||
        (NULL == CU_add_test(test_suite1, "test_clear2", test_clear2))  		    ||
        (NULL == CU_add_test(test_suite1, "test_keys", test_keys)) 				    ||
        (NULL == CU_add_test(test_suite1, "test_values", test_values))  		    ||
        (NULL == CU_add_test(test_suite1, "test_has_key", test_has_key)) 			||
        (NULL == CU_add_test(test_suite1, "test_has_value", test_has_value)) 		  ||
        (NULL == CU_add_test(test_suite1, "test_any_and_all", test_any_and_all)) 	||
        (NULL == CU_add_test(test_suite1, "test_apply_to_all", test_apply_to_all))  ||
        (NULL == CU_add_test(test_suite1, "test_resize", test_resize))
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
