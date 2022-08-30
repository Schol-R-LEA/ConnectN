SRC=src
TEST=tests
BIN=bin
INC=include
CC=g++
INC_OPTIONS=-Iinclude
CC_OPTIONS=-Wall -Wextra -Werror -std=c++17 $(INC_OPTIONS)


gui: gui_board AI
	$(CC) $(CC_OPTIONS) \
	-lallegro -lallegro_image \
	$(SRC)/connectnGUI.cpp \
	$(BIN)/connectnboard.o $(BIN)/connectnboard_GUI.o $(BIN)/connectn_AI.o \
	-o $(BIN)/connect-four-GUI

text: board AI
	$(CC) $(CC_OPTIONS) $(SRC)/connect-four.cpp $(BIN)/connectnboard.o $(BIN)/connectn_AI.o -o $(BIN)/connect-four

gui_board: board
	$(CC) $(CC_OPTIONS) -c $(SRC)/connectnboard_GUI.cpp -o $(BIN)/connectnboard_GUI.o

board:
	$(CC) $(CC_OPTIONS) -c $(SRC)/connectnboard.cpp -o $(BIN)/connectnboard.o

AI: board
	$(CC) $(CC_OPTIONS) -c $(SRC)/connectn_AI.cpp -o $(BIN)/connectn_AI.o

test: board
	$(CC) $(CC_OPTIONS) $(TEST)/conn4_test.cpp $(BIN)/connectnboard.o -o $(BIN)/conn4_test
