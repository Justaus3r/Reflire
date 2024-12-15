all: build


UNAME_S := $(shell uname -s)

prepare_build:
	@echo "PREPARING BUILD DIRECTORY..."
	@if [ ! -d "./builds" ]; then mkdir builds; fi	

build: prepare_build
	g++ -c src/reflire.cpp
	g++ -c src/controller.cpp
	g++ -c src/views.cpp 
	g++ -c src/main.cpp
	g++ -c src/misc.cpp



ifeq ($(UNAME_S),Linux)
	@echo "Platform: Linux"
	g++ -o builds/reflire reflire.o views.o main.o misc.o controller.o -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
else ifeq ($(OS),Windows_NT)
	@echo "Platform: Windows"
	g++ -o builds/reflire reflire.o views.o main.o misc.o controller.o -g -I"C:\\raylib\\raylib\\src" -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows
else
	$(error Unsupported Platform!!) 
endif

clean:
	rm -f views.o main.o reflire.o misc.o controller.o
	rm -rf builds

