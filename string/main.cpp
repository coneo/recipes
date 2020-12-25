#include <iostream>
#include <vector>
#include "common.h"

int main()
{
    char* str = "+hello+hxq+hah++jj";
    std::vector<std::string> vec;
    stringtok(vec, str, "+");

    for (auto& i : vec)
    {
        std::cout << i << std::endl;
    }
    return 0;
}
