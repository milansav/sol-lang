all: build

CC = gcc
CFLAGS = -O2 -std=c99

bd = build/
objects = $(bd)main.o $(bd)lexer.o $(bd)lexeme.o $(bd)keywords.o $(bd)parser.o $(bd)debug.o $(bd)file.o

debug: $(objects)
	$(CC) -o sol -g $(objects)

clean:
	rm $(bd)*.o
	rm $(bd)sol

build: $(objects)
	$(CC) -o $(bd)sol $(objects)

%/main.o: src/main.c
	$(CC) -c $< $(CFLAGS) -o $@

%/lexer.o: src/lexer/lexer.c
	$(CC) -c $< $(CFLAGS) -o $@

%/lexeme.o: src/lexer/lexeme.c
	$(CC) -c $< $(CFLAGS) -o $@

%/keywords.o: src/common/keywords.c
	$(CC) -c $< $(CFLAGS) -o $@

%/parser.o: src/parser/parser.c
	$(CC) -c $< $(CFLAGS) -o $@

%/debug.o: src/common/debug.c
	$(CC) -c $< $(CFLAGS) -o $@

%/file.o: src/util/file.c
	$(CC) -c $< $(CFLAGS) -o $@

install: build
	cp build/sol /usr/bin/sol