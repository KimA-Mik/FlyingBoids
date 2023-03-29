CC=g++
CFLAGS=-c -Wall -O2
SDL2 = -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image

all: main.o Fly.o Proga.o Texture.o Timer.o Window.o
	$(CC) main.o Fly.o Proga.o Texture.o Timer.o Window.o $(SDL2) -o main

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Fly.o: Fly.cpp
	$(CC) $(CFLAGS) Fly.cpp

Proga.o: Proga.cpp
	$(CC) $(CFLAGS) Proga.cpp

Texture.o: Texture.cpp
	$(CC) $(CFLAGS) Texture.cpp

Window.o: Window.cpp
	$(CC) $(CFLAGS) Window.cpp

Timer.o: Timer.cpp
	$(CC) $(CFLAGS) Timer.cpp

clean:
	rm -rf *.o
 
 
