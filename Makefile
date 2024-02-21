CC = gcc
CFLAGS = -Wall -Wfatal-errors -std=c17
OBJETS = src/Position.o src/main.o src/Graphique.o

all: main

main: $(OBJETSETS)
	$(CC) $(CFLAGS) -o $@ $^ -lncurses -lm
	make clean

src/Graphique.o : src/Graphique.c src/Graphique.h
	mkdir -p src
	$(CC) $(CFLAGS) -o $@ -c $<

src/Position.o:  src/Position.c src/Position.h
	mkdir -p src
	$(CC) $(CFLAGS) -o $@ -c $<

src/main.o: src/main.c
	mkdir -p src
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -r src

cleanExe:

	rm -f main