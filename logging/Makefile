CXXFLAGS= -std=c++11 -g -Wall

HEADERS=logger.h WriteFile.h #FIXME
TESTS= test_Logger test_WriteFile test_LogBuffer test_Vector

all: $(TESTS)

$(TESTS): $(HEADERS)

$(TESTS):
	g++ $(CXXFLAGS) -o $@ $(filter %.cpp,$^) -lpthread

test_Logger: test_Logger.cpp logger.cpp

test_WriteFile: test_WriteFile.cpp WriteFile.cpp

test_LogBuffer: test_LogBuffer.cpp

test_Vector: test_Vector.cpp

clean:
	rm -f $(TESTS) *.file
