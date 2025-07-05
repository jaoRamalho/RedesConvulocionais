SRC = src/main.cpp \
      src/Neuron.cpp \
	  src/Log.cpp 

INCLUDE = include/Neuron.h \
		  include/Layer.h \
		  include/Network.h \
		  include/Log.hpp \
		  include/ModulesNames.h 

OBJ = $(SRC:src/%.cpp=obj/%.o)

all: clean project

project: $(OBJ)
	g++ -std=c++17 -Wall -I. -Iinclude -o project $(OBJ)

obj/%.o: src/%.cpp
	@mkdir -p obj
	g++ -std=c++17 -Wall -I. -Iinclude -c $< -o $@

clean:
	rm -f $(OBJ) project

.PHONY:	all clean