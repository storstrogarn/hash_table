#include "linked_list.h"
#include "structs.h"
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <limits.h>


/**
 * @file simple_linked_list.c
 * @author Elias Castegren, Oscar Johansson, and Johan Söderström
 * @date 18 Sep 2021
 * @brief A simple linked list that implements parts of the interface 
 * of `linked_list.h`.
 */
 


link_t *link_create(elem_t value, link_t *next)
{
    link_t *link = calloc(1, sizeof(link_t));
    link->value = value;
    link->next = next;
    return link;
}



ioopm_list_t *ioopm_linked_list_create(ioopm_eq_function eqfun)
{
ioopm_list_t *results = calloc(1, sizeof(struct list));
results->eqfun = eqfun;
results->size = 0;
return results;
}

void ioopm_linked_list_destroy(ioopm_list_t *list)
{
    assert(list);
    link_t *current = list->head;
    while (current)
    {
        link_t *tmp = current;
        current = current->next;
        free(tmp);
    }
    free(list);
}

void ioopm_linked_list_append(ioopm_list_t *list, elem_t value)
{
	assert(list);
    if (list->size == 0)
    {
        list->head = link_create(value,list->head);
        list->last = list->head;
    }
	else if (list->size == 1)
		{
			list->head->next = link_create(value,list->head->next);
			list->last = list->head->next;
		}
    else if (list->size > 1)
    {
        list->last->next = link_create(value,list->last->next);
        list->last = list->last->next;
    }
    list->size++;
}

void ioopm_linked_list_prepend(ioopm_list_t *list, elem_t value)
{
    assert(list);
    list->head = link_create(value, list->head);
	if (ioopm_linked_list_size(list) == 0)
		{
			list->last = list->head;
		}
    list->size++;
}


void ioopm_linked_list_insert(ioopm_list_t *list, int index, elem_t value)
{   
    assert(index >= 0);
    assert(index <=ioopm_linked_list_size(list));
    assert(list);
    index = abs(index);
    if(index == 0)
        {
            ioopm_linked_list_prepend(list,value);
        }
    else if((ioopm_linked_list_size(list)) == 1 || index == (ioopm_linked_list_size(list)))
        {
            ioopm_linked_list_append(list,value);
        }
    else
        {
            link_t *old_head = list->head;
            for (int i = 0; i<(index-1); i++)
                {
                    list->head = list->head->next;
                }
            link_t *old_link = list->head->next;
            list->head->next = link_create(value,list->head->next->next);
            list->head->next->next = old_link;
            list->head = old_head;
            list->size++;
        }
}



elem_t ioopm_linked_list_remove(ioopm_list_t *list, int index)
{
    assert(list);
    assert(list->head);
    elem_t maxer; 
    maxer.i = INT_MAX;
	if (index < 0 || index > (list->size+1))
		{
			return maxer;
		}
	
    if (index == 0)
    {
        link_t *tmp = list->head;
        elem_t value = tmp->value;
        list->head = tmp->next;
        free(tmp);
        list->size--;
        return value;
    }

    // index > 0
    assert(list->head);
    link_t *prev = list->head;
    link_t *current = prev->next;
    for (int i = 1; i < index; i++)
    {
        assert(current);
        prev = current;
        current = current->next;
    }

    prev->next = current->next;
    elem_t value = current->value;
    free(current);
    list->size--;
    return value;
}

elem_t ioopm_linked_list_get(ioopm_list_t *list, int index)
{
    assert(list);
    assert(list->head);
    link_t *current = list->head;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
        assert(current);
    }
    return current->value;
}

bool ioopm_linked_list_contains(ioopm_list_t *list, elem_t element)
{
    
    assert(list);
    link_t *cursor = list->head;
    while (cursor)
    {
        if((list->eqfun)(cursor->value,element))
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

size_t ioopm_linked_list_size(ioopm_list_t *list)
{
    assert(list);
    return list->size;
}

bool ioopm_linked_list_is_empty(ioopm_list_t *list)
{
    if (list->size == 0)
    {
        return true;
    }
    return false;
}



void ioopm_linked_list_clear(ioopm_list_t *list)
{
int size = list->size; 
int head = 0;
for (int i = 0; i < size; i++)
{
    ioopm_linked_list_remove(list, head);
}
}




bool ioopm_linked_list_all(ioopm_list_t *list, ioopm_char_predicate prop, void *extra)
{   
    bool result = true;
    link_t *current = list->head;
	for (int i = 0; i < list->size && result; ++i)
    {
        result = result && (prop)(current->value, extra);
        current = current->next;
    }   
    return result;
}
    


bool ioopm_linked_list_any(ioopm_list_t *list, ioopm_char_predicate prop, void *extra)
{
    bool result = false;
    link_t *current =list->head;
    for (int i = 0; i < list->size; i++)
    {
        result = (prop)(current->value, extra);
        current = current->next;
        if (result == true)
        {
            return result;
        }
    }
    return result; 
}


void ioopm_linked_apply_to_all(ioopm_list_t *list, ioopm_apply_char_function fun, void *extra)
{
	link_t *current = list->head;
    for (int i = 0; i < list->size; i++)
    {
        (fun)(&(current->value), extra);
		current = current->next;
    }
}

