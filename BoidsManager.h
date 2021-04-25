//
// Created by louis on 06/04/2021.
//

#ifndef FOULOSCOPIE_LOUIS_VOLAT_BOIDSMANAGER_H
#define FOULOSCOPIE_LOUIS_VOLAT_BOIDSMANAGER_H
#include <vector>
#include "Boid.h"

class BoidsManager {
    //Nombre totale d'oisoïde demander
    int totalBoids;
    //Nombre acutel d'oisoïde
    int currentBoids;
    //Collection d'oisoïde
    std::vector<Boid> boids;

    //Taille de l'écran
    int screenWidth;
    int screenHeight;
public:
    BoidsManager(int totalBoids, int gWidth, int gHeight);
    void step(unsigned int step);
    void drawBoids();
private:
    void generateEntity();
};

#endif //FOULOSCOPIE_LOUIS_VOLAT_BOIDSMANAGER_H
