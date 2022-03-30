#include "../src/hash_table.h"
#include "../src/linked_list.h"

#define int_elem(x) (elem_t) { .i=(x) }
#define ptr_elem(x) (elem_t) { .p=(x) }
#define string_elem(x) (elem_t) { .s=(x) }

#define ioopm_int_str_ht_insert(ht, i, s) \
   ioopm_hash_table_insert(ht, int_elem(i), ptr_elem(s)) //Se hit

#define ioopm_str_str_ht_insert(ht, i, s) \
   ioopm_hash_table_insert(ht, ptr_elem(i), ptr_elem(s)) //Se hit

#define ioopm_str_key_lookup(ht, key) \
	ioopm_hash_table_lookup(ht, ptr_elem(key))


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


static int hash_key(elem_t key)
{
    return key.i;
}

static void print_ht_keys(ioopm_hash_table_t *ht)
{
	ioopm_list_t *keys = ioopm_hash_table_keys(ht);

	size_t length = ioopm_linked_list_size(keys);

	printf("Printing keys!\n");
	printf("--------------\n");
	for(int i = 0; i < length; i++)
		{
			elem_t current = ioopm_linked_list_get(keys,i);
			char* now = current.p;
			printf("%d: %s\n",(i+1), now);
		}
	printf("--------------\n");
	ioopm_linked_list_destroy(keys);
}

static void print_ht_values(ioopm_hash_table_t *ht)
{
	ioopm_list_t *values = ioopm_hash_table_values(ht);

	size_t length = ioopm_linked_list_size(values);

	printf("Printing values!\n");
	printf("--------------\n");
	for(int i = 0; i < length; i++)
		{
			elem_t current = ioopm_linked_list_get(values,i);
			char* now = current.p;
			printf("%d: %s\n",(i+1), now);
		}
	printf("--------------\n");
	ioopm_linked_list_destroy(values);
}


int main()
{
	ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_key);

	printf("Inserting entries into hash table!\n");
	printf("------------------------------------\n");
	
	printf("Inserting cool as key and dog as its value into ht!\n");
	ioopm_hash_table_insert(ht, ptr_elem("cool"), ptr_elem("dog"));
	if(ioopm_str_key_lookup(ht, "cool").success)
		{
			printf("Success!\n");
		}

	printf("Inserting Doctor as key and Who as its value into ht!\n");
	ioopm_str_str_ht_insert(ht, "Doctor", "Who");
	if(ioopm_str_key_lookup(ht, "Doctor").success)
		{
			printf("Success!\n");
		}

	printf("Inserting mips as key and DARK as its value into ht!\n");
	ioopm_str_str_ht_insert(ht, "mips", "DARK");
	if(ioopm_str_key_lookup(ht, "mips").success)
		{
			printf("Success!\n");
		}

	printf("Inserting 10 as key and Ten as its value into ht!\n");
	ioopm_str_str_ht_insert(ht, "10", "Ten");
	if(ioopm_str_key_lookup(ht, "10").success)
		{
			printf("Success!\n");
		}

	print_ht_keys(ht);
	print_ht_values(ht);
	
	ioopm_hash_table_destroy(ht);
}
