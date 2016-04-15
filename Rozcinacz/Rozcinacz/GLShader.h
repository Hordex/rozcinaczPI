#ifndef GLSHADER_H
#define GLSHADER_H

#include "GL/glew.h"

/// <summary>
/// Loads the shader.
/// </summary>
/// <param name="vertex_path">The vertex_path.</param>
/// <param name="fragment_path">The fragment_path.</param>
/// <returns></returns>
GLuint LoadShader(const char *vertex_path, const char *fragment_path);

#endif