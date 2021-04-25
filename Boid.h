//
// Created by louis on 25/04/2021.
//

#ifndef FOULOSCOPIE_LOUIS_VOLAT_BOID_H
#define FOULOSCOPIE_LOUIS_VOLAT_BOID_H

#include <vector>
#include <allegro5/allegro_primitives.h>

using std::vector;

class Boid {
    std::vector<double> position;
    double velocity, direction;
    int size;
    int detectionBox;
    ALLEGRO_COLOR color{};

public:
    Boid(std::vector<double> startPos, double velocity, int size, double direction, int detectionBox, ALLEGRO_COLOR col);

    void step(unsigned int step, vector<vector<double>> boidSee, int screenWidth, int screenHeight);

    void drawBoid();

    bool isDetected(std::vector<double> pos);

    std::vector<double> getPositionAndDirection();

private:
    void changeDirection(double angle);
};


#endif //FOULOSCOPIE_LOUIS_VOLAT_BOID_H
