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
LMUTEX_DIR = $(LIB_DIR)/Lmutex
IDIR := include

MFLAG = -lm

clean:	
	rm -rf $(BIN_DIR)
	rm -rf ./$(LIB_DIR)/$(LTHREAD)/*.a
	rm -rf ./$(LIB_DIR)/$(LTHREAD)/*.o

createBin:
	@mkdir $(BIN_DIR)

build: Lthread TestLthread TestPthread

Lthread:
	$(CC) -c ./$(LTHREAD_DIR)/Lthread.c -o ./$(LTHREAD_DIR)/Lthread.o
	$(CC) -c ./$(LTHREAD_DIR)/Lthread_queue.c -o ./$(LTHREAD_DIR)/Lthread_queue.o
	ar -rc ./$(LTHREAD_DIR)/libLthread.a ./$(LTHREAD_DIR)/*.o
	ranlib ./$(LTHREAD_DIR)/libLthread.a

TestLthread:
	$(CC) ./$(SRC_DIR)/LthreadsTest.c -L./lib/Lthread/ -lLthread -o ./$(BIN_DIR)/LthreadTest

TestPthread:
	$(CC) ./$(SRC_DIR)/PthreadsTest.c -lpthread -o ./$(BIN_DIR)/PthreadTest



