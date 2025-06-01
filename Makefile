all: build


UNAME_S := $(shell uname -s)

prepare_build:
	@echo "PREPARING BUILD DIRECTORY..."
	@if [ ! -d "./builds" ]; then mkdir builds; fi	

build: prepare_build
	g++ -c src/reflire.cpp
	g++ -c src/datastore.cpp -I./mysql+++/  -lmysqlclient
	g++ -c src/controller.cpp 
	g++ -c src/views.cpp 
	g++ -c src/misc.cpp
	g++ -c src/main.cpp



ifeq ($(UNAME_S),Linux)
	@echo "Platform: Linux"
	g++ -o builds/reflire reflire.o views.o main.o misc.o controller.o datastore.o -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lmysqlclient 
else ifeq ($(OS),Windows_NT)
	@echo "Platform: Windows"
	g++ -o builds/reflire reflire.o views.o main.o misc.o datastore.o controller.o -g -I"C:\\raylib\\raylib\\src" -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows
else
	$(error Unsupported Platform!!) 
endif

clean:
	rm -f views.o main.o reflire.o misc.o controller.o datastore.o
	rm -rf builds

