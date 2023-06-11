#ifndef EASY_COLLECTION_LIST_H
#define EASY_COLLECTION_LIST_H

#include <stdlib.h>
#include <string.h>


typedef struct _linked_list_ LinkedList;
typedef struct _linked_list_node LinkedListNode;

typedef struct _linked_list_ {

    LinkedListNode *head;
    LinkedListNode *rear;

} LinkedList;


typedef struct _linked_list_node {
    void* data;

    LinkedListNode *prev;
    LinkedListNode *next;
} LinkedListNode;


typedef struct _linked_list_iter_ {
    LinkedList *list;
    LinkedListNode *pos;
} LinkedListIter;


LinkedList* list_new();
void list_append(LinkedList *list,void* data);
LinkedListNode* list_get(LinkedList *list,void* data);
LinkedListNode* list_remove(LinkedList *list,LinkedListNode *node);
void list_empty(LinkedList *list);
void list_release(LinkedList *list);

LinkedListIter* list_iter(LinkedList *list);
LinkedListNode* list_iter_next(LinkedListIter *iter);
void list_iter_reset(LinkedListIter *iter);


#endif