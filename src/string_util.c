#include "string_util.h"
#include <stdio.h>
#include <math.h>        /* pow */
#include <string.h>      /* strcmp */
#include <stdlib.h>      /* qsort */

int str_t_fprint(str_t const * s, FILE * f)
{
	int r = 0;
	for(char * c = s->beg; c != s->end; ++c){
		if(*c == '\0')
			r = fprintf(f, "\\0");
		else if(*c == '\n')
			r = fprintf(f, "\\n");
		else
			r = fprintf(f, "%c", *c);
	}
	if(s->beg)
		fprintf(f, "\n");
	return r;
}

#if (defined __GNUC__) && !(defined __CYGWIN__)

char *strlwr(char *s)
{
	for (char *str = s; *str; ++str) {
		if (*str >= 'A' && *str <= 'Z') {
			*str += ('a' - 'A');
		}
	}
	return s;
}

char *strupr(char *s)
{
	for (char *str = s; *str; ++str) {
		if (*str >= 'a' && *str <= 'z') {
			*str -= ('a' - 'A');
		}
	}
	return s;
}

#endif	/*(defined __GNUC__) && !(defined __CYGWIN__)*/

/*@param unit 'K': KB, 'M':MB, 'G':GB, ' ':B*/
static double byte_to_mb_kb(size_t bytes, char * unit)
{
	if(!unit) return 0;

	if(bytes >= 1024 * 1024 && bytes < 1024 * 1024 * 1024){
		*unit = 'M';
		return bytes / (1024.0 * 1024);
	}
	else if(bytes >= 1024 * 1024 * 1024){
		*unit = 'G';
		return bytes / (1024.0 * 1024 * 1024);
	}
	else if(bytes >= 1024){
		*unit = 'K';
		return bytes / 1024.0;
	}
	else{
		*unit = ' ';
		return bytes / 1.0;
	}
}

char * byte_to_mb_kb_str_r(size_t bytes, char const * fmt, char * buff)
{
	if(!fmt) return buff;
	char c;
	double b = byte_to_mb_kb(bytes, &c);
	snprintf(buff, 64, fmt, b, c);
	return buff;
}
/*@param fmt: "%-.2f %cB*/
char const * byte_to_mb_kb_str(size_t bytes, char const * fmt)
{
	static char buff[64] = "";
	return byte_to_mb_kb_str_r(bytes, fmt, buff);
}


char const * strnrchr(char const * buf, int sz, char ch)
{
	for(char const * p = buf + sz - 1; p != buf - 1; --p) {
		if(*p == ch)
			return p;
	}
	return 0;
}

/* FIXME: overflow */
int myatoi(char const * str, size_t len)
{
	if(!(str && str[0] != '\0' && len > 0))
		return 0;

	int f = 0;
	if(str[0] == '+' || str[0] == '-'){
		if(str[0] == '-')
			f = 1;
		++str;
		--len;
	}

	int ints[64];
	int i = 0;
	for(char const * p = str; p != str + len; ++p){
		if(!(*p >= '0' && *p <= '9'))
			break;
		ints[i++] = *p - '0';
	}

	int r = 0;
	for(int j = 0; j < i; ++j){
		r += ints[j] * pow(10, i - j - 1);
	}
	return f? -r : r;
}

static int compare_strs(const void* a, const void* b)
{
	return strcmp(*(const char **)a, *(const char **)b);
}

void strutil_qsort(char ** strs, int size)
{
	return qsort(strs, size, sizeof(char *), compare_strs);
}

char const * strutil_findmax(char const * str, char ** strs, int size)
{
	qsort(strs, size, sizeof(char *), compare_strs);

	for(int i = 0; i < size; ++i){
		if(strncmp(strs[i], str, strlen(strs[i])) == 0 && i > 0)
				return strs[i - 1];
	}
	return 0;
}

