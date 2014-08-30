CXXFLAGS= -std=c++11 -g -Wall -I .. -pthread
LDFLAGS= -lpthread

BASE_SRC= ../base/Thread.cpp ../net/EventLoop.cpp ../net/Channel.cpp ../net/Poller.cpp
TESTS= thread_test eventloop_test test3

all: $(TESTS)

$(TESTS):
	g++ $(CXXFLAGS) -o $@ $(BASE_SRC) $(filter %.cpp,$^) $(LDFLAGS)

thread_test: Thread_test.cpp

eventloop_test: Eventloop_test.cpp

test3: test3.cpp

clean:
	rm -f $(TESTS)
