#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "polygon.hpp"
#include "commands.hpp"
#include <algorithm>

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cerr << "Error: File name not specified." << std::endl;
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "Error: Could not open file " << argv[1] << std::endl;
    return 1;
  }

  std::vector<Polygon> shapes;
  std::string line;

  while (std::getline(file, line))
  {
    // Пропускаем пустые строки или строки только с пробелами
    if (line.empty() || std::all_of(line.begin(), line.end(), ::isspace))
    {
      continue;
    }

    std::stringstream ss(line);
    Polygon poly;

    // Попытка распарсить полигон из строки
    if (ss >> poly)
    {
      std::string trailing;
      // Условие: если после чтения N точек в строке остался какой-то мусор/лишние точки
      if (!(ss >> trailing))
      {
        shapes.push_back(poly);
      }
    }
  }
  file.close();

  processCommands(shapes);
  return 0;
}
