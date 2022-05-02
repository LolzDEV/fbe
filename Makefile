CC=gcc
CFLAGS=-Wall -Wextra -g -fPIC
BINARY=fbe
SOURCES=$(wildcard src/*.c)
BUILD_DIR=build
LIBRARIES= -L ./build/libfbe -lfbe

all: $(BUILD_DIR)
	@make -C libfbe
	@make -C fbe
	gcc $(CFLAGS) $(LIBRARIES) $(BUILD_DIR)/*.o -o $(BUILD_DIR)/$(BINARY)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

clean:
	rm build/*.o
	rm build/libfbe/*.o
