#pragma once
#ifndef BOXUNICHARSLIB_H
#define BOXUNICHARSLIB_H
#include <string>
class BoxUniCharsLib
{
private:
  std::string BOXUNICHARS_ALL_DEFAULT;
  std::string BOXUNICHARS_ALL_HORZ;
  std::string BOXUNICHARS_ALL_VERT;
  std::string BOXUNICHARS_SINGLE_SINGLE_VERT_DOUBLE_HORZ;
  std::string BOXUNICHARS_SINGLE_DOUBLE_VERT_SINGLE_HORZ;
  std::string BOXUNICHARS_SINGLE_SINGLE;
  std::string BOXUNICHARS_SINGLE_DOUBLE;
public:
  void Initiate(std::string mode);
  std::string Default();
  std::string Horizontal();
  std::string Vertical();
  std::string SingleVerticalDoubleHorizontal();
  std::string DoubleVerticalSingleHorizontal();
  std::string Single();
  std::string Double();
};
#endif // !BOXUNICHARSLIB_H
