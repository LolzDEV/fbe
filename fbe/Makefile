CC=gcc
CFLAGS=-Wall -Wextra -g -c
SOURCES=$(wildcard *.c)
BUILD_DIR=../build
LIBRARIES= 

all: $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LIBRARIES) $(SOURCES)
	@mv -v --target-directory=$(BUILD_DIR) *.o

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

.PHONY:
	$(SOURCES)
