#ifndef EASY_COLLECTION_MAP_H
#define EASY_COLLECTION_MAP_H

#include <stdlib.h>
#include <string.h>

#include "e-list.h"

#define MAP_INI_CAPACITY 1024
#define FACTOR 0.75


typedef struct _hash_map_ HashMap ;
typedef struct _hash_map_entry_ HashMapEntry ;
typedef struct _hash_map_item_ data ;


typedef struct _hash_map_ {

    HashMapEntry entrySet[MAP_INI_CAPACITY];
    int capacity;
    int length;

} HashMap;


typedef struct _hash_map_entry_ {
    char* key;
    HashMapItem *item;
    LinkedList *bucket;
} HashMapEntry;

typedef struct _hash_map_item_ {
    void* data;
    long hash;
} HashMapItem;



HashMap* map_new();
void map_put(HashMap* map,char* key,void* data);
void* map_get(HashMap* map,char* key);
void* map_remove(HashMap* map,char*key);
int map_size(HashMap* map);
void map_empty(HashMap* map);
void map_release(HashMap* map);


#endif