# Makefile for compiling and running the semaphore example with threads

CXX = g++                   # Compiler to use (g++ for C++)
CXXFLAGS = -std=c++2a -Wall  # C++20 standard with all warnings
TARGET = share_ptr_example   # Output executable name

# Default target
all: $(TARGET)

# How to build the executable
$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp -pthread

# Clean up the compiled files
clean:
	rm -f $(TARGET)

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Help message
help:
	@echo "Makefile for semaphore example"
	@echo "Usage:"
	@echo "  make        - Build the executable"
	@echo "  make clean  - Remove the compiled files"
	@echo "  make run    - Build and run the executable"
	@echo "  make help   - Show this help message"
