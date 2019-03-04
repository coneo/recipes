#include "scope_guard.h"
#include <stdio.h>

int main()
{
    ScopeGuard onexit([&]{printf("hahah exit\n");});
    return 0;
}
