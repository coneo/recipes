#include "../net/EventLoop.h"
#include "../base/Thread.h"
#include <stdio.h>

int main()
{
    walle::EventLoop loop;
    loop.loop();
}
