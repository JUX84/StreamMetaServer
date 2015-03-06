CFLAGS=-lIce -lIceUtil -pthread -lvlc
SRC=src/
INC=inc/
OBJ=obj/
BIN=bin/
ICE=ice/
CXX=clang++ -std=c++11 -I$(INC)

all: $(BIN)StreamMetaServer.bin

run: all
	./$(BIN)StreamMetaServer.bin

slice: $(ICE)Server.ice
	slice2cpp $< && mv Server.cpp $(SRC) && mv Server.h $(INC)

$(BIN)StreamMetaServer.bin: $(OBJ)main.o $(OBJ)Server.o $(OBJ)StreamMetaServer.o
	$(CXX) $(CFLAGS) $^ -o $@
$(OBJ)main.o: $(SRC)main.cpp
	$(CXX) -c $< -o $@
$(OBJ)Server.o: $(SRC)Server.cpp $(INC)Server.h
	$(CXX) -c $< -o $@
$(OBJ)StreamMetaServer.o: $(SRC)StreamMetaServer.cpp $(INC)StreamMetaServer.hpp
	$(CXX) -c $< -o $@

clean:
	rm -f obj/*
