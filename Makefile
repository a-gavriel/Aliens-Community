all: clean createBin build
.PHONY: clean createBin build

CFLAGS = -Wall
CC := gcc
LDLIBS = -lrt -lpthread

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
IDIR := include

MFLAG = -lm

clean:	
	@rm -rf $(BIN_DIR)

createBin:
	@mkdir $(BIN_DIR)

build: producer

P_SRC = $(SRC_DIR)/producer.c $(SRC_DIR)/randomGenerators.c
producer: 
	$(CC) $(P_SRC) -o $(BIN_DIR)/$@ $(CFLAGS) $(LDLIBS) $(MFLAG)



