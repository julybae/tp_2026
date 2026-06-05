#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include "Polygon.h"
#include "Commands.h"

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;
    std::ifstream file(argv[1]);
    if (!file) return 1;

    std::vector<Polygon> figures;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        Polygon poly;
        if (ss >> poly) figures.push_back(poly);
    }

    std::string cmd;
    while (std::cin >> cmd) {
        try {
            if (cmd == "AREA") cmdArea(figures);
            else if (cmd == "INTERSECTIONS") cmdIntersections(figures);
            else if (cmd == "RMECHO") cmdRmEcho(figures);
            else {
                std::cout << "<INVALID COMMAND>\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } catch (...) {
            std::cout << "<INVALID COMMAND>\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return 0;
}
