#include "../base/Thread.h"

#include <stdio.h>
#include <unistd.h>
#include <boost/bind.hpp>

using namespace walle;

void threadFunc1()
{
    printf("%s:start\n",__func__);
    sleep(3);
    printf("%s:end\n",__func__);
}

void threadFunc2(const void *ptr)
{
    char *message = NULL;
    message = (char*)ptr;
    printf("%s: %s \n",__func__,message);
    sleep(3);
    printf("%s:end\n",__func__);
}

class Foo
{
public:
    void threadFunc3()
    {
	printf("%s:\n",__func__);
    }
    void threadFunc4(int x)
    {
	printf("%s: x=%d\n",__func__,x);
    }
};

int main(int argc, char**argv)
{
    printf("pid=%d\n",::getpid());

    Thread t1(boost::bind(::threadFunc1),"thread1");
    t1.start();
    t1.join();

    Thread t2(boost::bind(::threadFunc2,"hello world"), "thread2");
    t2.start();
    t2.join();

    Foo foo;
    Thread t3(boost::bind(&Foo::threadFunc3,&foo),"thread3");
    t3.start();
    t3.join();

    Thread t4(boost::bind(&Foo::threadFunc4,&foo,5),"thread4");
    t4.start();
    t4.join();

    sleep(10);
    return 0;
}
