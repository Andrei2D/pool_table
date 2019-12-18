#ifndef BALL_HPP_
#define BALL_HPP_

#include <unistd.h>     // for NULL
#include <math.h>       // for sin and cos
#include <GL/glew.h>    // for self drawing

#define PI 3.1415926f
#define RAD_NORM(angl) (angl >= 2 * PI ? angl - 2 * PI: \
                        angl < 0 ? angl + 2*PI: \
                        angl)
// #define EM_1(angl) (angl >= 0       &&  angl < 0.5f * PI)
// #define EM_2(angl) (angl >= 1.5f * PI && angl < 2 * PI)
// #define EM_3(angl) (angl >= PI      &&  angl < 1.5f * PI)
// #define EM_4(angl) (angl >= 0.5f * PI && angl < 1.5f * PI)

#define EMS_1 1
#define EMS_2 2
#define EMS_3 3
#define EMS_4 4

#define RAD_EMISF(angl) (angl < 0.5f * PI ? EMS_1 :\
                        angl < 1.f * PI ? EMS_4 :\
                        angl < 1.5f * PI ? EMS_3 :\
                        EMS_2)

struct Ball {
    static uint update_rate_ms;
    static float rot_angle;
    static float fric_force;

    float x; 
    float y;
    float radius;
    double alfa;
    float dist, veloc, acc;
    int lim_x_top, lim_y_top;
    int lim_x_bot, lim_y_bot;

    Ball ();
    void set (int init_x, int init_y, float radius) ;
    void set_limits (int x_t, int y_t, int x_b, int y_b);
    void check_limits ();
    void update ();
    void move ();
    void draw (GLfloat* vertex, int quality, float z_elm);
    void act_on (float force);
    void rotate_cw();
    void rotate_ccw();
    void angl_X_shift();
    void angl_Y_shift();
    void change_distance(float new_dist);
};

#endif /* BALL_HPP_ */