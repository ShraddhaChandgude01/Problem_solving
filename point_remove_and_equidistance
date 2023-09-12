#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

class ShapeAnalyzer {
public:
    ShapeAnalyzer(const std::string& filename) : filename_(filename) {}

    void ReadData() {
        std::ifstream file(filename_);
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file." << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line == "PTS") {
                ReadPoints(file);
            } else if (line == "CON") {
                ReadConnections(file);
            }
        }

        file.close();
    }

    double CalculateLargestArea() {
        double maxArea = 0.0;

        for (const std::vector<int>& connection : connections_) {
            if (connection.size() >= 3) {
                // Calculate the area of the shape formed by connected points
                double area = 0.0;
                for (size_t i = 1; i < connection.size() - 1; ++i) {
                    int x1 = points_[connection[i - 1] - 1].first;
                    int y1 = points_[connection[i - 1] - 1].second;
                    int x2 = points_[connection[i] - 1].first;
                    int y2 = points_[connection[i] - 1].second;
                    int x3 = points_[connection[i + 1] - 1].first;
                    int y3 = points_[connection[i + 1] - 1].second;

                    // Calculate the area of the triangle formed by three points
                    double triangleArea = 0.5 * std::abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
                    area += triangleArea;
                }

                maxArea = std::max(maxArea, area);
            }
        }

        return maxArea;
    }

    int FindPointToRemoveForLargestArea() {
        double largestArea = CalculateLargestArea();
        int pointToRemove = -1;

        for (size_t i = 0; i < points_.size(); ++i) {
            // Temporarily remove the i-th point
            std::vector<std::pair<int, int>> tempPoints = points_;
            tempPoints.erase(tempPoints.begin() + i);

            // Calculate the area without the i-th point
            ShapeAnalyzer tempAnalyzer(filename_);
            tempAnalyzer.points_ = tempPoints;
            double areaWithoutPoint = tempAnalyzer.CalculateLargestArea();

            if (areaWithoutPoint > largestArea) {
                largestArea = areaWithoutPoint;
                pointToRemove = i + 1; // Add 1 to convert to 1-based index
            }
        }

        return pointToRemove;
    }

    std::pair<int, int> CalculateEquidistantPoint() {
        int numPoints = points_.size();
        if (numPoints == 0) {
            return {0, 0}; // Handle empty input gracefully
        }

        double centerX = 0.0;
        double centerY = 0.0;

        for (const auto& point : points_) {
            centerX += point.first;
            centerY += point.second;
        }

        centerX /= numPoints;
        centerY /= numPoints;

        return {static_cast<int>(std::round(centerX)), static_cast<int>(std::round(centerY))};
    }

private:
    void ReadPoints(std::ifstream& file) {
        points_.clear();
        int numPoints;
        file >> numPoints;

        for (int i = 0; i < numPoints; ++i) {
            int x, y;
            file >> x >> y;
            points_.push_back({x, y});
        }
    }

    void ReadConnections(std::ifstream& file) {
        connections_.clear();
        int numConnections;
        file >> numConnections;

        for (int i = 0; i < numConnections; ++i) {
            int numPointsInConnection;
            file >> numPointsInConnection;

            std::vector<int> connection;
            for (int j = 0; j < numPointsInConnection; ++j) {
                int pointIndex;
                file >> pointIndex;
                connection.push_back(pointIndex);
            }

            connections_.push_back(connection);
        }
    }

    std::string filename_;
    std::vector<std::pair<int, int>> points_;
    std::vector<std::vector<int>> connections_;
};

int main() {
    ShapeAnalyzer shapeAnalyzer("input.txt");
    shapeAnalyzer.ReadData();

    int pointToRemove = shapeAnalyzer.FindPointToRemoveForLargestArea();
    if (pointToRemove != -1) {
        std::cout << "Remove point " << pointToRemove << " to get the largest area." << std::endl;
    } else {
        std::cout << "No point to remove for the largest area." << std::endl;
    }

    std::pair<int, int> equidistantPoint = shapeAnalyzer.CalculateEquidistantPoint();
    std::cout << "Equidistant Point: (" << equidistantPoint.first << ", " << equidistantPoint.second << ")" << std::endl;

    return 0;
}
