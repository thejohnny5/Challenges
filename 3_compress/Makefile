CC=g++
CFLAGS := -Wall -std=c++17
#CFLAGS := -I/opt/homebrew/Cellar/sdl2/2.28.5/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.6.3_2/include/SDL2 -Wall -std=c++11
#LDFLAGS := -L/opt/homebrew/Cellar/sdl2/2.28.5/lib -lSDL2 -L/opt/homebrew/Cellar/sdl2_image/2.6.3_2/lib -lSDL2_image
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
TARGET := $(BIN_DIR)/compress
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
