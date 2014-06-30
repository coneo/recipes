#include "classBase.h"
#include <boost/smart_ptr.hpp>

int main(int argc, char**argv)
{
  boost::shared_ptr<CTest> testA(new CTest);
  std::cout << "the test now has " << testA.use_count() << "references\n";

  boost::shared_ptr<CTest> testB = testA;
  std::cout << "the test now has " << testA.use_count() << "references\n";

  testA.reset();
  std::cout << "the test now has " << testB.use_count() << "references\n";
}
