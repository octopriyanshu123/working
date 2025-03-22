# Makefile for Semaphore Example

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -pthread

# Directories
SRC_DIR = .
OBJ_DIR = obj

# Source files
SRCS = $(SRC_DIR)/my_semaphore.cpp $(SRC_DIR)/main.cpp

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Executable name
EXEC = semaphore_example

# Targets

# Default target (build executable)
all: $(EXEC)

# Rule to build the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

# Rule to build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -rf $(OBJ_DIR) $(EXEC)

# Rule to run the program
run: $(EXEC)
	./$(EXEC)

# Rule to recompile everything
rebuild: clean all
