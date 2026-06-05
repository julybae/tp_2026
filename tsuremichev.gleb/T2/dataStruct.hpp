#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <string>
#include <complex>

struct DataStruct
{
  std::complex<double> key1; // CMP LSP
  double key2;               // DBL SCI
  std::string key3;

  DataStruct() {}
};

struct DelimiterIO
{
  char expected;
};
struct LabelIO
{
  std::string expected;
};

std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
std::istream &operator>>(std::istream &in, LabelIO &&dest);
std::istream &operator>>(std::istream &in, DataStruct &dest);
std::ostream &operator<<(std::ostream &out, const DataStruct &src);

#endif
