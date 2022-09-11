// main.cpp: 定义应用程序的入口点。
//

#include "main.h"

int main()
{
	hashMap myMap = createHashMap();
	for (int i = 97; i < 123; i++) {
		char c = i;
		char* s = malloc(2);
		if (s != NULL) {
			s[0] = c;
			s[1] = '\0';
			set(myMap, s, s, 2);
		}
		else {
			exit(1);
		}
	}
	// showHashMap(myMap);
	printf("has 'a': %d\n", has(myMap, "a"));
	set(myMap, "a", "b", 2);
	char* a = get(myMap, "a");
	printf("%s\n", (char*)a);
	clean(myMap);
	// showHashMap(myMap);
	printf("has 'a': %d\n", has(myMap, "a"));
	char c = getchar();
	return 0;
}
