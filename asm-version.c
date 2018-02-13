#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define Ustrlen strlen
#define Uatoi atoi

int parse_line(char *big_buffer, int *uid, int *gid) {
	char *p = big_buffer + Ustrlen(big_buffer);
	while (p > big_buffer && isspace(p[-1])) p--;
	*p = 0;
	if (!isdigit(p[-1])) goto SPOOL_FORMAT_ERROR;
	while (p > big_buffer && (isdigit(p[-1]) || '-' == p[-1])) p--;
	*gid = Uatoi(p);
	if (p <= big_buffer || *(--p) != ' ') goto SPOOL_FORMAT_ERROR;
	*p = 0;
	if (!isdigit(p[-1])) goto SPOOL_FORMAT_ERROR;
	while (p > big_buffer && (isdigit(p[-1]) || '-' == p[-1])) p--;
	*uid = Uatoi(p);
	if (p <= big_buffer || *(--p) != ' ') goto SPOOL_FORMAT_ERROR;
	*p = 0;
	return 1;
SPOOL_FORMAT_ERROR:
	return 0;
}
