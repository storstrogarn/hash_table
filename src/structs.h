#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "linked_list.h"

/*
 * @file structs.h
 * @author Johan Söderström & Oscar Johansson
 * @date 18 Sep 2021
 * @brief a simple collection of structs used accros the data structures.
 *
*/

typedef union elem elem_t;

union elem
{
    int i;
    unsigned int u;
    bool b;
    float f;
    void *p;
    char *s;

};




struct link
{
    elem_t value;
    struct link *next;
};

typedef struct link link_t;
typedef struct iter ioopm_list_iterator_t;
typedef struct list ioopm_list_t;

typedef bool(*ioopm_eq_function)(elem_t a, elem_t b);

struct list
{
    link_t *head;
    size_t size;
    link_t *last;
    ioopm_eq_function eqfun;
};


struct iter
{
    link_t *current;
    ioopm_list_t *list;
};

