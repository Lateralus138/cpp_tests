#pragma once
#ifndef PARSEARGS_H
#define PARSEARGS_H

class ParseArgs
{
private:
  int argC;
  char ** argV;
public:
  ParseArgs(int argc_, char ** argv_)
  {
    parseArgs(argc_, argv_);
  }
  void parseArgs(int argc_, char ** argv_)
  {
    setArgC(argc_);
    setArgV(argv_);   
  }
  void setArgC(int argc_)
  {
    argC = argc_;
  }
  int getArgC()
  {
    return argC;
  }
  void setArgV(char ** argv_)
  {
    argV = argv_;
  }
  char ** getArgV()
  {
    return argV;
  }
};

#endif
