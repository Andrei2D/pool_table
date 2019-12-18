#include "Ball.hpp"

uint Ball::update_rate_ms = 30;
float Ball::rot_angle = PI / 6;
float Ball::fric_force = 0.1f;

Ball::Ball () {
    x = 0;
    y = 0;
    radius = 0;
    alfa = 0;
    dist = veloc = acc = 0;
    lim_x_top = lim_y_top = lim_x_bot = lim_y_bot = 0;
}

void Ball::set (int init_x, int init_y, float radius) {
    x = init_x;
    y = init_y;
    this->radius = radius;
}

void Ball::set_limits (int x_t, int y_t, int x_b, int y_b) {
    lim_x_top = x_t;
    lim_y_top = y_t;
    lim_x_bot = x_b;
    lim_y_bot = y_b;
}

void Ball::check_limits () {
    if (x - radius <= lim_x_top || x + radius >= lim_x_bot) 
        angl_Y_shift();
    
    if (y - radius <= lim_y_top || y + radius >= lim_y_bot) 
        angl_X_shift();
}

void Ball::update () {
    veloc += acc;
    dist += veloc;
    move ();
    check_limits ();
    if (veloc <= 0) {
        veloc = 0;
        acc = 0;
    } 
    else {
        acc -= this->fric_force;
    }
}

void Ball::move () {
    float calc_x = x + sin (alfa) * dist;
    float calc_y = y - cos (alfa) * dist;
    x = (calc_x - radius <= lim_x_top ? lim_x_top + radius:
        calc_x + radius >= lim_x_bot ? lim_x_bot - radius:
        calc_x);
    y = (calc_y - radius <= lim_y_top ? lim_y_top + radius:
        calc_y + radius >= lim_y_bot ? lim_y_bot - radius:
        calc_y);
    dist = 0;
}

void Ball::draw (GLfloat* vertex, int quality, float z_elm) {
    double measure = (2*PI) / quality, angle = 0;
    float old_val[3];
    vertex[0] = x;
    vertex[1] = y;
    vertex[2] = z_elm;
    vertex += 3;
    
    for (int ind = 0; ind < quality; ind ++) {
        vertex[0] = x + cos (angle) * radius;
        vertex[1] = y + sin (angle) * radius;
        vertex[2] = z_elm;

        vertex += 3;
        angle += measure;
    }
    
}

void Ball::act_on (float force) {
    this->acc = force;
}

void Ball::rotate_cw() {
    alfa += this->rot_angle;
    alfa = RAD_NORM(alfa);
}

void Ball::rotate_ccw() {
    alfa -= this->rot_angle;
    alfa = RAD_NORM(alfa);
}

void Ball::angl_X_shift() {
    switch (RAD_EMISF(alfa)) {
        case EMS_1:  //[0, 90)
        case EMS_4:  // [90, 180)
        {
            // For RIGHT side emispheres the formula is:
            // R(alfa) = 2 * 90(deg) - alfa
            alfa = 2 * (PI / 2) - alfa;
            break;
        }
        case EMS_2: // [270, 360)
        case EMS_3: // [180, 270)
        {
            // For LEFT side emispheres the formula is:
            // L(alfa) = 2 * 270(deg) - alfa
            alfa = 2 * (3 * PI / 2.f) - alfa;
            break;
        }
    }
}

void Ball::angl_Y_shift() {
    /** For some reason there is the same formula for all
     * the emispheres. 
     * Namely Sh_Y(alfa) = 2 * 180(deg) - alfa
     */
    alfa = 2 * PI - alfa;
}

void Ball::change_distance(float new_dist) {
    this->dist = new_dist;
    this->move();
}