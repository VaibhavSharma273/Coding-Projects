#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "Deque.h"

typedef struct node {
    struct node* next;
    char* value;
} Node; 

typedef struct stack {
    Node* head; 
} *Stack;

struct deque {
    Stack T;
    Stack H;
};

// Implementation of createD()
bool createD (Deque *d)
{
    if ((*d = malloc (sizeof (**d))) == NULL)
        return false;
    if (((*d)->T = malloc (sizeof (Stack*))) == NULL)
        return false;
    if (((*d)->H = malloc (sizeof (Stack*))) == NULL)
        return false;

    ((*d)->T)->head = NULL;
    ((*d)->H)->head = NULL;
    return true;
}


// Implementation of isEmptyD()
bool isEmptyD (Deque *d)
{
    if (((*d)->T)->head == NULL && ((*d)->H)->head == NULL)
        return true;

    else if ((*d)->H->head == NULL)
        {
            while (((*d)->T)->head != NULL) {
                Node* e = malloc(sizeof(*e));
                Node* r;
                r = ((*d)->T)->head;

                e->value = r->value;
                e->next = ((*d)->H)->head;
                ((*d)->H)->head = e;

                ((*d)->T)->head = r->next;
                free (r);
            }
            return false;
        }
    else 
        return false;
}


// Implementation of addD()
bool addD (Deque *d, char *s)
{
    if (*d == NULL)
        return false;

    Node* e = malloc(sizeof(*e));
    if (e == NULL)
        return false;
    
    e->value = s;
    e->next = ((*d)->T)->head;
    ((*d)->T)->head = e;
    return true;
}


// Implementation of remD()
bool remD (Deque *d, char **s)
{
    if (*d == NULL)
        return false;

    if (isEmptyD(d)) {
        *s = NULL;
        return false;
    }
    else {
        Node* e;
        e = ((*d)->H)->head;
        *s = e->value;
        ((*d)->H)->head = e->next;
        free(e);   
    }

  return true;
}


// Implementation of headD()
bool headD (Deque *d, char **s)
{
    if (*d == NULL)
        return false;

    if (isEmptyD(d)) {
        *s = NULL;
        return false;
    }
    else {
        Node* e;
        e = ((*d)->H)->head;
        *s = e->value;
    }
    
  return true;
}


// Implementation of pushD()
bool pushD (Deque *d, char *s)
{
    if (*d == NULL)
        return false;

    Node* e = malloc(sizeof(*e));
    if (e == NULL)
        return false;

    e->value = s;
    e->next = ((*d)->H)->head;
    ((*d)->H)->head = e;

    return true;
}

// Implementation of destroyD()
bool destroyD (Deque *d)
{
    if (*d == NULL)
        return false;
    char* line;
    while (!isEmptyD(d)) {
        remD(d, &line);
        line = NULL;
    }
    free((*d)->H);
    free((*d)->T);
    free(*d);
    *d = NULL;
    return true; 
}