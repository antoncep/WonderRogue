CC=gcc
CFLAGS=-Wall -g
CLIBS=-lm -lncurses
BIN_DIR=bin/
BIN=wonder_rogue
INC_DIR=inc/
SRC_DIR=src/

all: $(BIN)

$(BIN): main.c $(SRC_DIR)*
	$(CC) $(CFLAGS) $(CLIBS) -o $(BIN_DIR)$@ -I $(INC_DIR) $^
