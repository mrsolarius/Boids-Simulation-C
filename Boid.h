//
// Created by louis on 25/04/2021.
//

#ifndef FOULOSCOPIE_LOUIS_VOLAT_BOID_H
#define FOULOSCOPIE_LOUIS_VOLAT_BOID_H

#include <vector>
#include <allegro5/allegro_primitives.h>
#include "Vectors.h"

using std::vector;

class Boid {
    Vectors position;
    double velocity, direction;
    int size;
    int detectionBox;
    ALLEGRO_COLOR color{};

public:
    Boid(Vectors startPos, double velocity, int size, int detectionBox, ALLEGRO_COLOR col);

    void step(unsigned int step, vector<Vectors> boidsSee, int screenWidth, int screenHeight);

    void drawBoid();

    bool isDetected(Vectors pos);

    Vectors getPositionAndDirection();

private:
    void changeDirection(double angle);

    void randomDirectionChange();
};


#endif //FOULOSCOPIE_LOUIS_VOLAT_BOID_H
