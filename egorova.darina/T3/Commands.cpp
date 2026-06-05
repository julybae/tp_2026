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
        size_t n = std::stoul(arg);
        res = std::accumulate(figures.begin(), figures.end(), 0.0, [n](double sum, const Polygon& p) {
            return (p.points.size() == n) ? sum + getArea(p) : sum;
        });
    }
    std::cout << std::fixed << std::setprecision(1) << res << "\n";
}

void cmdIntersections(const std::vector<Polygon>& figures) {
    Polygon target;
    if (!(std::cin >> target)) throw std::runtime_error("");
    long long count = std::count_if(figures.begin(), figures.end(), [&](const Polygon& p) {
        return polygonsIntersect(p, target);
    });
    std::cout << count << "\n";
}

void cmdRmEcho(std::vector<Polygon>& figures) {
    Polygon target;
    if (!(std::cin >> target)) throw std::runtime_error("");
    size_t initial_size = figures.size();
    auto it = std::unique(figures.begin(), figures.end(), [&](const Polygon& a, const Polygon& b) {
        return a == target && b == target;
    });
    figures.erase(it, figures.end());
    std::cout << initial_size - figures.size() << "\n";
}
