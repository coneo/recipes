CXXFLAGS= -std=c++11 -g -Wall

HEADERS=Logger.h WriteFile.h #FIXME
TESTS= test_Logger test_WriteFile

all: $(TESTS)

$(TESTS): $(HEADERS)

$(TESTS):
	g++ $(CXXFLAGS) -o $@ $(filter %.cpp,$^) -lpthread

test_Logger: test_Logger.cpp Logger.cpp

test_WriteFile: test_WriteFile.cpp WriteFile.cpp

clean:
	rm -f $(TESTS) *.file
