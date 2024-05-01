#pragma once

#define GL_SILENCE_DEPR
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#define GL_CHECK() \
do { \
    GLenum error = glGetError(); \
    if (error != GL_NO_ERROR) { \
        fprintf(stderr, "OpenGL Error (%s:%d): %d\n", __FILE__, __LINE__, error); \
    } \
} while (false)
