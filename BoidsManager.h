//
// Created by louis on 06/04/2021.
//

#ifndef FOULOSCOPIE_LOUIS_VOLAT_BOIDSMANAGER_H
#define FOULOSCOPIE_LOUIS_VOLAT_BOIDSMANAGER_H
#include <vector>
#include "Boid.h"

class BoidsManager {
    int totalEntities;
    int currentEntities;
    int screenWidth;
    int screenHeight;
    std::vector<Boid> entities;
public:
    BoidsManager(int gNbEntities, int gWidth, int gHeight);
    void step(unsigned int step);
    void drawBoids();
private:
    void generateEntity();
};

#endif //FOULOSCOPIE_LOUIS_VOLAT_BOIDSMANAGER_H
