#include "classBase.h"
#include <boost/smart_ptr.hpp>

void testScopePtr()
{
  boost::scoped_ptr<CTest> samplePtr(new CTest);
  if (samplePtr->isValid())
  {
    samplePtr->doSomething();
  }
}

int main(int argc, char**argv)
{
  testScopePtr();
}
