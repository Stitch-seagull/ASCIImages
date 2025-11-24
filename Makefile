CC = gcc
LLIB = -lncurses -lm
FLAGS = -Wall
TARGET = ASCIImages

SRC = src
BUILD = build

.PHONY: all clean

all: $(BUILD)/main.o
	$(CC) $(BUILD)/main.o -o $(TARGET) $(LLIB)

$(BUILD)/main.o: $(SRC)/main.c | $(BUILD)
	$(CC) -c $(SRC)/main.c $(FLAGS) -o $(BUILD)/main.o

$(BUILD): 
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)/*.o
	rm -f $(TARGET)
