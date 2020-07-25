all: clean createBin build
.PHONY: clean createBin build

CFLAGS = -Wall
CC := gcc
LDLIBS = -lrt -lpthread
ALLEGRO_LIBS = allegro-5 allegro_font-5 allegro_image-5 allegro_ttf-5 allegro_primitives-5

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
LIB_DIR = lib
LTHREAD_DIR = $(LIB_DIR)/Lpthreads
LMUTEX_DIR = $(LIB_DIR)/Lmutex
UTILS_DIR = $(LIB_DIR)/Utils

IDIR := include

MFLAG = -lm

clean:	
	rm -rf $(BIN_DIR)
	rm -rf ./$(LTHREAD_DIR)/*.a
	rm -rf ./$(LTHREAD_DIR)/*.o
	rm -rf ./$(LMUTEX_DIR)/*.a
	rm -rf ./$(LMUTEX_DIR)/*.o
	rm -rf ./$(UTILS_DIR)/*.a
	rm -rf ./$(UTILS_DIR)/*.o

createBin:
	@mkdir $(BIN_DIR)

build: Lpthreads Utils Tests graphics

Lpthreads:
	$(CC) -c ./$(LTHREAD_DIR)/Lpthreads.c -o ./$(LTHREAD_DIR)/Lpthreads.o
	$(CC) -c ./$(LTHREAD_DIR)/Lthread_queue.c -o ./$(LTHREAD_DIR)/Lthread_queue.o
	$(CC) -c ./$(LMUTEX_DIR)/Lmutex.c -o ./$(LMUTEX_DIR)/Lmutex.o
	ar -rc ./$(LTHREAD_DIR)/libLpthreads.a ./$(LTHREAD_DIR)/*.o ./$(LMUTEX_DIR)/*.o
	ranlib ./$(LTHREAD_DIR)/libLpthreads.a

Utils:
	$(CC) -c ./$(UTILS_DIR)/Random.c -o ./$(UTILS_DIR)/Random.o
	ar -rc ./$(UTILS_DIR)/libUtils.a ./$(UTILS_DIR)/*.o
	ranlib ./$(UTILS_DIR)/libUtils.a
Tests:
	$(CC) ./$(SRC_DIR)/Tests.c -L./$(LTHREAD_DIR)/ -L./$(UTILS_DIR)/ -lUtils -lLpthreads -lpthread -o ./$(BIN_DIR)/Tests


graphics:
	$(CC) ./$(SRC_DIR)/graphics.c -o ./$(BIN_DIR)/graphics `pkg-config --libs $(ALLEGRO_LIBS)`
