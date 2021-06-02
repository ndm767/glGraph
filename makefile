all:
	g++ src/*.cpp src/parser/*.cpp -o glGraph -lSDL2 -lGLEW -lGL -std=c++17