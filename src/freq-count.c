
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"
#include "linked_list.h"
#include "structs.h"

#define Delimiters "+-#@()[]{}.,:;!? \t\n\r"
#define BUCKS 17

struct entry
{
  elem_t key;       // holds the key
  elem_t value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

typedef struct entry entry_t;

struct hash_table
{
  entry_t *buckets;
  size_t size;
  hashfun_t hash_function;
  size_t bucks;
};



typedef struct hash_table ioopm_hash_table_t;

static int cmpstringp(const void *p1, const void *p2)
{
  return strcmp(*(char *const *)p1, *(char *const *)p2);
}

void sort_keys(char *keys[], size_t no_keys)
{
  qsort(keys, no_keys, sizeof(char *), cmpstringp);
}

void process_word(char *word, ioopm_hash_table_t *ht)
{
  // FIXME: Rewrite to match your own interface, error-handling, etc. funkar?
  int freq =
    ioopm_hash_table_has_key(ht, (elem_t) {.p = word})?
    (ioopm_hash_table_lookup(ht, (elem_t) {.p = word})).value.i:
    0;
  // Här sker minnesläckage pga strdup. Måste free:a varje ord i ht.
  if (freq == 0)
	  {
		  ioopm_hash_table_insert(ht, (elem_t) {.p =  strdup(word)}, (elem_t) {.i = freq + 1});
	  }
  else
	  {
		  ioopm_hash_table_insert(ht, (elem_t) {.p =  word}, (elem_t) {.i = freq + 1});
	  }

}

void process_file(char *filename, ioopm_hash_table_t *ht)
{
  FILE *f = fopen(filename, "r");

  while (true)
  {
    char *buf = NULL;
    size_t len = 0;
    getline(&buf, &len, f);

    if (feof(f))
    {
      free(buf);
      break;
    }

    for (char *word = strtok(buf, Delimiters);
         word && *word;
         word = strtok(NULL, Delimiters))
    {
      process_word(word, ht);
    }

    free(buf);
  }

  fclose(f);
}

int string_sum_hash(elem_t e)
{
  char *str = e.p;
  int result = 0;
  do
    {
      result += *str;
    }
  while (*++str != '\0');
  return result;
}

bool string_eq(elem_t e1, elem_t e2)
{
  return (strcmp(e1.p, e2.p) == 0);
}

char **list_to_string_array(ioopm_list_t *keys)
{
	int listSize = ioopm_linked_list_size(keys);
	char **strArray = calloc(listSize, sizeof(strArray));
	for (int i = 0; i < listSize; i++)
		{
			strArray[i] = (ioopm_linked_list_get(keys,i).s);
		}
	ioopm_linked_list_destroy(keys);
	return strArray;
}


entry_t *key_freer(entry_t *current)
{
	if(!current->next) return current;
	entry_t *to_free = key_freer(current->next);
	free(to_free->key.p);
	return current;
}



void free_the_keys(ioopm_hash_table_t *ht)
{
	int size = ht->bucks;
	if (ioopm_hash_table_is_empty(ht))
		{
			return;
		}
  for ( int i = 0; i < size; i++)
  {
		  entry_t *current = &ht->buckets[i];
		  key_freer(current);
    }
	
}

int main(int argc, char *argv[])
{
	ioopm_hash_table_t *ht = ioopm_hash_table_create(string_sum_hash);

  if (argc > 1)
  {
    for (int i = 1; i < argc; ++i)
    {
      process_file(argv[i], ht);
    }

    // FIXME: If the keys are returned as a list, transfer them into 
    // an array to use `sort_keys` (perhaps using an iterator?)
    char **keys = list_to_string_array(ioopm_hash_table_keys(ht));

    int size = ioopm_hash_table_size(ht);
    sort_keys(keys, size);

	int i = 0;
    for (i = 0; i < size; ++i)
    {
      // FIXME: Update to match your own interface, error handling, etc.
		// FIXAT???
      int freq = (ioopm_hash_table_lookup(ht, (elem_t) {.p = keys[i]})).value.i;
      printf("%s: %d\n", keys[i], freq);
    }
	printf("Unique words in this are: %d\n",i);
	free(keys);
  }
  else
  {
    puts("Usage: freq-count file1 ... filen");
  }

  // FIXME: Leaks memory! Use valgrind to find out where that memory is 
  // being allocated, and then insert code here to free it.

  //Iterera genom ht för att free:a alla ord (keys). Måste göras pga strdup.
  free_the_keys(ht);
  ioopm_hash_table_destroy(ht);
}

