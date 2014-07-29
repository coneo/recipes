CXXFLAGS= -g -Wall -I .. -pthread
LDFLAGS= -lpthread

BASE_SRC= ../base/Thread.cpp ../net/EventLoop.cpp
TESTS= thread_test eventloop_test

all: $(TESTS)

$(TESTS):
	g++ $(CXXFLAGS) -o $@ $(BASE_SRC) $(filter %.cpp,$^) $(LDFLAGS)

thread_test: Thread_test.cpp

eventloop_test: Eventloop_test.cpp

clean:
	rm -f $(TESTS)
