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
    int hasTouch{};
    ALLEGRO_COLOR color{};

public:
    Boid(std::vector<double> startPos, double velocity, int size, double direction, int detectionBox,
         ALLEGRO_COLOR col);

    void step(unsigned int gStep, vector <vector<double>> oderEntity, int gWidth, int gHeight);

    void drawAllegro();

    bool isDetected(std::vector<double> pos);

    std::vector<double> getPositionAndDirection();

private:
    void changeDirection(double angle);
};


#endif //FOULOSCOPIE_LOUIS_VOLAT_BOID_H
