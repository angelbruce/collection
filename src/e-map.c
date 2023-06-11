#include "e-map.h"
#include <math.h>

#define Var(T,var,n)                T *var  = (T *) malloc(sizeof(T) * (n)); memset(var,0,sizeof(T) * (n));
#define New(T,var,n)                var  = (T *) malloc(sizeof(T) * (n)); memset(var,0,sizeof(T) * (n));



HashMap* map_new() {
    Var(HashMap,map,1);
    memset(map->entrySet,0,sizeof(map->entrySet));
    map->capacity = MAP_INI_CAPACITY;
    return map;
}

void map_put(HashMap *map,char *key,void *data) {
    long hash = hashcode(map,key);
    int idx = hash % map->capacity;
    HashMapEntry *entry  = &map->entrySet[idx];
    if(!entry->item) {
        New(HashMapItem,entry->item,1);
        entry->item->hash = hash;
        entry->item->data = data;
        map -> length ++;
        return;
    } else {
        if( hash == entry->item->hash) {
            free(entry -> item -> data);
            entry -> item -> data = data;
            return;
        }
        
        LinkedList *bkt = entry -> bucket;
        if(!bkt) {
            bkt = list_new();
            entry -> bucket = bkt;
            Var(HashMapItem,ent,1);
            ent->hash = hashcode;
            ent->data = data;
            list_append(bkt,ent);
            map->length ++;
        } else {
            LinkedListNode *cur = 0;
            HashMapItem *ent = 0;
            LinkedListIter *iter = list_iter(bkt);
            while((cur = list_iter_next(iter))) {
                ent = (HashMapItem*)(cur->data);
                if(ent->hash == hash) {
                    free(ent->data);
                    ent->data=data;
                    return ;
                }
            }
            
            New(HashMapItem,ent,1);
            ent -> hash = hash;
            ent -> data = data;
            list_append(bkt,ent);
            map->length ++;
        }
    }

}


void* map_get(HashMap *map,char* key) {
    long hash = hashcode(map,key);
    HashMapEntry *entry  = &map->entrySet[hash];
    if(entry->item) {
        if(entry->item->hash==hash) {
            return entry->item->data;
        } else {
            LinkedList *bkt = entry -> bucket;
            if(!bkt) return 0;

            LinkedListNode *cur = 0;
            HashMapItem *ent = 0;
            LinkedListIter *iter = list_iter(bkt);
            while((cur = list_iter_next(iter))) {
                ent = (HashMapItem*)(cur->data);
                if(ent->hash == hash) return ent -> data;
            }
        }
    }

    return 0;
}

void* map_remove(HashMap* map,char *key) {
   long hash = hashcode(map,key);
    HashMapEntry *entry  = &map->entrySet[hash];
    if(entry->item) {
        if(entry->item->hash==hash) {
            map -> length --;
            void *data = entry->item->data;
            free(entry->item);
            LinkedList *bkt = entry -> bucket;
            if(!bkt) return data;

            LinkedListNode *head = bkt->head;
            if(head) {
                entry->item = (HashMapItem*) head-> data;
                if(head->next) head->next->prev = 0;
                bkt -> head = head->next;
                head-> next = 0;

                if(!bkt->head) bkt->rear = 0;
            }
        } else {
            LinkedList *bkt = entry -> bucket;
            if(!bkt) return 0;

            LinkedListNode *cur = 0;
            HashMapItem *ent = 0;
            LinkedListIter *iter = list_iter(bkt);
            while((cur = list_iter_next(iter))) {
                ent = (HashMapItem*) cur->data;
                if(ent->hash==hash) {
                    map -> length --;
                    void* data = ent->data;
                    list_remove(bkt,cur);
                    return data;
                }
            }
        }
    }

    return 0; 
}


int map_size(HashMap *map) {
    return map->length;
}

void map_empty(HashMap* map) {
    //TODO
}

void map_release(HashMap* map) {
    //TODO
    free(map);
}

long hashcode(HashMap *map,char* name) {
    if(!name) return 0;
    char* p = name;
    long hash = 0;
    int l = strlen(name);
    int i = 0;
    for (i = 0;i < l; i++) {
        char c = *(p+i);
        hash += c * pow(31,(l-i-11));
    }

    return hash;
}
