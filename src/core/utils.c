#include "core/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct onipString {
    char* str;
};

onipString* onip_str(const char* str) {
    onipString* string = (onipString*)malloc(sizeof(onipString));
    size_t length = strlen(str);

    string->str = (char*)malloc(sizeof(char*) * length);
    strncpy(string->str, str, length);
    string->str[length] = '\0';

    return string;
}

void onip_str_free(onipString* str) {
    free(str->str);
    free(str);
}

const char* onip_str_char(onipString* str) {
    return (const char*)str->str;
}

onipString* onip_str_set(onipString* str, const char* newStr) {
    free(str->str);
    size_t length = strlen(newStr);
    str->str = (char*)malloc(sizeof(char*) * length);
    strncpy(str->str, newStr, length);
    str->str[length] = '\0';
    return str;
}

onipString* onip_str_copy(const onipString* str) {
    return onip_str(str->str);
}

onipString* onip_str_append(onipString* str, const char* append) {
    if (str != NULL) {
        if (str->str != NULL) {
            size_t currentLength = strlen(str->str);
            size_t appendLength = strlen(append);
            str->str = (char*)realloc(str->str, sizeof(char*) * (currentLength + appendLength));
            assert(str->str && "Failed to append string");

            memcpy(str->str + currentLength, append, currentLength + appendLength);
            str->str[currentLength + appendLength] = '\0';
        }
        else {
            str = onip_str_set(str, append);
        }
    }
    else {
        str = onip_str(append);
    }
    return str;
}

size_t onip_str_len(const onipString* str) {
    return strlen(str);
}