#include "anyTypeHashMap.h"

int hash(const char* key) {
	int hash = 0;
	int i = 0;
	while (key[i] != 0) {
		hash += key[i];
		i++;
	}
	return hash % MAX_TABLE_LENGTH;
}

void copy(const void* des, const void* src, unsigned long long size) {
	char* d = des;
	char* s = src;
	while (size-- > 0) {
		*d++ = *s++;
	}
}

unsigned long long lenStr(const char* s) {
	unsigned long long len = 0;
	while (s[len] != '\0') {
		len++;
	}
	return len;
}

int isEqual(const char* s1, const char* s2) {
	int i = 0;
	while (s1[i] != '\0') {
		if (s1[i] != s2[i]) {
			return 0;
		}
		i++;
	}
	if (s1[i] != s2[i]) {
		return 0;
	}
	else {
		return 1;
	}
}

hashMapPtr createHashMap() {
	hashMapPtr map = (hashMapPtr)malloc(sizeof(hashMap));
	map->size = 0;
	map->buckets = (Node**)calloc(MAX_TABLE_LENGTH, sizeof(NodePtr));
	return map;
}

int mapSet(const hashMapPtr map, const char* key, const void* value, int size) {
	int idx = hash(key);
	if (map->buckets[idx] == 0) {
		NodePtr node = (NodePtr)malloc(sizeof(Node));
		if (node != NULL) {
			node->key = (const char*)malloc(lenStr(key) * sizeof(char));
			if (node->key != NULL) {
				copy(node->key, key, (lenStr(key) + 1) * sizeof(char));
				node->value = malloc(size);
				if (node->value != NULL) {
					copy(node->value, value, size);
				}
				else {
					printf("no more memory for use!\n");
					exit(1);
				}
				node->next = NULL;
				map->buckets[idx] = node;
				map->size++;
				return 1;
			}
			else {
				printf("no more memory for use!\n");
				exit(1);
			}
		}
		else {
			printf("no more memory for use!\n");
			exit(1);
		}
	}
	else {
		NodePtr current = map->buckets[idx];
		if (isEqual(current->key, key) == 1) {
			free(current->value);
			current->value = malloc(size);
			if (current->value != NULL) {
				copy(current->value, value, size);
			}
			else {
				printf("no more memory for use!\n");
				exit(1);
			}
			return 2;
		}
		else {
			while (current->next != NULL) {
				current = current->next;
				if (isEqual(current->key, key) == 1) {
					free(current->value);
					current->value = malloc(size);
					if (current->value != NULL) {
						copy(current->value, value, size);
					}
					else {
						printf("no more memory for use!\n");
						exit(1);
					}
					return 2;
				}
			}
		}
		NodePtr node = (NodePtr)malloc(sizeof(Node));
		if (node != NULL) {
			node->key = (const char*)malloc(lenStr(key) * sizeof(char));
			if (node->key != NULL) {
				copy(node->key, key, (lenStr(key) + 1) * sizeof(char));
				node->value = malloc(size);
				if (node->value != NULL) {
					copy(node->value, value, size);
				}
				else {
					printf("no more memory for use!\n");
					exit(1);
				}
				node->next = NULL;
				current->next = node;
				return 1;
			}
			else {
				printf("no more memory for use!\n");
				exit(1);
			}
		}
		else {
			printf("no more memory for use!\n");
			exit(1);
		}

	}
}


int mapGet(const hashMapPtr map, const char* key, void** dst) {
	int idx = hash(key);
	if (map->buckets[idx] != 0) {
		NodePtr current = map->buckets[idx];
		while (isEqual(current->key, key) != 1) {
			if (current->next == NULL) {
				return 0;
			}
			else {
				current = current->next;
			}
		}
		*dst = current->value;
		return 1;
	}
	else {
		return 0;
	}
}

int mapDelete(const hashMapPtr map, const char* key) {
	int idx = hash(key);
	if (map->buckets[idx] != 0) {
		NodePtr current = map->buckets[idx];
		if (isEqual(current->key, key) == 1) {
			if (current->next == NULL) {
				free(current);
				map->buckets[idx] = NULL;
				map->size--;
				return 1;
			}
			else {
				NodePtr tmp = current;
				map->buckets[idx] = current->next;
				free(tmp);
				map->size--;
				return 1;
			}
		}
		while (isEqual(current->next->key, key) != 1) {
			if (current->next->next == NULL) {
				return 0;
			}
			else {
				current = current->next;
			}
		}
		if (current->next->next) {
			NodePtr tmp = current->next;
			current->next = current->next->next;
			free(tmp);
			map->size--;
			return 1;
		}
		else {
			free(current->next);
			current->next = NULL;
			map->size--;
			return 1;
		}
	}
	else {
		return 0;
	}
}

void mapClean(const hashMapPtr map) {
	for (int i = 0; i < MAX_TABLE_LENGTH; i++) {
		if (map->buckets[i] != NULL) {
			NodePtr current = map->buckets[i];
			while (current->next) {
				NodePtr tmp = current->next;
				free(current);
				current = tmp;
			}
			free(current);
			map->buckets[i] = NULL;
		}
	}
	map->size = 0;
}

int mapHas(const hashMapPtr map, const char* key) {
	int idx = hash(key);
	if (map->buckets[idx] != NULL) {
		NodePtr current = map->buckets[idx];
		if (isEqual(current->key, key) == 1) {
			return 1;
		}
		else {
			while (isEqual(current->key, key) != 1) {
				if (current->next == NULL) {
					return 0;
				}
				else {
					current = current->next;
				}
			}
			return 1;
		}
	}
	else {
		return 0;
	}
}

void mapDestory(const hashMapPtr map) {
	free(map->buckets);
	free(map);
}

