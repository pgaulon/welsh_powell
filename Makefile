CFLAGS=-Wall -O0 -g
CC=gcc
EXEC=Welsh_Powell

all: $(EXEC)

$(EXEC): sommet.o graphe.o parser.o Welsh_Powell.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f *~ *.o
