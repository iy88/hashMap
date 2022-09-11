#ifndef MAP_H
#define MAP_H
#include <stdio.h>
#include <stdlib.h>
#define MAX_TABLE_LENGTH 50
#include <string.h>
typedef struct n {
    char* key;
    void* value;
    struct n* next;
} Node;

typedef Node** hashMap;

typedef Node* NodePtr;

int hash(char* key);

hashMap createHashMap();

int set(hashMap map, char* key, void* value, int size);

void* get(hashMap map, char* key);

int delete(hashMap map, char* key);

int clean(hashMap map);

int has(hashMap map, char* key);
#endif