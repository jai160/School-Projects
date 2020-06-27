SRC = jimmy_fallon.c
OBJ = jimmy_fallon.o
PROG = test

$(PROG): $(OBJ)
	gcc $(OBJ) -pthread -o $(PROG) 

$(OBJ): $(SRC)