#ifndef __SHOOTER_CORE_UTILS_H__ 
#define __SHOOTER_CORE_UTILS_H__

#include <stdint.h>

#ifndef NDEBUG
    #define ONIP_ASSERT_FMT(condition, format, ...) {\
        if (!condition) {\
            printf(format, __VA_ARGS__);\
            exit(-1);\
        }\
    }\

    #define ONIP_ASSERT(condition, message) {\
        if (!condition) {\
            printf(message);\
            exit(-1);\
        }\
    }\

#else
    #define ONIP_ASSERT_FMT(condition, format, ...)
    #define ONIP_ASSERT(condition, message)

#endif // NDEBUG 

typedef struct onipString onipString;

onipString* onip_str(const char* str);
void onip_str_free(onipString* str);

const char* onip_str_char(onipString* str);

onipString* onip_str_set(onipString* str, const char* new_str);
onipString* onip_str_copy(const onipString* str);
onipString* onip_str_append(onipString* str, const char* append);
size_t onip_str_len(const onipString* str);

#endif // __SHOOTER_CORE_UTILS_H__