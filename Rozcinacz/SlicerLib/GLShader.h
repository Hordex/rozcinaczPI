#ifndef GLSHADER_H
#define GLSHADER_H

#include "GL/glew.h"

/// <summary>
/// Loads the shader.
/// </summary>
/// <param name="vertex_path">The path to vertex shader.</param>
/// <param name="fragment_path">The path to fragment shader.</param>
/// <returns></returns>
GLuint LoadShader(const char *vertex_path, const char *fragment_path);

#endif