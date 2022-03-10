#include "hash_table.h"
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linked_list.h"
#include "structs.h"
#include <assert.h>
#include <float.h>

// Define a macro 'BUCKS' for the maximum num. of buckets in 'buckets'.
#define BUCKS 17
#define LF 0.5
#define Success(v)      (ioopm_option_t) { .success = true, .value = v};
#define Failure()       (ioopm_option_t) { .success = false };
#define Successful(o)   (o.success == true)
#define Unsuccessful(o) (o.success == false)

#define int_elem(x) (elem_t) { .i=(x) }
#define ptr_elem(x) (elem_t) { .p=(x) }
#define string_elem(x) (elem_t) { .s=(x) } 

struct entry
{
  elem_t key;       // holds the key
  elem_t value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t *buckets;
  size_t size;
  hashfun_t hash_function;
  size_t bucks;
};


static bool bucket_limit(ioopm_hash_table_t *ht)
{
	float size = ht->size;
	float buckets = ht->bucks;
	float ratio = (float)(size/buckets);
	float loadFactor = 0.5;
	return(ratio > loadFactor);
}


static entry_t *entry_create(elem_t key, elem_t value, entry_t *next)
{
    entry_t *entry = calloc(1, sizeof(entry_t));
    entry->key=key;
    entry->value=value;
    entry->next=next;
    return entry;
}


static void entry_destroy(entry_t *entry)
{
  free(entry);
}

int ioopm_hash_table_elem_t_to_int(elem_t key)
{
	return 0;
}



ioopm_hash_table_t *ioopm_hash_table_create(hashfun_t hash_function)
{
    
  /// Allocate space for a ioopm_hash_table_t = 17 pointers to
  /// entry_t's, which will be set to NULL

  ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
  result->bucks = BUCKS;
  result->hash_function = hash_function;
  result->size = 0;
  result->buckets = calloc(result->bucks, sizeof(entry_t));
  for (int i = 0 ; i < BUCKS; i++)
	  {
		  result->buckets[i] = (entry_t) {.key = int_elem(0), .value = int_elem(0), .next = NULL}; 
	  }
  return result;
}


static entry_t *find_previous_entry_for_key(ioopm_hash_table_t *ht, entry_t *current, int key)
{
	while (current->next !=NULL && (ht->hash_function)(current->next->key) < key)
		{
			current = current->next;
		}
	return current;

}


ioopm_option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key)
{
	int int_key = (ht->hash_function)(key);
  /// Find the previous entry for key
	entry_t *tmp = find_previous_entry_for_key(ht, &ht->buckets[abs(int_key) % ht->bucks], int_key);
	entry_t *next = tmp->next;
  // We have to check if the key is the one we are looking for.
  // Otherwise we cannot know
	if ((next) && (ht->hash_function)(next->key) == int_key)
  {
	  ioopm_option_t result = { .success = true, .value = next->value, .key = next->key};
	  return result;
  }
else
  {
    return Failure();
  }
}


static void ioopm_resize_ht(ioopm_hash_table_t *ht)
{
	ioopm_list_t *keys = ioopm_hash_table_keys(ht);
	ioopm_list_t *values = ioopm_hash_table_values(ht);
	int size_of_ht = ht->size;
	size_t primes[] = {17, 31, 67, 127, 257, 509, 1021, 2053, 4099, 8191, 16381};
	int i = 0;
	while (ht->bucks != primes[i])
	{
		i++;
	}
	if (i < 10)
		{
			ht->bucks = primes[i+1];
		}
	else
		{
			ht->bucks = primes[10];
		}
	entry_t *newBuckets = ht->buckets;
	ht->buckets = (entry_t *)realloc(newBuckets, ht->bucks * sizeof(entry_t));
	ioopm_hash_table_clear(ht); //h
	for (int y = primes[i]; y < primes[i+1]; y++)
		{
			ht->buckets[y] = (entry_t) {.key = int_elem(0), .value = int_elem(0), .next = NULL};  
		}

	
	for (size_t i = 0; i < size_of_ht; i++)
	{	
		elem_t key = ioopm_linked_list_get(keys, i);
		elem_t value = ioopm_linked_list_get(values, i);
		ioopm_hash_table_insert(ht, key, value);
	}
	ioopm_linked_list_destroy(keys);
	ioopm_linked_list_destroy(values);
}




void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value)
{
	int int_key = (ht->hash_function)(key);
	//assert(int_key != 0);
  /// Calculate the bucket for this entry
	int bucket = abs(int_key) % ht->bucks;
  /// Search for an existing entry for a key
	entry_t *entry = find_previous_entry_for_key(ht, &ht->buckets[bucket], int_key);
  entry_t *next = entry->next;

  /// Check if the next entry should be updated or not
  if (next != NULL && (ht->hash_function)(next->key) == int_key)
    {
      next->value = value;
    }
  else
    {
        entry->next = entry_create(key, value, next);   
        ht->size +=1;
		if (bucket_limit(ht))
		{
			ioopm_resize_ht(ht);
		}
		                             
    }  

}




elem_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key)
{
	int int_key = (ht->hash_function)(key);
	int bucket = abs(int_key) % ht->bucks;
	ioopm_option_t result = ioopm_hash_table_lookup(ht, key);
	bool lookupper = Successful(result);
  if (lookupper == true)
  {
	  entry_t *pEntry = find_previous_entry_for_key(ht, &ht->buckets[bucket], int_key);
	elem_t value = pEntry->next->value;
    ht->size -=1;
    if (pEntry->next == NULL)
    {
      entry_destroy(pEntry->next);
      return value;
    }
    else 
    {
      entry_t *tmp = pEntry->next;
      pEntry->next = pEntry->next->next;
      entry_destroy(tmp);
      return value;
    }
  }
  else 
  {
	  
	  elem_t empty;
	  empty.s = "NO";
    return empty;
  }
  
}


size_t ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
  return ht->size;
}


bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
	return (ioopm_hash_table_size(ht) == 0);
}



//TO-DO ta bort i-argumentet
static entry_t *key_traverser(entry_t *current, ioopm_hash_table_t *ht, int counter,ioopm_list_t *keys)
{
	if(!current->next) return current;
	entry_t *to_add = key_traverser(current->next,ht, counter, keys);
	ioopm_linked_list_insert(keys, counter, (to_add->key));
	counter++;
	return current;
}

ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{

  ioopm_list_t *keys = calloc(ioopm_hash_table_size(ht), sizeof(link_t));
  int counter = 0; 
  for ( int i = 0; i < ht->bucks; i++)
  {
	  	  if (ioopm_hash_table_is_empty(ht))
		  {
			  break;
		  }
		  entry_t *current = &ht->buckets[i];
		  key_traverser(current,ht,counter,keys);
    }
  return keys;
}



static entry_t *value_traverser(entry_t *current, ioopm_hash_table_t *ht, int counter,ioopm_list_t *values)
{
	if(!current->next) return current;
	entry_t *to_add = value_traverser(current->next,ht, counter, values);
	ioopm_linked_list_insert(values, counter, (to_add->value));
	counter++;
	return current;
}



ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht)
{
	ioopm_list_t *values = calloc(ioopm_hash_table_size(ht), sizeof(link_t));
	int counter = 0; 
	for ( int i = 0; i < ht->bucks; i++)
		{
			if (ioopm_hash_table_is_empty(ht))
				{
					break;
				}
			entry_t *current = &ht->buckets[i];
			value_traverser(current,ht,counter,values);
		}
	return values;
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key)
{
	return (ioopm_hash_table_lookup(ht,key).success);
}

bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value, ioopm_eq_function eqfun)
{
	ioopm_list_t *values = ioopm_hash_table_values(ht);
	values->eqfun = eqfun;
	bool result = ioopm_linked_list_contains(values,value);
	ioopm_linked_list_destroy(values);
	return result;
}

bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg)
{
	int size = ioopm_hash_table_size(ht);
	ioopm_list_t *keys = ioopm_hash_table_keys(ht);
	ioopm_list_t *values = ioopm_hash_table_values(ht);
	bool result = true;
	for (int i = 0; i < size && result; ++i)
		{
			result = result && (pred)(ioopm_linked_list_get(keys,i),(ioopm_linked_list_get(values,i)), arg);
		}
	ioopm_linked_list_destroy(keys);
	ioopm_linked_list_destroy(values);
	return result;
}

bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg)
{
	int size = ioopm_hash_table_size(ht);
	ioopm_list_t *keys = ioopm_hash_table_keys(ht);
	ioopm_list_t *values = ioopm_hash_table_values(ht);
	bool result = false;
	for (int i = 0; i < size; ++i)
		{
			result = (pred)(ioopm_linked_list_get(keys,i), ioopm_linked_list_get(values,i), arg);
			if (result)
				{
					ioopm_linked_list_destroy(keys);
					ioopm_linked_list_destroy(values);
					return result;
				}
		}
	ioopm_linked_list_destroy(keys);
	ioopm_linked_list_destroy(values);
	return result;
}


void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *arg)
{
	int size = ioopm_hash_table_size(ht);
	ioopm_list_t *keys = ioopm_hash_table_keys(ht);
	ioopm_list_t *values = ioopm_hash_table_values(ht);
	for (int i = 0; i < size; i++)
		{
			elem_t current_value = ioopm_linked_list_get(values,i);
			(apply_fun)((ioopm_linked_list_get (keys,i)), &current_value, arg);
			ioopm_hash_table_insert(ht, ioopm_linked_list_get (keys,i), current_value);
		}
	ioopm_linked_list_destroy(keys);
	ioopm_linked_list_destroy(values);
}


static entry_t *traverser(entry_t *current, ioopm_hash_table_t *ht)
{
  if (!current->next) return current;
  entry_t *to_remove = traverser(current->next,ht);
  entry_destroy(to_remove);
  ht->size -= 1;
  return current;
}



void ioopm_hash_table_clear(ioopm_hash_table_t *ht)
{
for (int i = 0; i < ht->bucks; i++)
  {
	  if (ioopm_hash_table_is_empty(ht))
		  {
			  break;
		  }
      entry_t *current = &ht->buckets[i];
      traverser(current,ht);
	  current->next = NULL;
  }
}


 void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
	if (!(ioopm_hash_table_is_empty(ht)))
		{
			ioopm_hash_table_clear(ht);
		}
	for (int i = 0; i < 1; i++)
		{
			free(ht->buckets);
		}
	free(ht);
}





