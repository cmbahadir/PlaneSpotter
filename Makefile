CPPFLAGS=-g -std=c++11 
INC=-Iinc -I/usr/local/include
SRC=src/*.cpp
TEST_SRC=tests/*.cpp
LIBS=-L/usr/local/lib -lm -pthread -lamqpcpp -ldl -levent
BIN=bin

sbsDecode: $(OBJS)
	g++ $(CPPFLAGS) $(INC) -o $(BIN)/sbsDecode $(SRC) $(LIBS)

clean:
	rm -r $(BIN)/*
