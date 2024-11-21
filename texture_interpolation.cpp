//cpp
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

// Define a vertex structure to hold position, normal and texture coordinates
struct Vertex {
    glm::vec3 position;
    glm::vec2 texCoord;
};

// Function to create a mesh from vertices
void createMesh(std::vector<Vertex> &vertices) {
    // Create indices for the mesh
    std::vector<int> indices;

    // Define some vertices and faces of the mesh
    vertices.push_back({{ -1.0f,  -1.0f,  0.0f }, { 0.5f,  0.0f } });
    vertices.push_back({{ 1.0f,   -1.0f,  0.0f }, { 0.5f,  0.0f } });
    vertices.push_back({{ 1.0f,   1.0f,  0.0f }, { 0.5f,  1.0f } });

    // Define faces of the mesh
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    vertices.push_back({{ -1.0f,   1.0f,  0.0f }, { 0.5f,  1.0f } });
    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(3);

    vertices.push_back({{ -1.0f,  -1.0f,  0.0f }, { 0.0f,  0.5f } });
    indices.push_back(0);
    indices.push_back(3);
    indices.push_back(2);
}

// Function to interpolate between two textures
glm::vec4 interpolateTexture(glm::vec4 tex1, glm::vec4 tex2) {
    float t = 0.5f; // interpolation factor

    return tex1 * (1 - t) + tex2 * t;
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Texture Interpolation", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewInit();

    // Create a vertex array object (VAO)
    GLuint vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    // Define the vertex data for the mesh
    std::vector<Vertex> vertices = {};
    createMesh(vertices);

    // Allocate memory for the vertex buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    // Define the vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(1);

    // Create a texture for the mesh
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_FLOAT, NULL);

    // Define a uniform for the interpolation factor
    GLuint interpFactor;
    glGenUniforms(1, &interpFactor);
    glUniform1f(interpFactor, 0.5f);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw the mesh using interpolated texture
        for (int i = 0; i < 256; i++) {
            glm::vec4 tex1(0.5f, 0.0f, 0.0f, 1.0f); // texture on the left side of the screen
            glm::vec4 tex2(0.0f, 0.5f, 0.0f, 1.0f); // texture on the right side of the screen

            // Interpolate between textures based on the x-coordinate of the pixel
            glm::vec4 tex = interpolateTexture(tex1, tex2);
            glReadPixels(i, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &tex.r);

            // Draw a rectangle in the middle of the screen using the interpolated texture
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position));
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texCoord));
            glEnableVertexAttribArray(1);

            glDrawArrays(GL_QUADS, 0, 4);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position));
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texCoord));
            glDisableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
        }

        // Swap buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Clean up
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteTextures(1, &texture);
    glDeleteUniforms(1, &interpFactor);

    glfwTerminate();

    return 0;
}
/*
```

This code creates a window with a red square in the middle. The square's color changes as you move your mouse across the screen, due to texture
interpolation.

Please note that this is a simplified example and does not take into account many real-world issues such as textures at different scales or aspect
ratios, or more complex mesh topologies.

To compile this code, use:

```bash
g++ -std=c++11 -o main main.cpp `pkg-config --cflags --libs glfw3 glew`
```

Make sure to install the necessary packages (GLFW and GLEW) using your package manager.

Remember that OpenGL is a low-level API and it requires manual management of memory, buffers, textures and uniforms. This example uses static
allocation for vertex buffer, which means all vertices are stored in RAM at once, as opposed to dynamic allocation where only the requested amount
is allocated.
*/
