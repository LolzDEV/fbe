CC=gcc
CFLAGS=-Wall -Wextra -g
BINARY=libfbe
BUILD_DIR=../build/libfbe
LIBRARIES= -lm

all: $(BUILD_DIR)
	@make -C src
	ar rcs $(BUILD_DIR)/libfbe.a $(BUILD_DIR)/*.o 

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

clean:
	rm $(BUILD_DIR)/*
