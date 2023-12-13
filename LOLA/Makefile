CC=gcc
CFLAGS := -Wall -g -O0  # Added debug flags
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# Find all .c files in SRC_DIR
SOURCES := $(wildcard $(SRC_DIR)/*.c)

# Substitute .c to .o and set path to OBJ_DIR
OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

TARGET := $(BIN_DIR)/lola_SQIRREL

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

# Changed from %.cpp to %.c
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)  # Modified to also remove BIN_DIR

