#include "main.h"

void memcpy(void *dest, void *src, u32 size) {
	u8* dst8 = (u8*)dest;
	u8* src8 = (u8*)src;

	while (size--)
		*dst8++ = *src8++;

	return;
}

void memset(void *dest, u32 filler, u32 size) {
    u8 *destc = (u8 *)dest;

    while(size--)
		*destc++ = filler;

	return;
}

void strcat(char* a, char* b) {
	while(*a != 0)
		a++;

	while(*b != 0)
		*a++ = *b++;

	*a = 0;
}

size_t strlen( const char* s ) {
	size_t rc = 0;
	while(s[rc])
		++rc;
	return rc;
}

int isspace(char c) {
	if (c == ' ' || c == '\n' || c == '\t')
		return 1;
	return 0;
}

int isalpha(char c) {
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return 1;
	return 0;
}

int isnum(char c) {
	if (c >= '0' && c <= '9')
		return 1;
	return 0;
}

int isalnum(char c) {
	if (isnum(c) || isalpha(c))
		return 1;
	return 0;
}

/* This implementation of strtok is shamelessly stolen from PDClib. */
char *strtok( char *s1, const char *s2 ) {
    static char * tmp = NULL;
    const char * p = s2;

    if ( s1 != NULL )
        tmp = s1;
    else {
        if ( tmp == NULL )
            return NULL;
        s1 = tmp;
    }

    while ( *p && *s1 ) {
        if ( *s1 == *p ) {
            ++s1;
            p = s2;
            continue;
        }
        ++p;
    }

    if ( ! *s1 )
        return ( tmp = NULL );

    tmp = s1;
    while ( *tmp ) {
        p = s2;
        while ( *p ) {
            if ( *tmp == *p++ ) {
                *tmp++ = '\0';
                return s1;
            }
        }
        ++tmp;
    }

    tmp = NULL;
    return s1;
}

