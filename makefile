# Makefile for Neural Network project
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I. -Iinclude

DIR_SRC = src
DIR_OBJ = obj
DIR_INC = include

SRC = $(DIR_SRC)/main.cpp \
      $(DIR_SRC)/Neuron.cpp 

OBJ = $(SRC:$(DIR_SRC)/%.cpp=$(DIR_OBJ)/%.o)

all: clean project

project: $(OBJ)
	$(CXX) $(CXXFLAGS) -o project $(OBJ)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.cpp
	@mkdir -p $(DIR_OBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) project

.PHONY:	all clean