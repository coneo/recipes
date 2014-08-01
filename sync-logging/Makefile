CXXFLAGS= -std=c++11 -g -Wall -DTEST_IO_BUFFER1

HEADERS=SyncLogger.h WriteFile.h#FIXME
TESTS= test_Logger test_performance

all: $(TESTS)

$(TESTS): $(HEADERS)

$(TESTS):
	g++ $(CXXFLAGS) -o $@ $(filter %.cpp,$^) -lpthread

test_Logger: test_Logger.cpp SyncLogger.cpp WriteFile.cpp

test_performance: test_performance.cpp 

clean:
	rm -f $(TESTS) *.f

cf:
	rm *.f
