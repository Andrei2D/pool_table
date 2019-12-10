#ifndef BILLIARD_GAME_HPP_
#define BILLIARD_GAME_HPP_

#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h

#include "myHeader.h"

#define GLM_ENABLE_EXPERIMENTAL 1
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// ################## DEFINES ##################

#define WIND_TITLE "Billiard game"
#define WIND_WIDTH 1280
#define WIND_HEIGHT 800

#define X_MAX 500
#define X_MIN -X_MAX
#define Y_MAX 500
#define Y_MIN -Y_MAX
#define Z_MAX 10
#define Z_MIN -Y_MAX

// ################# VARIABLES #################

GLuint VBO_ID, VAO_ID,
    COL_BUF_ID, PROG_ID;

GLfloat vertices[] = {
    10.f, 20.f, 1.f
};

GLshort colors[] = {

};

// ################# FUNCTION ##################

// ~~~~~~~~~~ Main functioons ~~~~~~~~~~
void program_init ();
void render_function ();
void normal_keyb_handler ();
void special_keyb_handler ();
void clean_up ();

// ~~~~~~~~~ Other functions ~~~~~~~~~~~
void create_vbo ();
void destroy_vbo ();
void create_shaders ();


// ################ END OF FILE ################

#endif /** BILLIARD_GAME_HPP_*/