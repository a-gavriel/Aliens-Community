all: clean createBin build
.PHONY: clean createBin build

CFLAGS = -Wall
CC := gcc
LDLIBS = -lrt -lpthread


SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
LIB_DIR = lib
LTHREAD_DIR = $(LIB_DIR)/Lthread
IDIR := include

MFLAG = -lm

clean:	
	rm -rf $(BIN_DIR)
	rm -rf ./$(LIB_DIR)/$(LTHREAD)/*.a
	rm -rf ./$(LIB_DIR)/$(LTHREAD)/*.o

createBin:
	@mkdir $(BIN_DIR)

build: Lthread TestLthread

Lthread:
	$(CC) -c ./$(LTHREAD_DIR)/Lthread.c -o ./$(LTHREAD_DIR)/Lthread.o
	$(CC) -c ./$(LTHREAD_DIR)/Lthread_q.c -o ./$(LTHREAD_DIR)/Lthread_q.o
	ar -rc ./$(LTHREAD_DIR)/libLthread.a ./$(LTHREAD_DIR)/*.o
	ranlib ./$(LTHREAD_DIR)/libLthread.a

TestLthread:
	$(CC) ./$(SRC_DIR)/LthreadsTest.c -L./lib/Lthread/ -lLthread -o ./$(BIN_DIR)/LthreadTest



