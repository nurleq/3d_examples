/*
To create a 3D scene where the background doesn't distract from the foreground, you can use various techniques:

1. **Use a skybox**: A skybox is a large, spherical image that surrounds the entire scene, creating a sense of
depth and environment. You can pre-render a single image of the sky with a consistent color and texture to
create a uniform background.
2. **Set a clear background color**: In OpenGL, you can set a clear background color using `glClearColor()`.
This will help reduce distractions from the background.
3. **Use a gradient or texture for the background**: Instead of a solid color, use a gradient or texture that
transitions smoothly from one color to another, creating a sense of depth and distance.
4. **Add some ambient occlusion**: Ambient occlusion (AO) is a technique that simulates the way light interacts
with objects in the scene. By adding AO to your background, you can create a more realistic and immersive
environment.

Here's an example of how you could implement these techniques in C++:
*/
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Define some constants for the skybox texture
const int SKYBOX_SIZE = 256;
const float SKYBOX_FOV = 180.0f;

// Define a class to represent the scene
class Scene {
public:
    // Function to render the background using a skybox
    void renderSkybox() {
        // Load the skybox texture
        unsigned char* skyboxTexture = new unsigned char[SKYBOX_SIZE * SKYBOX_SIZE * 3];
        for (int i = 0; i < SKYBOX_SIZE; ++i) {
            for (int j = 0; j < SKYBOX_SIZE; ++j) {
                // Generate a random color for each pixel
                skyboxTexture[(i * SKYBOX_SIZE * 3) + (j * 3)] = rand() % 256;
                skyboxTexture[(i * SKYBOX_SIZE * 3) + (j * 3) + 1] = rand() % 256;
                skyboxTexture[(i * SKYBOX_SIZE * 3) + (j * 3) + 2] = rand() % 256;
            }
        }

        // Set up the skybox texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SKYBOX_SIZE, SKYBOX_SIZE, 0, GL_RGB, GL_UNSIGNED_BYTE,
skyboxTexture);

        // Generate a quad to render the skybox
        Vertex quadVertices[4];
        quadVertices[0].x = -1.0f; quadVertices[0].y = -1.0f; quadVertices[0].z = 1.0f;
        quadVertices[1].x = 1.0f; quadVertices[1].y = -1.0f; quadVertices[1].z = 1.0f;
        quadVertices[2].x = 1.0f; quadVertices[2].y = 1.0f; quadVertices[2].z = 1.0f;
        quadVertices[3].x = -1.0f; quadVertices[3].y = 1.0f; quadVertices[3].z = 1.0f;

        // Set up the material for the skybox
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluPerspective(2 * SKYBOX_FOV, 1, 0.01f, 10000.0f);

        glMatrixMode(GL_MODELVIEW);
        glDisable(GL_DEPTH_TEST);

        // Render the skybox
        glBegin(GL_QUADS);
        for (int i = 0; i < 4; ++i) {
            glVertex3fv(&quadVertices[i]);
        }
        glEnd();

        // Clean up
        delete[] skyboxTexture;
    }

    // Function to render the scene using OpenGL
    void renderScene() {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set up the lighting
        glEnable(GL_LIGHTING);
        glLightfv(GL_LIGHT0, GL_POSITION, new float[] {0.0f, 1.0f, 2.0f});

        // Render the skybox
        renderSkybox();

        // Set up the foreground objects
        Vertex foregroundVertices[4];
        foregroundVertices[0].x = -1.0f; foregroundVertices[0].y = -1.0f; foregroundVertices[0].z = 2.0f;
        foregroundVertices[1].x = 1.0f; foregroundVertices[1].y = -1.0f; foregroundVertices[1].z = 2.0f;
        foregroundVertices[2].x = 1.0f; foregroundVertices[2].y = 1.0f; foregroundVertices[2].z = 2.0f;
        foregroundVertices[3].x = -1.0f; foregroundVertices[3].y = 1.0f; foregroundVertices[3].z = 2.0f;

        // Render the foreground objects
        glBegin(GL_QUADS);
        for (int i = 0; i < 4; ++i) {
            glVertex3fv(&foregroundVertices[i]);
        }
        glEnd();
    }
};

// Create a Scene object and render it using OpenGL
int main() {
    Scene scene;

    while (!glfwWindowShouldClose()) {
        // Render the scene
        scene.renderScene();

        // Poll events
        glfwPollEvents();
    }

    return 0;
}
/*
This code creates a basic 3D scene with a skybox and foreground objects. The skybox is rendered using a quad,
and the lighting is set up to create a sense of depth and distance.
*/