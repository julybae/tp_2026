#include "DataStruct.hpp"
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>

int main()
{
  std::vector<DataStruct> data;
  std::string line;

  while (std::getline(std::cin, line))
  {
    if (line.empty())
    {
      continue;
    }

    std::stringstream ss(line);
    DataStruct temp;

    if (ss >> temp)
    {
      data.push_back(temp);
    }
  }

  std::sort(data.begin(), data.end(), compareDataStruct);

  std::copy(
      data.begin(),
      data.end(),
      std::ostream_iterator<DataStruct>(std::cout, "\n"));

  return 0;
}
