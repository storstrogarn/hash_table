#include "structs.h"
#include "iterator.h"
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
/**
 * @file iterator.c
 * @author Oscar Johansson, and Johan Söderström
 * @date 24 Sep 2021
 * @brief A simple linked list that implements parts of the interface 
 * of `linked_list.h`. The functions that are not implemented will fail
 * at runtime with an assertion error, printing a message to stderr.
 */


 


ioopm_list_iterator_t *ioopm_list_iterator(ioopm_list_t *list)
{
    assert(list);
    ioopm_list_iterator_t *result = calloc(1, sizeof(ioopm_list_iterator_t));
    result->list = list;
	result->current = list->head;
    return result; 
}


bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter)
{

    if (iter->current->next == NULL)
    {
        return false;
    }
    return true;
}


elem_t ioopm_iterator_current(ioopm_list_iterator_t *iter)
{
  return iter->current->value;
}


elem_t ioopm_iterator_next(ioopm_list_iterator_t *iter)
{
    if (iter->current->next != NULL)
    {
    
   iter->current = iter->current->next;
   return(iter->current->value);
    }
    elem_t intmaximum;
    intmaximum.i=INT_MAX;
    return intmaximum;
}



void ioopm_iterator_destroy(ioopm_list_iterator_t *iter)
{
    free(iter);
}

void ioopm_iterator_reset(ioopm_list_iterator_t *iter)
{
    iter->current = iter->list->head;
}
