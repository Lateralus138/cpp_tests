#pragma once
class ArgumentParser
{
private:
  std::vector<std::string> tokens;
public:
  ArgumentParser(int& argc, const char** argv, int start);
  const std::vector<std::string>& getArgs() const;
  bool optionExists(const std::string& option) const;
  template <typename UnaryPredicate>
  bool optionExistsByPredicate(UnaryPredicate predicate, bool remove)
  {
    std::vector<std::string>::iterator iterator =
      std::find_if(this->tokens.begin(), this->tokens.end(), predicate);
    bool result = (iterator != this->tokens.end());
    if (result && remove) this->tokens.erase(iterator);
    return result;
  }
  bool optionsExist(const std::vector<std::string>& options) const;
  const std::string& getOption(const std::string& option) const;
  const std::string& getOptions(const std::vector<std::string>& options) const;
  // TODO Revluate if string conversion is necessary in getOptionByPredicate
  template <typename UnaryPredicate>
  const std::string getOptionByPredicate(UnaryPredicate predicate, bool remove)
  {
    std::string value = std::string("");
    std::vector<std::string>::iterator iterator =
      std::find_if(this->tokens.begin(), this->tokens.end(), predicate);
    if (iterator != this->tokens.end())
    {
      int check = 1;
      if (remove)
      {
        iterator = this->tokens.erase(iterator);
        check--;
      }
      if ((iterator + check) != this->tokens.end())
      {
        std::advance(iterator, check);
        value = std::string(*iterator);
        if (remove) iterator = this->tokens.erase(iterator);
      }
    }
    static const std::string RESULT = value;
    return RESULT;
  }
};

