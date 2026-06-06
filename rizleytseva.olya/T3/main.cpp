#include "polygon.h"
#include "commands.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

int main()
{
  std::vector< Polygon > polys;
  std::string line;

  while (std::getline(std::cin, line))
  {
    if (line.empty())
    {
      continue;
    }

    std::istringstream ss(line);
    std::string firstToken;
    if (!(ss >> firstToken))
    {
      continue;
    }

    // Проверяем, является ли первое слово командой
    static const std::string cmdsList[] = {
      "AREA", "MAX", "MIN", "COUNT", "LESSAREA", "INTERSECTIONS", "MAXSEQ"
    };
    bool isCmd = false;
    for (const auto& c : cmdsList)
    {
      if (firstToken == c)
      {
        isCmd = true;
        break;
      }
    }

    if (isCmd)
    {
      doTasks(polys, line);
    }
    else
    {
      // Пробуем прочитать полигон
      Polygon p;
      std::istringstream polyStream(line);
      if (polyStream >> p)
      {
        std::string extra;
        if (!(polyStream >> extra))
        {
          polys.push_back(std::move(p));
        }
      }
    }
  }

  return 0;
}

