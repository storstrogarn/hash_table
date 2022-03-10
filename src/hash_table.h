#pragma once
#include <stdbool.h>
#include <stdio.h>
#include "structs.h"

/**
 * @file hash_table.h
 * @author Johan Söderström & Oscar Johansson
 * @date 14 Sep 2021
 * @brief Simple hash table that maps integer keys to string values.
 *
 * A simple hash table which utilizes an array of linked lists, which will expand upon the hash table's size reaching the LF limit.
 * The initial array size and LF limit can be adjusted at the top in hash_table.c 
 *
 *
 *
*/


typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;


typedef struct option ioopm_option_t;
struct option
{
	bool success;
	elem_t value;
	elem_t key;
};

typedef bool (*ioopm_predicate)(elem_t key, elem_t value, void *extra);
typedef void (*ioopm_apply_function)(elem_t key, elem_t *value, void *extra);
typedef int (*hashfun_t)(elem_t key);


/// @brief Create a new hash table
/// @param hash_function function for converting keys to ints
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(hashfun_t hash_function);


/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);


/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value);


/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @return the value mapped to by key if it exists, along with a bool.
ioopm_option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key);


/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @return the value mapped to by key, if value is not in ht, return "NO".
elem_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key);


/// @brief returns the number of key => value entries in the hash table
/// @param h hash table operated upon
/// @return the number of key => value entries in the hash table
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht);


/// @brief checks if a hash table is emty
/// @param h hash table operated upon
/// @return returns a bool, true, if emty, false if not emty
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);


/// @brief clear all the entries in a hash table
/// @param h hash table operated upon
void ioopm_hash_table_clear(ioopm_hash_table_t *ht);

/// @brief return the keys for all entries in a hash map (in no particular order, but same as ioopm_hash_table_values)
/// @param h hash table operated upon
/// @return a linked list of keys for hash table h
ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht);

/// @brief return the values for all entries in a hash map (in no particular order, but same as ioopm_hash_table_keys)
/// @param h hash table operated upon
/// @return a linked list of values for hash table h
ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht);


/// @brief check if a hash table has an entry with a given key
/// @param h hash table operated upon
/// @param key the key sought
/// @return a bool for whether the key was found in ht or not.
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key);

/// @brief check if a hash table has an entry with a given value
/// @param h hash table operated upon
/// @param value the value sought
/// @param eqfun function for comparing elem_ts with each other
/// @return a bool for whether the key was found in ht or not.
bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value, ioopm_eq_function eqfun);


/// @brief check if a predicate is satisfied by all entries in a hash table
/// @param h hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg);

/// @brief check if a predicate is satisfied by any entry in a hash table
/// @param h hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg);

/// @brief apply a function to all entries in a hash table
/// @param h hash table operated upon
/// @param apply_fun the function to be applied to all elements
/// @param arg extra argument to apply_fun
void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *arg);
