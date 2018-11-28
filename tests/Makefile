#Makefile For Testing with Google Test
GTEST_DIR = /usr/src/gtest
TESTBINS = /obj

# Where to find user code.
USER_DIR = ..
CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra -pthread -std=c++11 -lm -lamqpcpp -ldl -levent

#Add additional tests here
TESTS = tcpListener_test


GTEST_HEADERS = $(GTEST_DIR)/src/*.h

test : $(TESTS)

clean :
	rm -f $(TESTBINS)/$(TESTS) $(TESTBINS)/gtest.a $(TESTBINS)/gtest_main.a $(TESTBINS)/*.o


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
tcplistener.o : $(USER_DIR)/src/tcplistener.cpp $(USER_DIR)/inc/tcpListener.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(USER_DIR)/inc -c $(USER_DIR)/src/tcplistener.cpp

tcpListener_test.o : tcpListener_test.cpp \
                     $(USER_DIR)/inc/tcpListener.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I$(USER_DIR)/inc -c $(USER_DIR)/tests/tcpListener_test.cpp

tcpListener_test : tcplistener.o tcpListener_test.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

test:
	./tcpListener_test