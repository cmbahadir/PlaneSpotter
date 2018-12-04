#Makefile For Testing with Google Test
GTEST_DIR = /usr/src/gtest
TESTBINS = /obj

# Where to find user code.
USER_DIR = ..
CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g --coverage -Wall -Wextra -pthread -std=c++11 -lm -lamqpcpp -ldl -levent

#Add additional tests here
TESTS = TCPListener_Test


GTEST_HEADERS = $(GTEST_DIR)/src/*.h

test : $(TESTS)

clean :
	rm -f $(TESTS) gtest.a gtest_main.a *.o


GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# Compile and Build Google Test First
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Compile the CPP under Test and test objects then execute tests
TCPListener.o : $(USER_DIR)/src/TCPListener.cpp $(USER_DIR)/inc/TCPListener.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(USER_DIR)/inc -c $(USER_DIR)/src/TCPListener.cpp

TCPListener_Test.o : TCPListener_Test.cpp \
                     $(USER_DIR)/inc/TCPListener.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(USER_DIR)/inc -c $(USER_DIR)/tests/TCPListener_Test.cpp

TCPListener_Test : TCPListener.o TCPListener_Test.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@