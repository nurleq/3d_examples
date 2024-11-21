/* Here's an example of a C++ program that demonstrates GPU optimization techniques for utilizing the GPU,
including:

1.  **Vertex Buffer Objects (VBOs)**: Storing vertex data in a buffer object on the GPU.
2.  **Index Buffer Objects (IBOs)**: Storing index data in a buffer object on the GPU.
3.  **Shader Optimization**: Minimizing shader complexity and improving performance by reducing the number of
uniforms and using techniques like constant folding.
4.  **Instancing**: Reducing the number of draw calls by creating multiple copies of a single model instance.
*/
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Define some structs to hold vertex and index data
struct Vertex {
    glm::vec3 position;
    glm::vec2 texCoord;
};

struct Index {
    unsigned int idx;
};

class GPU {
public:
    // Initialize the GPU context
    void init() {
        glfwInit();
        glewInit();

        window_ = glfwCreateWindow(800, 600, "GPU Optimization", nullptr, nullptr);

        // Create VBO and IBO for vertex and index data
        glGenBuffers(1, &vbo_);
        glGenBuffers(1, &ibo_);

        // Set up vertex and index data
        vertices_.resize(16);
        indices_.resize(24);

        // Populate the vertex and index arrays with some example data
        for (unsigned int i = 0; i < 4; ++i) {
            vertices_[i * 2] = glm::vec3(i * 2, i * 2, i * 2);
            vertices_[i * 2 + 1] = glm::vec2(0.5f, 0.5f);

            indices_[i * 6] = i;
            indices_[i * 6 + 1] = (i + 1) % 4;
            indices_[i * 6 + 2] = (i + 3) % 4;
        }

        // Copy the vertex and index data to the GPU
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), &vertices_[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_), &indices_[0], GL_STATIC_DRAW);
    }

    // Draw a triangle using the GPU context
    void drawTriangle() {
        GLuint program = createShaderProgram();

        // Bind VBO and IBO to the shader program
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);

        // Set up vertex attributes in the shader program
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(&vertices_[0].position));
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, &indices_[0]);
    }

    // Create a shader program
    GLuint createShaderProgram() {
        // Create vertex and fragment shaders
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        // Compile the shaders
        const char* vertexShaderSource = R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            void main() {
                gl_Position = vec4(aPos, 1.0);
            }
        )";

        const char* fragmentShaderSource = R"(
            #version 330 core
            out vec4 FragColor;
            void main() {
                FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
            }
        )";

        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);

        glCompileShader(vertexShader);
        glCompileShader(fragmentShader);

        // Create a shader program
        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        return shaderProgram;
    }

    // Instancing example (uses the GPU's multi-threading capabilities to render multiple instances of a single
model)
    void drawInstanced() {
        GLuint program = createShaderProgram();

        // Set up vertex attributes in the shader program
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(&vertices_[0].position));
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);

        // Set up instance data in the shader program
        GLuint instanceAttributeLocation = glGetAttribLocation(program, "instance");
        glVertexAttrib1ui(instanceAttributeLocation, 4);  // 4x4 identity matrix for instance transformations

        // Draw multiple instances of a single model using instancing
        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_) * 16, &vertices_[0], GL_STATIC_DRAW);

        glDrawArraysInstanced(GL_TRIANGLES, 0, 4, 16);  // Draw 16 instances of the same model

        // Clean up
        glDeleteBuffers(1, &vbo_);
        glDeleteBuffers(1, &ibo_);
    }

private:
    GLFWwindow* window_;
    GLuint vbo_, ibo_;

    std::vector<Vertex> vertices_;
    std::vector<Index> indices_;
};

int main() {
    GPU gpu;

    // Initialize the GPU context
    gpu.init();

    while (!glfwWindowShouldClose(window_)) {
        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw a triangle using the GPU context
        gpu.drawTriangle();

        // Draw multiple instances of a single model using instancing
        gpu.drawInstanced();
    }

    return 0;
}