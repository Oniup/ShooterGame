#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>

#include "core/utils.h"
#include "graphics/types.h"
#include "graphics/handler.h"

int main(int argc, char** argv) {
    onipWindow* window = onip_window_create(1280, 720, "This is a test", false);

    while (!onip_window_closing()) {
        onip_window_refresh();
    }

    onip_window_free();
    return 0;
}