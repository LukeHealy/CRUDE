OBJ = main.o io.o db_handler.o
CC = gcc
EXEC = crude
CFLAGS = -Wall

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)
	mv $(EXEC) ..

main.o: main.c main.h
	$(CC) main.c -c $(CFLAGS)

io.o: io.c io.h
	$(CC) io.c -c $(CFLAGS)

db_handler.o: db_handler.c db_handler.h
	$(CC) db_handler.c -c $(CFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)
