#include "SLList.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/***************************** Helper functions. *****************************/

// List mustn't be NULL.
struct node_t * __get_last_node(SLList_t *list) {
    struct node_t *node;

    node = list->head;
    while (node != NULL && node->next != NULL) {
        node = node->next;
    }

    return node;
}


/******************************* Node methods. *******************************/

struct node_t * Node_Create() {
    struct node_t *node;

    node = malloc(sizeof(struct node_t));
    if (node == NULL) {
        return NULL;
    }

    node->data = NULL;
    node->next = NULL;

    return node;
}

void Node_Destroy(struct node_t *node) {
    free(node);
    return;
}


/****************************** Public methods. ******************************/

SLList_t *SLList_Create() {
    SLList_t *list;
    
    list = malloc(sizeof(SLList_t));
    if (list == NULL) {
        return NULL;
    }

    list->size = 0;
    list->head = NULL;

    return list;
}

void SLList_Destroy(SLList_t *self) {
    struct node_t *curr_node, *next_node;
    if (self != NULL) {
        curr_node = self->head;
        while (curr_node != NULL) {
            next_node = curr_node->next;
            Node_Destroy(curr_node);
            curr_node = next_node;
        }
    }

    free(self);
    return;
}

int SLList_Append(SLList_t *self, void *data) {
    struct node_t *last_node, *new_node;
    assert(self != NULL && data != NULL);

    new_node = Node_Create();
    if (new_node == NULL) {
        return -1;
    }

    new_node->data = data;
    new_node->next = NULL;

    last_node = __get_last_node(self);
    if (last_node == NULL) {
        self->head = new_node;
    } else {
        last_node->next = new_node;
    }

    self->size++;
    return 0; 
}

void *SLList_Access(SLList_t *self, unsigned int pos) {
    struct node_t *node;
    assert(self != NULL && pos < self->size);

    for (node = self->head; pos != 0; node = node->next, pos--);
    return node->data;
}

unsigned int SLList_Size(SLList_t *self) {
    assert(self != NULL);

    return self->size;
}

void SLList_Print(SLList_t *self, void (*print_data)(void *data_to_print)) {
    const int ELEMS_PER_ROW = 5;
    struct node_t *node;
    char separator;
    int i;

    assert(self != NULL && print_data != NULL);

    printf("[");
    for (i = 0, node = self->head; node != NULL; i++, node = node->next) {
        separator = (i % ELEMS_PER_ROW == ELEMS_PER_ROW-1) &&
            (node->next != NULL)? '\n': ',';

        print_data(node->data);
        if (node->next != NULL) {
            printf("%c", separator);
        }
    }

    printf("]\n");
    return;
}

