#include "Ball.hpp"

Ball::Ball () {
    x = NULL;
    y = NULL;
    radius = 0;
    alfa = 0;
    dist = veloc = acc = fric_coef = 0;
}


void Ball::set (float* mem_beginn, float radius) {
    x = mem_beginn;
    y = mem_beginn  + 1;
    this->radius = radius;
}

void Ball::update () {
    veloc += acc;
    dist += veloc;
    move ();
    acc += fric_coef * veloc * veloc;
}

void Ball::move () {
    *x += cos (alfa) * dist;
    *y += sin (alfa) * dist;
}


void Ball::draw (GLfloat* vertex, int quality, float z_elm) {
    double measure = (2*PI) / quality, angle = 0;
    float old_val[3];
    vertex[0] = *x;
    vertex[1] = *y;
    vertex[2] = z_elm;
    vertex += 3;
    
    for (int ind = 0; ind < quality; ind ++) {
        vertex[0] = *x + cos (angle) * radius;
        vertex[1] = *y + sin (angle) * radius;
        vertex[2] = z_elm;

        vertex += 3;
        angle += measure;
    }
    
}