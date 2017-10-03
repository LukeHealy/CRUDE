CC = gcc
EXEC = crude

all:
	$(MAKE) -C src $(EXEC)

clean:
	$(MAKE) -C src clean
	rm -f $(EXEC)