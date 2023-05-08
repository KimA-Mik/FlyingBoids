CC=g++
CFLAGS=-c -Wall -O2
SDL2 = -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image
MKDIR_P = mkdir -p
OUT_DIR = build

all: directories main.o Fly.o Proga.o Texture.o Timer.o Window.o
	cd $(OUT_DIR); \
	$(CC) main.o Fly.o Proga.o Texture.o Timer.o Window.o $(SDL2) -o main; \
	rm -rf *.o

directories: $(OUT_DIR)

$(OUT_DIR):
	$(MKDIR_P) $(OUT_DIR)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o $(OUT_DIR)/main.o

Fly.o: Fly.cpp
	$(CC) $(CFLAGS) Fly.cpp -o $(OUT_DIR)/Fly.o

Proga.o: Proga.cpp
	$(CC) $(CFLAGS) Proga.cpp -o $(OUT_DIR)/Proga.o

Texture.o: Texture.cpp
	$(CC) $(CFLAGS) Texture.cpp -o $(OUT_DIR)/Texture.o

Window.o: Window.cpp
	$(CC) $(CFLAGS) Window.cpp -o $(OUT_DIR)/Window.o

Timer.o: Timer.cpp
	$(CC) $(CFLAGS) Timer.cpp -o $(OUT_DIR)/Timer.o

clean:
	rm -rf ./build
	