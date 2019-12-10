#ifndef BALL_HPP_
#define BALL_HPP_

#include <unistd.h>     // for NULL
#include <math.h>       // for sin and cos
#include <GL/glew.h>    // for self drawing

#define PI 3.1415926

struct Ball {

    float* x; 
    float* y;
    float radius;
    double alfa;
    float dist, veloc, acc, fric_coef;

    Ball ();
    void set (float* mem_beginn, float radius);
    void update ();
    void move ();
    void draw (GLfloat* vertex, int quality, float z_elm);
};

#endif /* BALL_HPP_ */