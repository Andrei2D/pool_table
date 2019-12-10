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

// Window
#define WIND_TITLE "Billiard game"
#define WIND_WIDTH 1280
#define WIND_HEIGHT 800

// Axis
#define X_MAX 1000
#define X_MIN 0
#define X_CEN (X_MAX + X_MIN) / 2
#define Y_MAX 1000
#define Y_MIN 0
#define Y_CEN (Y_MAX + Y_MIN) / 2
#define Z_MAX 10
#define Z_MIN 0
#define Z_CEN (Z_MAX + Z_MIN) / 2


// Table
#define TABL_I_HEIGHT 500
#define TABL_I_WIDTH 2 * TABL_I_HEIGHT
#define TABL_MARG (TABL_I_HEIGHT * 2) / 5
#define TABL_O_HEIGHT 2 * TABL_MARG + TABL_I_HEIGHT
#define TABL_O_WIDTH 2 * TABL_MARG + TABL_O_HEIGHT
#define TABL_X_OFFS 0
#define TABL_Y_OFFS 0


// ################# VARIABLES #################

GLuint VBO_ID, VAO_ID,
    COL_BUF_ID, PROG_ID;

uint bg_o_offs = 0, bg_o_size = 6,
    bg_i_offs = bg_o_offs + bg_o_size,
    bg_i_size = 6;

glm::mat4 axis_mat(1.f);

GLfloat vertices[] = {
    500.f, 500.f, 1.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f
};

GLshort colors[] = {
    255, 0, 0,
    255, 0, 0,
    255, 0, 0,
    255, 0, 0,
    255, 0, 0,
    255, 0, 0,
    
    0, 255, 0,
    0, 255, 0,
    0, 255, 0,
    0, 255, 0,
    0, 255, 0,
    0, 255, 0
};

// ################# FUNCTION ##################

// ~~~~~~~~~~ Main functioons ~~~~~~~~~~
void program_init ();
void render_function ();
void normal_keyb_handler (u_char key, int xx, int yy);
void special_keyb_handler (int key, int xx, int yy);
void clean_up ();

// ~~~~~~~~~ Other functions ~~~~~~~~~~~
void init_background_p ();
void create_vbo ();
void destroy_vbo ();
void create_shaders ();

// ~~~~ Fragment sending functions ~~~~~~
void sendIntToShader (int number, char* varName);
void sendVec3ToShader (glm::vec3 vect, char* varName);
void sendVec4ToShader (glm::vec4 vect, char* varName);
void sendMat4ToShader (glm::mat4 matrix, char* varName);


// ~~~~~~~~~~ Useful functions ~~~~~
glm::vec3 getPointAtOffs (uint offset);
void setPoinAtOffs (uint offset, glm::vec3 point);
void movePoint (int pointOffs, int x, int y);

// ################ END OF FILE ################

#endif /** BILLIARD_GAME_HPP_*/