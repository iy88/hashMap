#ifndef MAP_H
#define MAP_H
#include <stdio.h>
#include <stdlib.h>
#define MAX_TABLE_LENGTH 50
#include <string.h>
typedef struct n {
	const char * key;
	unsigned long long size;
	void* value;
	struct n* next;
} Node;

//typedef Node** hashMap;

typedef struct {
	unsigned long long size;
	Node** buckets;
} hashMap;

typedef Node* NodePtr;

typedef hashMap* hashMapPtr;

int hash(const char * key);

hashMapPtr createHashMap();

int mapSet(const hashMapPtr map, const char * key, void* value, int size);

void* mapGet(const hashMapPtr map, const char * key);

int mapDelete(const hashMapPtr map, const char * key);

void mapClean(const hashMapPtr map);

int mapHas(const hashMapPtr map, const char * key);

void mapDestory(const hashMapPtr);

#endif