#ifndef __ONIP_GRAPHICS_TYPES_H__
#define __ONIP_GRAPHICS_TYPES_H__

#include <stdint.h>
#include <cglm/cglm.h>
#include <stdbool.h>

typedef struct onipShader onipShader;
typedef struct onipTexture onipTexture;
typedef struct onipWindow onipWindow;

typedef struct onipVertex {
    vec3 position;
    vec2 uv;
    vec3 normal;
    float textureID;
} onipVertex;

onipWindow* onip_window_create(int width, int height, const char* title, bool fullscreen);
void onip_window_free();

onipWindow* onip_window_get();
bool onip_window_closing();
void onip_window_refresh();

#endif // __ONIP_GRAPHICS_TYPES_H__