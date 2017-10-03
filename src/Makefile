CC = gcc
OBJ = main.o io.o
EXEC = crude
CFLAGS = -Wall

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)
	mv $(EXEC) ..

main.o: main.c main.h
	$(CC) main.c -c $(CFLAGS)

io.o: io.c io.h
	$(CC) io.c -c $(CFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)