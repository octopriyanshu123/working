# makeFile to compiling the my_program

#Compiler and FLags
CXX = g++
CXXFLAGS = -std=c++17

# SFML Library
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

TARGET = my_program

SRC = main.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Default target to build the program
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(SFML_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean

run:
	./$(TARGET)