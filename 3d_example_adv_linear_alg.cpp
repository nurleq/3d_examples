/*Here's an example of using C++ to perform some advanced vector calculations in 3D linear algebra: */
#include <iostream>
#include <cmath>

// Define a class for 3D vectors
class Vector3 {
public:
    double x, y, z;

    // Constructor
    Vector3(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {}

    // Calculate the magnitude (length) of the vector
    double magnitude() const {
        return sqrt(x * x + y * y + z * z);
    }

    // Normalize the vector to a unit length
    Vector3 normalize() const {
        double mag = magnitude();
        if (mag == 0.0) return Vector3(0, 0, 0); // cannot divide by zero!
        return Vector3(x / mag, y / mag, z / mag);
    }

    // Calculate the dot product of this vector and another
    double dotProduct(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Calculate the cross product of this vector and another
    Vector3 crossProduct(const Vector3& other) const {
        double a = y * other.z - z * other.y;
        double b = z * other.x - x * other.z;
        double c = x * other.y - y * other.x;

        return Vector3(a, b, c);
    }

    // Calculate the reflection of this vector across another
    Vector3 reflect(const Vector3& normal) const {
        double cosTheta = dotProduct(normal) / magnitude() / normal.magnitude();
        Vector3 reflected;
        reflected.x = x + 2 * (cosTheta - 1) * normal.x;
        reflected.y = y + 2 * (cosTheta - 1) * normal.y;
        reflected.z = z + 2 * (cosTheta - 1) * normal.z;

        return reflected;
    }

    // Calculate the projection of this vector onto another
    Vector3 project(const Vector3& other) const {
        double cosTheta = dotProduct(other) / magnitude() / other.magnitude();
        Vector3 projected;
        projected.x = x * cosTheta;
        projected.y = y * cosTheta;
        projected.z = z * cosTheta;

        return projected;
    }
};

// Function to print a 3D vector
void printVector(const Vector3& v) {
    std::cout << "(" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
}

int main() {
    // Create two example vectors
    Vector3 v1(1.0, 2.0, 3.0);
    Vector3 v2(4.0, 5.0, 6.0);

    // Calculate and print some vector calculations
    std::cout << "Vector 1: ";
    printVector(v1);
    std::cout << "Vector 2: ";
    printVector(v2);

    double dotProduct = v1.dotProduct(v2);
    std::cout << "Dot Product: " << dotProduct << std::endl;

    Vector3 normal(0.0, 0.0, -1.0); // a unit vector in the z-direction
    Vector3 reflected = v1.reflect(normal);
    std::cout << "Reflected Vector: ";
    printVector(reflected);

    Vector3 projected = v1.project(v2);
    std::cout << "Projected Vector: ";
    printVector(projected);

    return 0;
}
/*
This code defines a `Vector3` class with methods for calculating various advanced vector operations, such as the
magnitude (length), normalization, dot product, cross product, reflection across another vector, and projection
onto another vector.

The example demonstrates how to use these functions in a simple C++ program.
*/