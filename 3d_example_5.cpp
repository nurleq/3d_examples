#include <SFML/Graphics.hpp>
#include <vector>

// Define a 3D point structure
struct Point {
    float x, y, z;

    // Constructor to initialize point with coordinates
    Point(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}

    // Function to draw the point as a sphere in SFML window
    void draw(sf::RenderWindow& window) {
        sf:: SphereShape sphere(2);
        sphere.setPosition(x, y, z);
        window.draw(sphere);
    }
};

// Define a Polygon class for modeling and transformations
class Polygon {
private:
    std::vector<Point> vertices;

public:
    // Constructor to initialize polygon with points
    Polygon(const std::vector<Point>& vertices) : vertices(vertices) {}

    // Function to draw the polygon in SFML window
    void draw(sf::RenderWindow& window) {
        for (size_t i = 0; i < vertices.size(); ++i) {
            Point v1 = vertices[i];
            if (i + 1 == vertices.size()) { // Close the polygon by connecting back to first vertex
                Point v2 = vertices[0];
            } else {
                Point v2 = vertices[i + 1];
            }

            sf::Vertex line[] = {{v1.x, v1.y, v1.z}, {v2.x, v2.y, v2.z}};
            window.draw(line, 2, sf::Lines);
        }
    }

    // Function to rotate the polygon around X-axis
    void rotateX(float angle) {
        for (Point& v : vertices) {
            v.z = std::sin(angle / 57.2957795131f) * v.x - std::cos(angle / 57.2957795131f) * v.y;
            v.y = std::cos(angle / 57.2957795131f) * v.x + std::sin(angle / 57.2957795131f) * v.z;
        }
    }

    // Function to rotate the polygon around Y-axis
    void rotateY(float angle) {
        for (Point& v : vertices) {
            float newX = v.y * std::cos(angle / 57.2957795131f) - v.z * std::sin(angle / 57.2957795131f);
            float newY = v.x * std::sin(angle / 57.2957795131f) + v.z * std::cos(angle / 57.2957795131f);
            v.y = newX;
            v.x = newY;

            // Update z coordinate for rotation
            Point tempPoint(v.x, v.y, v.z);
            v.x = newX;
            v.y = newY;
        }
    }

    // Function to scale the polygon by factor
    void scale(float factor) {
        for (Point& v : vertices) {
            v.x *= factor;
            v.y *= factor;
            v.z *= factor;
        }
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Polygonal Modeler");

    // Define points of the polygon
    std::vector<Point> vertices = {{0.0f, 0.0f, -5.0f}, {2.0f, 0.0f, -5.0f}, {1.0f, 3.0f, -5.0f}, {0.0f, 4.0f,
-5.0f}};

    Polygon polygon(vertices);

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Rotate polygon around X-axis
        float angle = 10.0f; // Change this value to rotate the polygon
        polygon.rotateX(angle);

        // Draw everything
        window.clear();

        polygon.draw(window);
        window.display();
    }

    return 0;
}
/*
This code creates a simple polygon with four vertices and allows you to manipulate it by rotating it around the
X-axis. You can modify the rotation angle in the main loop to change the direction of rotation.

The Polygon class encapsulates the logic for handling transformations, including rotations and scaling. It uses
SFML's Vertex class to store 3D points and draw lines between them.

You can use this code as a starting point and extend it with additional features such as:

*   Additional transformation methods (Y-axis rotation, Z-axis rotation, etc.)
*   Support for different polygon types (triangle, quadrilateral, pentagon)
*   Improved rendering capabilities
*   User input handling to change vertices or apply transformations interactively
*/