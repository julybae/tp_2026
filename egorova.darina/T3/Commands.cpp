#include "Commands.h"
#include "Geometry.h"
#include <iostream>
#include <numeric>
#include <string>
#include <algorithm>
#include <iomanip>

void cmdArea(const std::vector<Polygon>& figures) {
    std::string arg;
    if (!(std::cin >> arg)) return;
    double res = 0;
    if (arg == "EVEN") {
        res = std::accumulate(figures.begin(), figures.end(), 0.0, [](double sum, const Polygon& p) {
            return (p.points.size() % 2 == 0) ? sum + getArea(p) : sum;
        });
    } else if (arg == "ODD") {
        res = std::accumulate(figures.begin(), figures.end(), 0.0, [](double sum, const Polygon& p) {
            return (p.points.size() % 2 != 0) ? sum + getArea(p) : sum;
        });
    } else if (arg == "MEAN") {
        if (figures.empty()) throw std::runtime_error("");
        res = std::accumulate(figures.begin(), figures.end(), 0.0, [](double sum, const Polygon& p) {
            return sum + getArea(p);
        }) / figures.size();
    } else {
        if (!std::all_of(arg.begin(), arg.end(), ::isdigit)) throw std::runtime_error("");
        size_t n = std::stoul(arg);
        if (n < 3) throw std::runtime_error("");
        res = std::accumulate(figures.begin(), figures.end(), 0.0, [n](double sum, const Polygon& p) {
            return (p.points.size() == n) ? sum + getArea(p) : sum;
        });
    }
    std::cout << std::fixed << std::setprecision(1) << res << "\n";
}

void cmdMax(const std::vector<Polygon>& figures) {
    if (figures.empty()) throw std::runtime_error("");
    std::string arg;
    std::cin >> arg;
    if (arg == "AREA") {
        auto it = std::max_element(figures.begin(), figures.end(), [](const Polygon& a, const Polygon& b) {
            return getArea(a) < getArea(b);
        });
        std::cout << std::fixed << std::setprecision(1) << getArea(*it) << "\n";
    } else if (arg == "VERTEXES") {
        auto it = std::max_element(figures.begin(), figures.end(), [](const Polygon& a, const Polygon& b) {
            return a.points.size() < b.points.size();
        });
        std::cout << it->points.size() << "\n";
    } else throw std::runtime_error("");
}

void cmdMin(const std::vector<Polygon>& figures) {
    if (figures.empty()) throw std::runtime_error("");
    std::string arg;
    std::cin >> arg;
    if (arg == "AREA") {
        auto it = std::min_element(figures.begin(), figures.end(), [](const Polygon& a, const Polygon& b) {
            return getArea(a) < getArea(b);
        });
        std::cout << std::fixed << std::setprecision(1) << getArea(*it) << "\n";
    } else if (arg == "VERTEXES") {
        auto it = std::min_element(figures.begin(), figures.end(), [](const Polygon& a, const Polygon& b) {
            return a.points.size() < b.points.size();
        });
        std::cout << it->points.size() << "\n";
    } else throw std::runtime_error("");
}

void cmdCount(const std::vector<Polygon>& figures) {
    std::string arg;
    std::cin >> arg;
    if (arg == "EVEN") {
        std::cout << std::count_if(figures.begin(), figures.end(), [](const Polygon& p) { return p.points.size() % 2 == 0; }) << "\n";
    } else if (arg == "ODD") {
        std::cout << std::count_if(figures.begin(), figures.end(), [](const Polygon& p) { return p.points.size() % 2 != 0; }) << "\n";
    } else {
        if (!std::all_of(arg.begin(), arg.end(), ::isdigit)) throw std::runtime_error("");
        size_t n = std::stoul(arg);
        if (n < 3) throw std::runtime_error("");
        std::cout << std::count_if(figures.begin(), figures.end(), [n](const Polygon& p) { return p.points.size() == n; }) << "\n";
    }
}

void cmdIntersections(const std::vector<Polygon>& figures) {
    Polygon target;
    if (!(std::cin >> target)) throw std::runtime_error("");
    std::cout << std::count_if(figures.begin(), figures.end(), [&](const Polygon& p) {
        return polygonsIntersect(p, target);
    }) << "\n";
}

void cmdRmEcho(std::vector<Polygon>& figures) {
    Polygon target;
    if (!(std::cin >> target)) throw std::runtime_error("");
    size_t initial_size = figures.size();
    auto it = std::unique(figures.begin(), figures.end(), [&](const Polygon& a, const Polygon& b) {
        return (a == target && b == target);
    });
    figures.erase(it, figures.end());
    std::cout << initial_size - figures.size() << "\n";
}
