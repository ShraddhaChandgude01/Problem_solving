#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

// Structure to represent a point
struct Point {
    int id;
    double x;
    double y;
    Point(int _id, double _x, double _y) : id(_id), x(_x), y(_y) {}
};

class FileReader {
private:
    std::vector<Point> points;
    std::vector<std::pair<int, int>> connections;

public:
    // Function to read data from a text file
    bool readDataFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open the file: " << filename << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line == "PTS") {
                readPoints(file);
            } else if (line == "CON") {
                readConnections(file);
            }
        }

        file.close();
        return true;
    }

    // Function to get the read points
    const std::vector<Point>& getPoints() const {
        return points;
    }

    // Function to get the read connections
    const std::vector<std::pair<int, int>>& getConnections() const {
        return connections;
    }

private:
    // Function to read points from the file
    void readPoints(std::ifstream& file) {
        std::string line;
        int id = 1;

        while (std::getline(file, line) && !line.empty()) {
            std::istringstream iss(line);
            double x, y;
            if (iss >> x >> y) {
                points.emplace_back(id++, x, y);
            }
        }
    }

    // Function to read connections from the file
    void readConnections(std::ifstream& file) {
        std::string line;

        while (std::getline(file, line) && !line.empty()) {
            std::istringstream iss(line);
            int p1, p2;
            if (iss >> p1 >> p2) {
                connections.emplace_back(p1, p2);
            }
        }
    }
};

int main() {
    FileReader reader;
    if (reader.readDataFromFile("input.txt")) { 
        const std::vector<Point>& points = reader.getPoints();
        const std::vector<std::pair<int, int>>& connections = reader.getConnections();

        std::cout << "Points:" << std::endl;
        for (const Point& point : points) {
            std::cout << point.id << " " << point.x << " " << point.y << std::endl;
        }

        std::cout << "Connections:" << std::endl;
        for (const auto& connection : connections) {
            std::cout << connection.first << " " << connection.second << std::endl;
        }
    }

    return 0;
}
