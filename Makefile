all: build

debug: build/main.o build/lexer.o build/lexeme.o
	gcc -o sol.out -g build/main.o build/lexer.o build/lexeme.o

clean:
	rm *.o

build: build/main.o build/lexer.o build/lexeme.o
	gcc -o sol.out build/main.o build/lexer.o build/lexeme.o

build/main.o: src/main.c
	gcc -c src/main.c -o build/main.o -O2 -std=c99

build/lexer.o: src/lexer/lexer.c
	gcc -c src/lexer/lexer.c -o build/lexer.o -O2 -std=c99

build/lexeme.o: src/lexer/lexeme.c
	gcc -c src/lexer/lexeme.c -o build/lexeme.o -O2 -std=c99
