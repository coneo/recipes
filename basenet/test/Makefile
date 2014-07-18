BASE_DIR=../base
CXXFLAGS=-g -Wall

HEADERS=$(BASE_DIR)/Thread.h  #FIXME
TESTS= thread_test

all: $(TESTS)

$(TESTS): $(HEADERS)

$(TESTS):
	g++ $(CXXFLAGS) -o $@ $(filter %.cpp,$^) -lpthread

thread_test: Thread_test.cpp $(BASE_DIR)/Thread.cpp

clean:
	rm -f $(TESTS)
