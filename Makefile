CC=gcc
CFLAGS=-lGL -lGLU -lglut -lm

game: src/main.o src/mold.o src/shape.o src/screentext.o src/timer.o src/display.o src/init.o src/keyboard.o
	$(CC) -o game src/main.o src/mold.o src/shape.o src/screentext.o src/timer.o src/display.o src/init.o src/keyboard.o $(CFLAGS)
	
.PHONY: clean

clean:
	-rm src/*.o game
