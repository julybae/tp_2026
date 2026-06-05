#include "data_struct.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <iomanip>

// Вставь сюда код main() и ничего больше! Без операторов и компаратора.

int main() {
    std::vector<DataStruct> data;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) break;
        std::istringstream iss(line);
        DataStruct d;
        if (iss >> d) {
            data.push_back(d);
        }
    }
    std::sort(data.begin(), data.end(), comparator);
    for (const auto& d : data) {
        std::cout << d << "\n";
    }
    return 0;
}
