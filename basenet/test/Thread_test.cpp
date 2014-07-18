#include "../base/Thread.h"

#include <stdio.h>
#include <unistd.h>
#include <boost/bind.hpp>

void printMessage(const void *ptr)
{
    char *message = NULL;
    message = (char*)ptr;
    printf("%s \n",message);
    sleep(5);
}

int main(int argc, char**argv)
{
    Thread t1(boost::bind(::printMessage,"hello world"), "thread1");
    t1.start();
    t1.join();

    return 0;
}
