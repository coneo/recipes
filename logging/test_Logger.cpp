#include "Logger.h"
#include <iostream>
#include <functional>

int main()
{
    //LOG_DEBUG("int=%d,str=%s", 25,"hello");
    gLogger.print("hello logging\n");
    gLogger.print("int=%d,str=%s", 32, "hello logging \n");
    //gLogger.print("hello%s"); //runtime error
    //gLogger.print("hello %d", 23,24,"hello"); //runtime error
}
