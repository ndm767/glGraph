all:
	g++ src/*.cpp src/parser/*.cpp src/renderer/*.cpp -o glGraph -lSDL2 -lGLEW -lGL -std=c++17