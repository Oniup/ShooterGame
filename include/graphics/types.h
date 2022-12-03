#ifndef __SHOOTER_GRAPHICS_TYPES_H__
#define __SHOOTER_GRAPHICS_TYPES_H__

typedef struct Shader Shader;
typedef struct Texture Texture;
typedef struct Vertex Vertex;

typedef struct Window Window;

Window* sh_window_create(int width, int height, const char* title);

#endif // __SHOOTER_GRAPHICS_TYPES_H__