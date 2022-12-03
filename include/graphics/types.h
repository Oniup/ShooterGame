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

onipShader* onip_shader_create(const char* fragment_path, const char* vertex_path);
void onip_shader_free(onipShader* shader);
uint32_t onip_shader_id(onipShader* shader);

onipTexture* onip_texture_create(const char* image_path, bool flip, bool linear_filtering);
void onip_texture_free(onipTexture* texture);
uint32_t onip_texture_id(onipTexture* texture);
int onip_texture_width(onipTexture* texture);
int onip_texture_height(onipTexture* texture);

#endif // __ONIP_GRAPHICS_TYPES_H__