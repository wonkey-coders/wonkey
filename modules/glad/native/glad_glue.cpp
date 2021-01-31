#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glad_glue.h"

int gladLoadGLLoaderGLFW(void) {
    return gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
}