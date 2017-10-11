OBJ = main.o io.o db_handler.o
CC = gcc
EXEC = crude
VULN = -fno-stack-protector -z execstack
CFLAGS = -Wall -g $(VULN)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(VULN)
	mv $(EXEC) ..

main.o: main.c main.h io.h db_handler.h employee.h
	$(CC) main.c -c $(CFLAGS)

io.o: io.c io.h
	$(CC) io.c -c $(CFLAGS)

db_handler.o: db_handler.c db_handler.h employee.h io.h
	$(CC) db_handler.c -c $(CFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)
