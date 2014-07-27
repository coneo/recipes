CXXFLAGS= -std=c++11 -g -Wall

HEADERS=Logger.h  #FIXME
TESTS= test_Logger

all: $(TESTS)

$(TESTS): $(HEADERS)

$(TESTS):
	g++ $(CXXFLAGS) -o $@ $(filter %.cpp,$^) -lpthread

test_Logger: test_Logger.cpp Logger.cpp

clean:
	rm -f $(TESTS)
