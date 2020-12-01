#ifndef CAOS_STRINGS_H
#define CAOS_STRINGS_H

#include <stdlib.h>

struct String {
    char* data;
    size_t length;
    size_t capacity;
};

void string_init(struct String* string, const char* initial);
void string_free(struct String* string);
void string_append(struct String* string, int c);

#endif
