#include "BitmapRenderer.h"

#include <iostream>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <ShaderProgram/ShaderProgram.h>

/// <summary>
/// The coordinates and texture coordinates of the canvas vertices.
/// </summary>
const GLfloat canvasVertexData[]
{
    -1, -1, 0, 0,
    1, -1, 1, 0,
    1, 1, 1, 1,
    -1, 1, 0, 1
};

/// <summary>
/// The per-triangle element indices of the canvas mesh.
/// </summary>
const GLuint canvasElementData[]
{
    0, 1, 2,
    0, 3, 2
};

BitmapRenderer::BitmapRenderer (size_t width, size_t height, std::vector<uint8_t>&& bitmap)
    : width (width), height (height), bitmap (std::move (bitmap))
{
    if (this->bitmap.size () != 3 * width * height)
    {
        std::cerr << "Size of image data storage does not match canvas dimensions\n";
        exit (EXIT_FAILURE);
    }
}

void BitmapRenderer::Render () const
{
    GLFWwindow* window;

    if (glfwInit () == GLFW_FALSE)
    {
        std::cerr << "Failed to initialize GLFW\n";
        exit (EXIT_FAILURE);
    }

    window = glfwCreateWindow (width, height, "", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cerr << "Failed to create a GLFW window\n";
        exit (EXIT_FAILURE);
    }

    glfwMakeContextCurrent (window);

    if (glewInit () != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW\n";
        exit (EXIT_FAILURE);
    }

    GLuint vao, vbo, ebo, texture;
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);
    glGenBuffers (1, &vbo);
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData (GL_ARRAY_BUFFER, sizeof (canvasVertexData), canvasVertexData, GL_STATIC_DRAW);
    glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof (GLfloat), reinterpret_cast<void*> (0));
    glEnableVertexAttribArray (0);
    glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof (GLfloat), reinterpret_cast<void*>(2 * sizeof (GL_FLOAT)));
    glEnableVertexAttribArray (1);
    glGenBuffers (1, &ebo);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof (canvasElementData), canvasElementData, GL_STATIC_DRAW);
    glActiveTexture (GL_TEXTURE0);
    glGenTextures (1, &texture);
    glBindTexture (GL_TEXTURE_2D, texture);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap.data ());
    glGenerateMipmap (GL_TEXTURE_2D);

    ShaderProgram canvasShader = ShaderProgram::CreateBasicShaderProgram ("Canvas");
    canvasShader.UseProgram ();
    canvasShader.SetUniformSampler ("canvasTexture", 0);

    glClearColor (0, 0, 0, 1);
    glClear (GL_COLOR_BUFFER_BIT);
    glDrawElements (GL_TRIANGLES, 6, GL_UNSIGNED_INT, reinterpret_cast<void*> (0));
    glfwSwapBuffers (window);

    do
    {
        glfwWaitEvents ();
    } while (!glfwWindowShouldClose (window));

    glDeleteTextures (1, &texture);
    glDeleteBuffers (1, &ebo);
    glDeleteBuffers (1, &vbo);
    glDeleteVertexArrays (1, &vao);

    glfwDestroyWindow (window);
    glfwTerminate ();
}
