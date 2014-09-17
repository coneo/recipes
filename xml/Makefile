CXXFLAGS= -std=c++11 -g

INC = -I. -I/usr/include/libxml2
TESTS= test_Main

all: $(TESTS)

$(TESTS):
	g++ $(INC) $(CXXFLAGS) -o $@ $(filter %.cpp,$^) -lrt -lxml2

test_Main: test.cpp xmlparser.cpp

clean:
	rm -f $(TESTS)
