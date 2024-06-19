GCC		  := g++
FLAGS := -Wall -Wextra -w -Wno-unused-parameter -std=c++11 -ggdb

BIN		:= bin
SRC		:= source
INCLUDE	:= includes
LIB		:= lib

LIBS	:= -lsfml-graphics -lsfml-window -lsfml-system
EXECUTABLE	:= main

MKDIR_P = mkdir -p

.PHONY: directories

all: directories $(BIN)/$(EXECUTABLE)

directories: ${BIN}

${BIN}:
	${MKDIR_P} ${BIN}

run: clean all
	
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(GCC) $(FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBS)

clean:
	-rm $(BIN)/*