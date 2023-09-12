#include <iostream>
#include <vector>
#include <cmath>

// Structure to represent a point
struct Point {
    double x;
    double y;
    Point(double _x, double _y) : x(_x), y(_y) {}
};

// Function to calculate the area of a triangle formed by three points using the shoelace formula
double calculateArea(const Point& p1, const Point& p2, const Point& p3) {
    return 0.5 * std::abs((p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)));
}

// Function to calculate the largest area of the shape formed by a set of points
double calculateLargestArea(const std::vector<Point>& points) {
    double largestArea = 0.0;
    int n = points.size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                double area = calculateArea(points[i], points[j], points[k]);
                largestArea = std::max(largestArea, area);
            }
        }
    }

    return largestArea;
}

int main() {
    // Sample points
    std::vector<Point> points = {
        Point(1.0, 2.0),
        Point(2.0, 3.0),
        Point(3.0, 4.0),
        Point(4.0, 5.0),
        Point(5.0, 1.0)
    };

    double largestArea = calculateLargestArea(points);
    std::cout << "Largest area of the shape: " << largestArea << std::endl;

    return 0;
}
