/**
* deque.c consists of function definitions of the deque implementation.
*/

#include "deque.h"


/* === function definitions ========================================================= */
DEQUE * getNewNode (int value) {
    DEQUE *newNode;
    if ((newNode = (DEQUE *)malloc(sizeof(DEQUE))) == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }

    newNode->value = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void pushFront (DEQUE ** root, int value) {
    if ((*root) == NULL) {
        /* if root is null, simply initialise the root */
        (*root) = getNewNode(value);
        return;
    }

    DEQUE *newNode = getNewNode(value);
    /* assigning newNode to the front of root */
    (*root)->prev = newNode;
    newNode->next = (*root);
    (*root) = newNode;
}

void pushBack (DEQUE ** root, int value) {
    if ((*root) == NULL) {
        /* if root is null, simply initialise the root */
        (*root) = getNewNode(value);
        return;
    }

    /* adding newNode to the end of root */
    if ((*root)->next == NULL) {
        DEQUE *newNode = getNewNode(value);
        (*root)->next = newNode;
        newNode->prev = (*root);
    }
    else {
        pushBack(&(*root)->next, value);
    }
}

int popFront (DEQUE ** root) {
    int value;
    if ((*root) == NULL) return -1;
    else value = (*root)->value;

    if ((*root)->next == NULL) {
        DEQUE *temp = *root;
        (*root) = NULL;
        free(temp);
        return value;
    }

    /* removing the front node from root */
    DEQUE *temp = *root;
    (*root) = (*root)->next;
    free(temp);
    (*root)->prev = NULL;
    return value;
}

int popBack (DEQUE ** root) {
    int value;
    if ((*root) == NULL) return -1;
    else value = (*root)->value;

    /* removing node at the end of root */
    if ((*root)->next == NULL) {
        DEQUE *temp = *root;
        (*root) = (*root)->prev;
        free(temp);
        (*root)->next = NULL;
        return value;
    }
    else {
        return popBack(&(*root)->next);
    }
}

int sizeDeque (DEQUE * root) {
    int accumSize = 0;
    while (root != NULL) {
        root = root->next;
        accumSize++;
    } return accumSize;
}

void emptyDeque (DEQUE ** root) {
    freeDeque(*root);
    (*root) = NULL;
}

int isEmpty (DEQUE * root) {
    return root == NULL;
}

void freeDeque (DEQUE * root) {
    while (root != NULL)
    {
        DEQUE *temp = root;
        root = root->next;
        free(temp);
    }
}

void printDeque (DEQUE * root) {
    /* start of deque */
    printf("[");
    if (root == NULL) {
        /* end of deque */
        printf("]\n");
        return;
    }

    while (root->next != NULL) {
        printf("%d, ", root->value);
        root = root->next;
    }
    /* end of deque */
    printf("%d]\n", root->value);
}
