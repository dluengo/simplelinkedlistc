#ifndef __SIMPLE_LINKED_LIST_H_
#define __SIMPLE_LINKED_LIST_H_

// Nodes of the list, intended to be used just by the list (i.e. not public).
struct node_t {
    void *data;
    struct node_t *next;
};

// The list itself. The name stands for Simple-Linked List.
typedef struct {
    unsigned int size;
    struct node_t *head;
} SLList_t;

SLList_t *SLList_Create();

void SLList_Destroy(SLList_t *self);

int SLList_Append(SLList_t *self, void *data);

int SLList_Remove(SLList_t *self, unsigned int pos);

void *SLList_Access(SLList_t *self, unsigned int pos);

unsigned int SLList_Size(SLList_t *self);

void SLList_Print(SLList_t *self, void (*print_data)(void *data_to_print));

#endif 
