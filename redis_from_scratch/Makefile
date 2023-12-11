# Makefile for C project with source code in src directory

CC = gcc
CFLAGS = -Wall
DEBUGFLAGS = -g
SRCDIR = src
OBJDIR = obj
BINDIR = bin
SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET = main

# Default build target
all: CFLAGS += $(DEBUGFLAGS)
all: $(BINDIR)/$(TARGET)

# Debug build target
debug: CFLAGS += $(DEBUGFLAGS)
debug: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/$(TARGET)

