all: build 


prepare_build:
	echo "PREPARING BUILDS DIRECTORY..."
	if [ ! -d "./builds" ]; then mkdir builds; fi	

build : prepare_build
	g++ -c src/reflire.cpp
	g++ -c src/controller.cpp
	g++ -c src/views.cpp 
	g++ -c src/main.cpp
	g++ -c src/misc.cpp

	g++ -o builds/reflires.exe reflire.o views.o main.o misc.o controller.o  -g -I"C:\\raylib\raylib\src" -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows


clean:
	rm views.o main.o reflire.o misc.o controller.o
	rm -rf builds
