.SUFFIXES: .c .h .x .o

CFLAGS = -pedantic -Wall -std=c++11
LFLAGS = -pedantic -Wall -std=c++11
CO = g++
LD = $(CO)

NAME1 = main

OBJS1 = $(NAME1).o

EXEC1 = $(NAME1).x

.PHONY: help
help:
	@echo "make all		Kompiluje wszystkie programy"
	@echo "make run-all	Uruchamia wszystkie programy"
	@echo "make run-$(NAME1)    Uruchamia program $(NAME1)"
	@echo "make clean	Usuwa pliki *.o oraz *.x"
.PHONY: all
all: $(EXEC1) 

$(EXEC1): $(OBJS1)
	$(LD) $(LFLAGS) $^ -o $@ -lsfml-graphics -lsfml-window -lsfml-system

%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<

.PHONY: run-$(EXEC1) 
run-$(NAME1): $(EXEC1)
	./$(EXEC1)

.PHONY: clean

clean:
	rm *.o *.x

.PHONY: run-all
run-all: $(EXEC1) 
	./$(EXEC1)
	

