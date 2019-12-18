#ifndef BILLIARD_GAME_HPP_
#define BILLIARD_GAME_HPP_

#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <ctime>
#include <math.h>
#include <iostream>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h

#include "myHeader.h"
#include "Ball.hpp"

#define GLM_ENABLE_EXPERIMENTAL 1
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// ################## DEFINES ##################

// Window
#define WIND_TITLE "Billiard game"
// 16:10 resolution
#define WIND_WIDTH 1280
#define WIND_HEIGHT 800

// Axis
#define X_MAX 1000
#define X_MIN 0
#define X_CEN (X_MAX + X_MIN) / 2
#define Y_MAX 625
#define Y_MIN 0
#define Y_CEN (Y_MAX + Y_MIN) / 2
#define Z_MAX 10
#define Z_MIN 0
#define Z_CEN (Z_MAX + Z_MIN) / 2

#define Z_FG 2

#define TABL_O_HEIGHT 500
#define TABL_O_WIDTH 2 * TABL_O_HEIGHT
#define TABL_MARG (TABL_O_HEIGHT / 10)
#define TABL_I_HEIGHT TABL_O_HEIGHT - 2 * TABL_MARG
#define TABL_I_WIDTH TABL_O_WIDTH - 2 * TABL_MARG
#define TABL_X_OFFS 0
#define TABL_Y_OFFS 0
#define TABL_X_CEN TABL_MARG + (TABL_I_WIDTH / 2)
#define TABL_Y_CEN TABL_MARG + (TABL_I_HEIGHT / 2)

#define BALL_RADIUS 17
#define DELT_T 1/121.f
#define DT_MS uint(DELT_T * 1000)

// ################# VARIABLES #################

GLuint VBO_ID, VAO_ID,
    COL_BUF_ID, PROG_ID;

pthread_t ball_th;
pthread_mutex_t ball_mtx = PTHREAD_MUTEX_INITIALIZER;

uint bg_o_offs = 0, bg_o_size = 6,
    bg_i_offs = bg_o_offs + bg_o_size,
    bg_i_size = 6,
    c_cen_offs = bg_i_offs + bg_i_size,
    c_cen_size = 1,
    c_qual_offs = c_cen_offs + c_cen_size,
    c_qual_size = 12,
    pt_test_offs = c_qual_offs + c_qual_size,
    pt_test_size = 1;

clock_t update_clock;
glm::mat4 axis_mat(1.f);
Ball ball;

GLfloat vertices[] = {
    // Background far
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    
    // Background close
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    
    // Circle: c=1, q=12
    0.f, 0.f, 0.f,

    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,
    0.f, 0.f, 0.f,

    // Rest of points
    0.f, 0.f, 0.f
};

GLshort colors[] = {
    150, 150, 0,
    150, 150, 0,
    150, 150, 0,
    150, 150, 0,
    150, 150, 0,
    150, 150, 0,

    0, 255, 0,
    0, 255, 0,
    0, 255, 0,
    0, 255, 0,
    0, 255, 0,
    0, 255, 0, 

    // Ball
    0,  0,  0,
    255,255,255,
    255,255,255,
    255,255,255,
    255,255,255,
    255,255,255,
    255,255,255,
    255,255,255,
    255,255,255,
    255,255,255,
    255,255,255,
    255,255,255,
    255,255,255,
    0,0,255

};

// ################# FUNCTION ##################

// ~~~~~~~~~~ Main functioons ~~~~~~~~~~
void program_init ();
void render_function ();
void normal_keyb_handler (u_char key, int xx, int yy);
void special_keyb_handler (int key, int xx, int yy);
void clean_up ();

void create_vbo ();
void destroy_vbo ();
void create_shaders ();

// ~~~~~~~~~ Other functions ~~~~~~~~~~~
void init_background_p ();

// ~~~~ Fragment sending functions ~~~~~~
void sendIntToShader (int number, char* varName);
void sendVec3ToShader (glm::vec3 vect, char* varName);
void sendVec4ToShader (glm::vec4 vect, char* varName);
void sendMat4ToShader (glm::mat4 matrix, char* varName);


// ~~~~~~~~~~ Useful functions ~~~~~
glm::vec3 get_point_at_offs (uint offset);
void set_point_at_offs (uint offset, glm::vec3 point);
void move_point (int pointOffs, int x, int y);
void init_circle (int offset, int quality, float radius);
bool timer (clock_t& last_clock, uint durr_msec); 
void* ball_update_th(void* nothing);
// ################ END OF FILE ################

#endif /** BILLIARD_GAME_HPP_*/