#pragma once

// if a file needs access to OpenGL or GLFW,
// include this

#define GL_SILENCE_DEPR
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
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

