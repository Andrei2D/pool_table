
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace std;

float dist, veloc, acc, fric_coef;
float dt = 0.03;

void update () {

    veloc += acc * dt;
    dist += veloc * dt;
    acc += fric_coef * veloc ;


    if (veloc <= 0) {
        veloc = 0;
        acc = 0;
    }
}

void outy () {
    printf ("\t %.3f \t %.3f \t %.3f \t| %.3f \n",
        dist, veloc, acc, fric_coef);
}

int main () {
    dist = 0;
    veloc = 0;
    acc = 0;
    fric_coef = -0.5;

    int c;
    while (true) {
        cout << "> ";
        cin >> c;
        update ();
        if (c == 0) {
            veloc += 10;
        }
        outy();
    }

    return 0;
}