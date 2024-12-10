all: build 

build :
		 g++ -o reflires main.cpp -g -I"C:\\raylib\raylib\src" -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows
