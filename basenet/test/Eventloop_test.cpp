#include "../net/EventLoop.h"
#include "../base/Thread.h"
#include <stdio.h>

int main()
{
    Walle::EventLoop loop;
    loop.loop();
}
