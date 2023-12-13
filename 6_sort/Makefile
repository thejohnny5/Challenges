CC=g++
CFLAGS := -Wall -std=c++17
#CFLAGS := -I/opt/homebrew/Cellar/sdl2/2.28.5/include/SDL2 -I/opt/homebrew/Cellar/sdl2_image/2.6.3_2/include/SDL2 -Wall -std=c++11
#LDFLAGS := -L/opt/homebrew/Cellar/sdl2/2.28.5/lib -lSDL2 -L/opt/homebrew/Cellar/sdl2_image/2.6.3_2/lib -lSDL2_image
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
ARGPARSER_SRC_DIR := ../parsing_util/src
ARGPARSER_OBJ_DIR := ../parsing_util/obj

SOURCES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(ARGPARSER_SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(wildcard $(SRC_DIR)/*.cpp)) \
           $(patsubst $(ARGPARSER_SRC_DIR)/%.cpp,$(ARGPARSER_OBJ_DIR)/%.o,$(wildcard $(ARGPARSER_SRC_DIR)/*.cpp))


TARGET := $(BIN_DIR)/csort
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ARGPARSER_OBJ_DIR)/%.o: $(ARGPARSER_SRC_DIR)/%.cpp
	mkdir -p $(ARGPARSER_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)  $(ARGPARSER_OBJ_DIR)
