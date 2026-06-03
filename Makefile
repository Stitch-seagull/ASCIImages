CC = gcc
LLIB = -lm
FLAGS = -g -Wall
TARGET = ASCIImages

ROOT_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))
SRC := $(ROOT_DIR)/src
INCLUDE := $(ROOT_DIR)/include
LIBS := $(ROOT_DIR)/libraries
TESTS := $(ROOT_DIR)/tests
BUILD := $(ROOT_DIR)/build
BUILD_TESTS := $(BUILD)/tests/

.PHONY: build/app clean
.DEFAULT_GOAL := build/app

build/app: $(BUILD)/main.o $(BUILD)/pixel.o
	$(CC) $^ -o $(ROOT_DIR)$(TARGET) $(LLIB)

$(BUILD)/main.o: $(SRC)/main.c | $(BUILD)
	$(CC) -c $(SRC)/main.c $(FLAGS) -o $(BUILD)/main.o

$(BUILD)/pixel.o: $(SRC)/pixel.c $(INCLUDE)/pixel.h | $(BUILD)
	$(CC) -c $(SRC)/pixel.c $(FLAGS) -o $(BUILD)/pixel.o

$(BUILD)/resize.o: $(SRC)/resize.c $(INCLUDE)/resize.h | $(BUILD)
	$(CC) -c $(SRC)/resize.c $(FLAGS) -o $(BUILD)/resize.o

$(BUILD): 
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)/*.o
	rm -rf $(BUILD)/*.gcno
	rm -rf $(BUILD)/*.gcda
	rm -rf $(BUILD_TESTS)
	rm -f $(ROOT_DIR)/$(TARGET)
	rm -f $(TESTS)/test_pixel
