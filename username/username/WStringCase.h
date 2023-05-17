#include <string>
class WStringCase
{
private:
  std::wstring wstring_;
public:
  WStringCase(std::wstring _wstring);
  void setString(std::wstring _wstring);
  std::wstring getString();
  std::wstring upper();
  std::wstring lower();
  std::wstring title();
};
