# Compiler
CC = gcc

# Directories
SRC = src
OBJ = obj
BIN = bin

OBJS = \
	$(OBJ)/json_parse.o \
	$(OBJ)/str_vector.o

# Flags - include
CFLAGS = -g -Wall -I $(OBJ)

# Target executable
TARGET = $(BIN)/jparser

all: $(TARGET)

# Rule to link object files and create the executable
$(TARGET): $(OBJS) $(OBJ)/main.o
	$(CC) -o $(TARGET) $(OBJS) $(OBJ)/main.o

# Make all object files in obj directory
$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@


# Build Tests
TESTS = tests
T_TARGET = $(TESTS)/bin/test_jparser
T_FLAGS = -I $(TESTS)/$(OBJ) -I $(SRC)

T_OBJS = \
	$(TESTS)/$(OBJ)/test_svec.o \
	$(TESTS)/$(OBJ)/test_jdict.o \

test: $(T_TARGET)

# Directory checks
$(T_TARGET): $(OBJ) $(T_OBJS)
	$(CC) $(T_FLAGS) -o $(T_TARGET) $(T_OBJS) $(OBJS) $(TESTS)/test.c

$(TESTS)/$(OBJ)/%.o: $(TESTS)/%.c
	$(CC) $(CFLAGS) $(T_FLAGS) -c $< -o $@




# Clean rule to remove object files and the executable
clean:
	rm -rf $(OBJ)/* $(BIN)/* tests/bin/* tests/obj/*
