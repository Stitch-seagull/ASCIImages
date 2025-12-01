CC = gcc
LLIB = -lncurses -lm
FLAGS = -Wall
TARGET = ASCIImages

SRC = src
INCLUDE = include
BUILD = build

.PHONY: all clean

all: $(BUILD)/main.o $(BUILD)/pixel.o
	$(CC) $^ -o $(TARGET) $(LLIB)

$(BUILD)/main.o: $(SRC)/main.c | $(BUILD)
	$(CC) -c $(SRC)/main.c $(FLAGS) -o $(BUILD)/main.o

$(BUILD)/pixel.o: $(SRC)/pixel.c $(INCLUDE)/pixel.h | $(BUILD)
	$(CC) -c $(SRC)/pixel.c $(FLAGS) -o $(BUILD)/pixel.o

$(BUILD): 
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)/*.o
	rm -f $(TARGET)
