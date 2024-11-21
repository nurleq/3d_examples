#include <iostream>
#include <vector>

// Define a point structure
struct Point {
    float x, y;
};

// Define a curve class
class Curve {
public:
    std::vector<Point> points;

    void addPoint(const Point& point) {
        points.push_back(point);
    }

    // NURBS function
    void nurbs(float t, const std::vector<Point>& controlPoints, float weight) {
        // Calculate the basis functions for the current degree
        float basis[3][4];
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (j <= controlPoints.size() - i - 1) {
                    basis[i][j] = 1;
                } else {
                    basis[i][j] = 0;
                }
            }

            // Calculate the basis functions using the control points
            for (int j = 0; j < 4; ++j) {
                float sum = 0;
                for (int k = 0; k <= i; ++k) {
                    sum += pow(t, j + k - i) * basis[k][j];
                }
                for (int k = controlPoints.size() - i - 1; k >= 0; --k) {
                    sum -= pow(t, j + k - i) * basis[k][j];
                }
                basis[i][j] = sum;
            }
        }

        // Calculate the curve point using the basis functions and weight
        float x = 0;
        float y = 0;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 4; ++j) {
                float value = basis[i][j] * controlPoints[j].x + weight * (basis[i][j] - 1);
                x += value;
                y += value * controlPoints[j].y;
            }
        }

        // Return the curve point
        std::cout << "Curve Point: (" << x << ", " << y << ")" << std::endl;
    }

    // B-Spline function
    void bspline(float t, const std::vector<Point>& controlPoints) {
        float n = 3; // Degree of the spline
        float m = controlPoints.size();

        // Calculate the basis functions for the current degree
        float basis[4][m + 1];
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j <= m; ++j) {
                if (i <= j) {
                    basis[i][j] = 1;
                } else {
                    basis[i][j] = 0;
                }
            }

            // Calculate the basis functions using the control points
            float sum = 0;
            for (int k = i; k < m + 1 - i; ++k) {
                sum += pow(t, i + k);
            }
            for (int k = m + 1 - i; k <= i; ++k) {
                sum -= pow(t, i + k);
            }
            basis[i][j] = sum;
        }

        // Calculate the curve point using the basis functions and weight
        float x = 0;
        float y = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= m + 1 - i; ++j) {
                float value = basis[i][j] * controlPoints[j].x + weight * (basis[i][j] - 1);
                x += value;
                y += value * controlPoints[j].y;
            }
        }

        // Return the curve point
        std::cout << "Curve Point: (" << x << ", " << y << ")" << std::endl;
    }

    // Spline function
    void spline(float t, const std::vector<Point>& controlPoints) {
        float x = 0;
        float y = 0;

        // Iterate over the control points to calculate the curve point
        for (int i = 0; i < controlPoints.size(); ++i) {
            Point p1 = controlPoints[i];
            Point p2 = controlPoints[(i + 1) % controlPoints.size()];
            float t1 = (t - i / controlPoints.size()) * (p2.x - p1.x);
            float t2 = t1;
            x += t1 * p1.x + t2 * p2.x;
            y += t1 * p1.y + t2 * p2.y;
        }

        // Return the curve point
        std::cout << "Curve Point: (" << x << ", " << y << ")" << std::endl;
    }
};

// Define a geometric primitive class
class GeometricPrimitive {
public:
    float x, y;

    GeometricPrimitive(float x, float y) : x(x), y(y) {}

    void nurbs(float t, const std::vector<Point>& controlPoints, float weight) {
        Curve().nurbs(t, controlPoints, weight);
    }

    void bspline(float t, const std::vector<Point>& controlPoints) {
        Curve().bspline(t, controlPoints);
    }

    void spline(float t, const std::vector<Point>& controlPoints) {
        Curve().spline(t, controlPoints);
    }
};

int main() {
    // Create a geometric primitive
    GeometricPrimitive primitive(0, 0);

    // Define some control points for the NURBS function
    std::vector<Point> nurbsControlPoints = {{1, 1}, {2, 2}, {3, 3}};

    // Call the NURBS function with different weights
    float t = 0.5;
    primitive.nurbs(t, nurbsControlPoints, 0);
    primitive.nurbs(t, nurbsControlPoints, 1);

    // Define some control points for the B-Spline function
    std::vector<Point> bsplineControlPoints = {{1, 1}, {2, 2}, {3, 3}};

    // Call the B-Spline function with different weights
    primitive.bspline(t, bsplineControlPoints);
    primitive.bspline(t, bsplineControlPoints, 0.5);

    // Define some control points for the Spline function
    std::vector<Point> splineControlPoints = {{1, 1}, {2, 2}};

    // Call the Spline function with different weights
    primitive.spline(t, splineControlPoints);
    primitive.spline(t, splineControlPoints, 0.5);

    return 0;
}