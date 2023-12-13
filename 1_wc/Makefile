CC=g++
CFLAGS := -Wall -std=c++17 -g
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
ARGPARSER_SRC_DIR := ../parsing_util/src
ARGPARSER_OBJ_DIR := ../parsing_util/obj
TEST_DIR := test
GTEST_DIR := /opt/homebrew/Cellar/googletest/1.14.0


# Exclude main.cpp from the list of source files for the test target
APPLICATION_SOURCES := $(filter-out $(SRC_DIR)/main.cpp, $(wildcard $(SRC_DIR)/*.cpp))
APPLICATION_OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(APPLICATION_SOURCES))
ARGPARSER_OBJECTS := $(patsubst $(ARGPARSER_SRC_DIR)/%.cpp,$(ARGPARSER_OBJ_DIR)/%.o,$(wildcard $(ARGPARSER_SRC_DIR)/*.cpp))
TEST_SOURCES := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJECTS := $(patsubst $(TEST_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(TEST_SOURCES))

TARGET := $(BIN_DIR)/ccwc # Change this to your main application name
TEST_TARGET := $(BIN_DIR)/runTests

all: $(TARGET)

$(TARGET): $(APPLICATION_OBJECTS) $(ARGPARSER_OBJECTS)
	mkdir -p $(BIN_DIR)
	$(CC) $(APPLICATION_OBJECTS) $(ARGPARSER_OBJECTS) -o $@

$(TEST_TARGET): $(APPLICATION_OBJECTS) $(ARGPARSER_OBJECTS) $(TEST_OBJECTS)
	$(CC) $(APPLICATION_OBJECTS) $(ARGPARSER_OBJECTS) $(TEST_OBJECTS) -o $@ -lgtest -lpthread

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(GTEST_DIR)/include -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(SRC_DIR) -I$(GTEST_DIR)/include -c $< -o $@

$(ARGPARSER_OBJ_DIR)/%.o: $(ARGPARSER_SRC_DIR)/%.cpp
	mkdir -p $(ARGPARSER_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(TEST_TARGET) $(ARGPARSER_OBJ_DIR)

test: $(TEST_TARGET)

.PHONY: all test clean