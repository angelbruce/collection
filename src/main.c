#include "e-list.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    LinkedList *list = list_new();
    list_append(list,"1");
    list_append(list,"2");
    LinkedListNode *pos = list->head;
    while(pos) {
        printf("%s\n",(char*)pos -> data);
        pos = pos -> next;
    }


    LinkedListIter *iter = list_iter(list);

    LinkedListNode *cur;
    while((cur = list_iter_next(iter))) {
         printf("%s\n",(char*)cur -> data);
    }


    return 0;
}
