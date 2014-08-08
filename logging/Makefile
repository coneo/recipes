CXXFLAGS= -std=c++11 -g -Wall

HEADERS=logger.h #FIXME
TESTS= test_Logger test_WriteFile test_LogBuffer test_Vector

all: $(TESTS)

$(TESTS): $(HEADERS)

$(TESTS):
	g++ $(CXXFLAGS) -o $@ $(filter %.cpp,$^) -lpthread

test_Logger: test_Logger.cpp logger.cpp backend_logger.cpp log_file.cpp

test_WriteFile: test_WriteFile.cpp log_file.cpp

test_LogBuffer: test_LogBuffer.cpp

test_Vector: test_Vector.cpp

clean:
	rm -f $(TESTS) *.file
