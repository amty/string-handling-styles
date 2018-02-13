#include <string.h>
#include <stdio.h>
#include <ctype.h>

struct substr {
	char *str;
	unsigned len;
};

struct substr substr_from_str(char *s) {
	return (struct substr){.str = s, .len = strlen(s)};
}

int substr_to_int(struct substr s, int *num) {
	int ret = 0;
	int sign = (s.str[0] == '-');
	int start = sign ? 1 : 0;
	if(start >= s.len) { // strings like "" or "-" are error strings
		return 0;
	}
	for(int i = start; i < s.len; i ++) {
		char c = s.str[i];
		if(!isdigit(c)) {
			return 0;
		}
		ret *= 10;
		ret += c - '0';
	}
	*num = sign ? - ret : ret;
	return 1;
}

static inline struct substr trim_spaces_back(struct substr s) {
	for(int i = s.len-1; i >= 0; i --) {
		if(!isspace(s.str[i])) {
			s.len = i + 1;
			return s;
		}
	}
	return (struct substr){.str = s.str, .len = 0};
}
static inline struct substr cut_number_back(struct substr *s) {
	for(int i = s->len-1; i >= 0; i --) {
		if(!isdigit(s->str[i]) && s->str[i] != '-') {
			struct substr ret = {
				.str = s->str + i + 1,
				.len = s->len - i - 1
			};
			s->len = i + 1;
			return ret;
		}
	}
	return (struct substr){NULL, 0};
}
struct substr parse_int_back(struct substr *s) {
	*s = trim_spaces_back(*s);
	return cut_number_back(s);
}

int parse_line(char *str, int *uid, int *gid) {
	struct substr line = substr_from_str(str);
	struct substr gid_str = parse_int_back(&line);
	if(gid_str.str == NULL || gid_str.len == 0) {
		goto SPOOL_READ_ERROR;
	}
	struct substr uid_str = parse_int_back(&line);
	if(uid_str.str == NULL || uid_str.len == 0) {
		goto SPOOL_READ_ERROR;
	}
	return substr_to_int(uid_str, uid) && substr_to_int(gid_str, gid);
SPOOL_READ_ERROR:
	return 0;
}
