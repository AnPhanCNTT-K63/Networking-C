all:
	g++ -Isrc/Include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_net -lSDL2_image -lSDL2_ttf
