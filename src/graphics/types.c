#include "graphics/types.h"
#include "core/utils.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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
