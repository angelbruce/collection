#include "e-list.h"


#define Var(T,var,n)                T *var  = (T *) malloc(sizeof(T) * (n)); memset(var,0,sizeof(T) * (n));
#define New(T,var,n)                var  = (T *) malloc(sizeof(T) * (n)); memset(var,0,sizeof(T) * (n));

LinkedList* list_new() {
    Var(LinkedList,list,1);
    list -> head = list -> rear = 0;
    return list;
}


void list_append(LinkedList *list,void *data) {
    if(!list) return;

    Var(LinkedListNode,node,1);
    node->data = data;
    if(!(list-> head) && !(list-> rear)) {
        list -> head = list-> rear = node;
    } else {
        list->rear->next = node;
        node->prev = list->rear;
        list->rear = node;
    }
}


LinkedListNode* list_get(LinkedList *list,void* data) {
    if(!list)  return 0;

    LinkedListNode *pos = list -> head;
    while(pos) {
        if( pos -> data == data) return pos;
        pos = pos -> next;
    }

    return 0;
}


LinkedListNode* list_remove(LinkedList *list,LinkedListNode *node) {
    if(!list)  return 0;
    if(!node) return 0;

    if(node -> prev && node -> next) {
        node -> prev -> next = node -> next;
        node -> next -> prev = node -> prev;
        free(node);
    } else if (node -> prev && !node -> next) {
        list -> rear = node -> prev;
        node -> prev -> next = 0;
        free(node);
    } else if (!node->prev && node-> next) {
        list -> head = node -> prev;
        node -> next -> prev = 0;
        free(node);
    } else {
        list -> head = list -> rear = 0;
        free(node);
    }

}


void list_empty(LinkedList *list) {
    if(!list) return;
    LinkedListNode *pos = list->head;
    while(pos) {
        if(pos -> prev) free(pos -> prev);
        pos = pos -> next;
    }

    if(pos) {
        free(pos);
    }

    list->head=list->rear = 0;
    list->head->next=list->head->prev = 0;
    list->rear->next=list->rear->prev = 0;
}

void list_release(LinkedList *list) {
    list_empty(list);
    free(list);
}

LinkedListIter* list_iter(LinkedList *list) {
    if(!list) return 0;

    Var(LinkedListIter,iter,1);
    iter -> list = list;
    iter -> pos = list -> head;
    return iter;
}

LinkedListNode* list_iter_next(LinkedListIter *iter) {
    if(!iter || !iter->list) return 0;

    if(iter -> pos) {
        LinkedListNode *node = iter -> pos;
        iter -> pos = iter -> pos -> next;
        return node;
    }
    
    return 0;
}

void list_iter_reset(LinkedListIter *iter) {
    if(!iter || !iter->list) return;
    
    iter -> pos = iter -> list -> head;
}
