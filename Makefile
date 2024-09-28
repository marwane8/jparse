# Compiler
CC = gcc

# Directories
SRC_DIR = src
JLIB_DIR = $(SRC_DIR)/jlib
BUILD_DIR = build

# Files
MAIN_SRC = $(SRC_DIR)/main.c
JLIB_SRC = $(JLIB_DIR)/strvec.c
OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/strvec.o

# Flags
CFLAGS = -I $(JLIB_DIR)

# Target executable
TARGET = $(BUILD_DIR)/jparser

# Default rule to build the executable
all: $(BUILD_DIR) $(TARGET)

# Rule to link object files and create the executable
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

# Rule to compile main.c
$(BUILD_DIR)/main.o: $(MAIN_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(MAIN_SRC) -o $(BUILD_DIR)/main.o

# Rule to compile strvec.c
$(BUILD_DIR)/strvec.o: $(JLIB_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(JLIB_SRC) -o $(BUILD_DIR)/strvec.o

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean rule to remove object files and the executable
clean:
	rm -rf $(BUILD_DIR)
