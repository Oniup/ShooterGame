#ifndef __SHOOTER_CORE_UTILS_H__ 
#define __SHOOTER_CORE_UTILS_H__

#include <stdint.h>

typedef struct onipString onipString;

onipString* onip_str(const char* str);
void onip_str_free(onipString* str);

const char* onip_str_char(onipString* str);

onipString* onip_str_set(onipString* str, const char* newStr);
onipString* onip_str_copy(const onipString* str);
onipString* onip_str_append(onipString* str, const char* append);
size_t onip_str_len(const onipString* str);

#endif // __SHOOTER_CORE_UTILS_H__