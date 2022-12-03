#include "graphics/types.h"
#include "core/utils.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

struct onipShader {
    uint32_t tag;
    uint32_t id;
};

struct onipTexture {
    uint32_t tag;
    uint32_t id;
    int width;
    int height;
};

struct onipWindow {
    GLFWwindow* native;
    int width;
    int height;
    onipString* name;
};

static onipWindow* WINDOW = NULL;

onipWindow* onip_window_create(int width, int height, const char* title, bool fullscreen) {
    if (WINDOW == NULL) {
        glfwInit();

        WINDOW = (onipWindow*)malloc(sizeof(onipWindow));
        WINDOW->width = width;
        WINDOW->height = height;
        WINDOW->name = onip_str(title);

        glfwWindowHint(GLFW_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_VERSION_MINOR, 5);
        // Forgot the window hint to be able to run this on mac rip

        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);
        if (fullscreen) {
            WINDOW->native = glfwCreateWindow(width, height, title, monitor, NULL);
        }
        else {
            WINDOW->native = glfwCreateWindow(width, height, title, NULL, NULL);
        }

        glfwMakeContextCurrent(WINDOW->native);
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        glViewport(0, 0, WINDOW->width, WINDOW->height);

        vec2 pos = {
            (vidmode->width - WINDOW->width) * 0.5f,
            (vidmode->height - WINDOW->height) * 0.5f
        };
        glfwSetWindowPos(WINDOW->native, pos[0], pos[1]);
    }

    return WINDOW;
}

void onip_window_free() {
    onip_str_free(WINDOW->name);
    glfwDestroyWindow(WINDOW->native);
    glfwTerminate();

    free(WINDOW);
    WINDOW = NULL;
}

onipWindow* onip_window_get() {
    return WINDOW;
}

bool onip_window_closing() {
    return glfwWindowShouldClose(WINDOW->native);
}

void onip_window_refresh() {
    glfwSwapBuffers(WINDOW->native);
    glfwPollEvents();
    // TODO: Camera stuff here
    glfwGetWindowSize(WINDOW->native, &WINDOW->width, &WINDOW->height);
    glViewport(0, 0, WINDOW->width, WINDOW->height);
    glClear(GL_COLOR_BUFFER_BIT);
}




onipShader* onip_shader_create(const char* fragment_path, const char* vertex_path) {
    uint32_t shaders[] = { 0, 0 };

    for (int i = 0; i < 2; i++) {
        FILE* file = fopen(i == 0 ? fragment_path : vertex_path, "rb");
        ONIP_ASSERT_FMT(file, "failed to open file [%s]", i == 0 ? fragment_path : vertex_path);

        fseek(file, 0, SEEK_END);
        size_t length = (size_t)ftell(file);
        fseek(file, 0, SEEK_SET);
        char* source = (char*)malloc(sizeof(char*) * length);

        fread(source, sizeof(char), length, file);
        fclose(file);
        ONIP_ASSERT_FMT(source, "failed to read file [%s]", i == 0 ? fragment_path : vertex_path);

        shaders[i] = glCreateShader(GL_FRAGMENT_SHADER + i);
        glShaderSource(shaders[i], 1, (const char* const*)source, NULL);
        glCompileShader(shaders[i]);
        free(source);

        int result;
        glGetShaderiv(shaders[i], GL_COMPILE_STATUS, &result);
        if (!result) {
            glGetShaderiv(shaders[i], GL_INFO_LOG_LENGTH, &result);
            char* message = (char*)malloc(sizeof(char*) * result);
            glGetShaderInfoLog(shaders[i], result, &result, message);
            ONIP_ASSERT_FMT(result, "failed to compile shader [%s]", i == 0 ? fragment_path : vertex_path);
        }
    }

    onipShader* shader = (onipShader*)malloc(sizeof(onipShader));
    shader->id = glCreateProgram();
    shader->tag = (uint32_t)rand();
    glAttachShader(shader->id, shaders[0]);
    glAttachShader(shader->id, shaders[1]);
    glLinkProgram(shader->id);

    int result;
    glGetProgramiv(shader->id, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramiv(shader->id, GL_INFO_LOG_LENGTH, &result);
        char* message = (char*)malloc(sizeof(char*) * result);
        glGetProgramInfoLog(shader->id, result, &result, message);
        ONIP_ASSERT_FMT(result, "failed to link shaders to program\n\tfrag:\t[%s]\n\tvert:\t[%s]", fragment_path, vertex_path);
    }

    return shader;
}

void onip_shader_free(onipShader* shader) {
    glDeleteProgram(shader->id);
    free(shader);
}

uint32_t onip_shader_id(onipShader* shader) {
    ONIP_ASSERT(shader, "shader is NULL, cannot get shader id");
    return shader->id;
}




onipTexture* onip_texture_create(const char* image_path, bool flip, bool linear_filtering) {
    return NULL;
}

void onip_texture_free(onipTexture* texture) {
}

uint32_t onip_texture_id(onipTexture* texture) {
    ONIP_ASSERT(texture, "texture is NULL, cannot get texture id");
    return texture->id;
}

int onip_texture_width(onipTexture* texture) {
    ONIP_ASSERT(texture, "texture is NULL, cannot get texture width");
    return texture->width;
}

int onip_texture_height(onipTexture* texture) {
    ONIP_ASSERT(texture, "texture is NULL, cannot get texture height");
    return texture->height;
}