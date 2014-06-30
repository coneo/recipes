#include "classBase.h"
#include <boost/smart_ptr.hpp>
#include <vector>

int main(int argc, char**argv)
{
  typedef boost::shared_ptr<CTest> CTestPtr;

  std::vector<CTestPtr> vec;

  vec.push_back(CTestPtr(new CTest));
  vec.push_back(CTestPtr(new CTest));
  vec.push_back(CTestPtr(new CTest));

  CTestPtr ele = vec[0];

  //clear vec
  vec.clear();

  //ele still in use
  ele->doSomething();
}
