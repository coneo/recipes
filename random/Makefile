CXXFLAGS= -std=c++11 -g -Wall -DTEST_IO_BUFFER1

HEADERS=  #FIXME
TESTS= test_c_rand test_basic_random test_random_faq

all: $(TESTS)

$(TESTS): $(HEADERS)

$(TESTS):
	g++ $(CXXFLAGS) -o $@ $(filter %.cpp,$^) -lpthread

test_c_rand: test_c_rand.cpp

test_basic_random: test_basic_random.cpp

test_random_faq: test_random_faq.cpp

clean:
	rm -f $(TESTS)
