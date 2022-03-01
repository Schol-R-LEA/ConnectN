SRC=src
TEST=tests
BIN=bin
INC=include
CC=g++
INC_OPTIONS=-Iinclude
CC_OPTIONS=-Wall -Wextra -Werror -std=c++17 $(INC_OPTIONS)


main: board
	$(CC) $(CC_OPTIONS) $(SRC)/connect-four.cpp $(BIN)/connectnboard.o -o $(BIN)/connect-four

board: 
	$(CC) $(CC_OPTIONS) -c $(SRC)/connectnboard.cpp -o $(BIN)/connectnboard.o

test: board
	$(CC) $(CC_OPTIONS) $(TEST)/conn4_test.cpp $(BIN)/connectnboard.o -o $(BIN)/conn4_test
