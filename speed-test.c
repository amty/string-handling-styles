#include <stdio.h>

int parse_line(char *s, int *uid, int *gid);

int main() {
	int uids = 0;
	int gids = 0;
	char buf[64];
	FILE *f = fopen("data.txt", "r");
	if(f == NULL) {
		perror("Unable to open data file");
		return 1;
	}
	while(fgets(buf, 64, f) != NULL) {
		int uid, gid;
		if(parse_line(buf, &uid, &gid)) {
			uids += uid;
			gids += gid;
		} else {
			printf("error\n");
			return 1;
		}
	}
	printf("%d, %d\n", uids, gids);
	return 0;
}
