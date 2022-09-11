#include "anyTypeHashMap.h"

int hash(char* key) {
	int hash = 0;
	int i = 0;
	while (key[i] != 0) {
		hash += key[i];
		i++;
	}
	return hash % MAX_TABLE_LENGTH;
}

void copy(void* des, void* src, unsigned long long size) {
	char* d = (char*)des;
	char* s = (char*)src;
	while (size-- > 0) {
		*d++ = *s++;
	}
}

unsigned long long lenStr(char* s) {
	unsigned long long len = 0;
	while (s[len] != '\0') {
		len++;
	}
	return len;
}

int isEqual(char* s1, char* s2) {
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


hashMap createHashMap() {
	hashMap map = (hashMap)calloc(MAX_TABLE_LENGTH, sizeof(NodePtr));
	return map;
}

int set(hashMap map, char* key, void* value, int size) {
	int idx = hash(key);
	if (map[idx] == 0) {
		NodePtr node = (NodePtr)malloc(sizeof(Node));
		if (node != NULL) {
			node->key = (char*)malloc(lenStr(key) * sizeof(char));
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
				map[idx] = node;
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
		NodePtr current = map[idx];
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
			node->key = (char*)malloc(lenStr(key) * sizeof(char));
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


void* get(hashMap map, char* key) {
	int idx = hash(key);
	if (map[idx] != 0) {
		NodePtr current = map[idx];
		while (isEqual(current->key, key) != 1) {
			if (current->next == NULL) {
				printf("the key[%s] doesn't exist\n", key);
				exit(1);
			}
			else {
				current = current->next;
			}
		}
		return current->value;
	}
	else {
		printf("the key[%s] doesn't exist\n", key);
		exit(1);
	}
}

int delete(hashMap map, char* key) {
	int idx = hash(key);
	if (map[idx] != 0) {
		NodePtr current = map[idx];
		if (isEqual(current->key, key) == 1) {
			if (current->next == NULL) {
				free(current);
				map[idx] = NULL;
				return 1;
			}
			else {
				NodePtr tmp = current;
				map[idx] = current->next;
				free(tmp);
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
			return 1;
		}
		else {
			free(current->next);
			current->next = NULL;
			return 1;
		}
	}
	else {
		return 0;
	}
}

int clean(hashMap map) {
	for (int i = 0; i < MAX_TABLE_LENGTH; i++) {
		if (map[i] != NULL) {
			free(map[i]);
			map[i] = NULL;
		}
	}
	return 1;
}

int has(hashMap map, char* key) {
	int idx = hash(key);
	if (map[idx] != NULL) {
		NodePtr current = map[idx];
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

