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
    /**
     * Constructeur BoidsManager
     * @param totalBoids nombre total de boid à simuler
     * @param screenWidth largeur de l'écran en px
     * @param screenHeight hauteur de l'écran en px
     */
    BoidsManager(int totalBoids, int screenWidth, int screenHeight);

    /**
     * Methode Step
     * Permet de calculer une nouvelle etape de simulation
     * @param step
     */
    void step(unsigned int step);

    /**
     * Methode drawBoids
     * Permet d'afficher à l'écran tous les boid
     */
    void drawBoids();
private:
    /**
     * Methode generateBoid
     * Permet de générer des boid
     */
    void generateBoid();
};

#endif //FOULOSCOPIE_LOUIS_VOLAT_BOIDSMANAGER_H
