// main.cpp: 定义应用程序的入口点。
//

#include "main.h"

int main()
{
	hashMapPtr myMap = createHashMap();
	for (int i = 97; i < 123; i++) {
		char c = i;
		char* s = malloc(2);
		if (s != NULL) {
			s[0] = c;
			s[1] = '\0';
			mapSet(myMap, s, s, 2);
		}
		else {
			exit(1);
		}
	}
	printf("map size: %d\n", myMap->size);
	printf("has 'a': %d\n", mapHas(myMap, "a"));
	mapSet(myMap, "a", "b", 2);
	char** a = malloc(sizeof(char *));
	mapGet(myMap, "a", a);
	printf("%s\n", *a);
	mapClean(myMap);
	printf("map size: %d\n", myMap->size);
	printf("has 'a': %d\n", mapHas(myMap, "a"));
	mapDestory(myMap);
	getchar();
	return 0;
}
