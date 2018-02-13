#include <stdio.h>
#include <stdlib.h>

int main() {
	int i;
	for(i = 1000000; i >= 0; i --) {
		char name[16];
		int name_len = rand() % 8 + 4;
		int j;
		for(j = 0; j < name_len; j ++) {
			name[j] = rand() % 26 + 'a';
		}
		name[j] = '\0';
		int uid = rand();
		int gid = rand();
		printf("%s %d %d\n", name, uid, gid);
	}
	return 0;
}
