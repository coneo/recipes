CXXFLAGS= -std=c++11 -g -D_HXQ_DEBUG

INC = -I../ -I/usr/include/mysql/
TESTS = test_sqlapi test_db

all: $(TESTS)

$(TESTS):
	g++ $(INC) $(CXXFLAGS) -o $@ $(filter %.cpp,$^) -lpthread -lrt -lmysqlclient

test_sqlapi: test_sqlapi.cpp

test_db: test_db.cpp ../db.cpp

clean:
	rm -f $(TESTS)
