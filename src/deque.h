/**
 * deque.h consists of structure definitions and function prototypes
 * of the deque as a doubly linked list implementation.
 */

#ifndef TRAFFIC_SIM_DEQUE_H
#define TRAFFIC_SIM_DEQUE_H

#include <stdio.h>
#include <stdlib.h>


/* === structure definitions ========================================================= */
struct dequeStruct {
    /* value single node holds */
    int value;

    /* next and previous nodes - doubly linked list */
    struct dequeStruct *next;
    struct dequeStruct *prev;
}; typedef struct dequeStruct DEQUE;


/* === function prototypes ========================================================= */
DEQUE * getNewNode (int value);
void pushFront (DEQUE **, int);
void pushBack (DEQUE **, int);
int popFront (DEQUE **);
int popBack (DEQUE **);

int sizeDeque (DEQUE *);
void emptyDeque (DEQUE **);
int isEmpty (DEQUE *);
void freeDeque (DEQUE *);
void printDeque (DEQUE *);


#endif
