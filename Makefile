CPPFLAGS=-g -std=c++11
INC=-Iinc
SRC=src/*.cpp
BIN=bin

sbsDecode: $(OBJS)
	g++ $(CPPFLAGS) $(INC) -o $(BIN)/sbsDecode $(SRC)

clean:
	rm -r bin/*
