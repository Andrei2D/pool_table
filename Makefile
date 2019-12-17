GL_X_FLG =-lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor 
GL_GLUT_FLG	= -lGLU -lglut
GL_GLEW_FLG	=-lGLEW  -lrt -lm -pthread
GL_FLAGS 	=-I./inc -lGL $(GL_GLUT_FLG) $(GL_GLEW_FLG)

SRC_NAMES 	=loadShaders billiard_game Ball
SRC 		= $(foreach dir, $(SRC_NAMES), ./src/$(dir).cpp)
EXE 		=Billiard

all: run

build:
	g++ $(SRC) -o $(EXE) $(GL_FLAGS)
run: build
	./$(EXE)

test:
	g++ simulate.cpp
	./a.out