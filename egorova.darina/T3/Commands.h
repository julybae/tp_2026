#ifndef COMMANDS_H
#define COMMANDS_H

#include <vector>
#include "Polygon.h"

void cmdArea(const std::vector<Polygon>& figures);
void cmdMax(const std::vector<Polygon>& figures);
void cmdMin(const std::vector<Polygon>& figures);
void cmdCount(const std::vector<Polygon>& figures);
void cmdIntersections(const std::vector<Polygon>& figures);
void cmdRmEcho(std::vector<Polygon>& figures);

#endif
