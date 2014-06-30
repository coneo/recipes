#pragma once
#include <iostream>

class CTest
{
public:
  CTest(){}
  ~CTest(){}

  bool isValid() {return true;}
  void doSomething() 
  {
    std::cout << "do something" <<std::endl;
  }
};
