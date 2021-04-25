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
    // Représentation de la position et de l'angle du boid
    Vectors vectorPosition;
    // Indique la vitesse à laquel se déplace un boid (compris entre 1.5 et 5)
    double velocity;
    // Représente la taille du boid
    int size;
    // Représente le champs de vision du boid
    int detectionBox;
    // Indique la couleur du boid
    ALLEGRO_COLOR color{};

public:
    /**
     * Constructor Boid
     * @param startPos indique la position inisial du boid
     * @param velocity indique sa vélocité inisial
     * @param size indique la taille du boid
     * @param detectionBox indique la taille du champs de vision du boid
     * @param color indique la couleur du boid
     */
    Boid(Vectors startPos, double velocity,int size,int detectionBox, ALLEGRO_COLOR color);

    /**
     * Methode step
     * Permmet de mettre à jour les donnes du boid et d'editer c'est variable
     * @param boidsSee Listes de tous les boid vue au tour précédent à l'aide de la methode isSee()
     * @param screenWidth taille de la fenêtre horizontal en px
     * @param screenHeight taille de la fenêtre vertial en px
     */
    void step(vector<Vectors> boidsSee, int screenWidth, int screenHeight);

    /**
     * Methode drawBoid
     * Permet de déssiner le bloid dans alegros tant que le backbuffer et ouvert
     */
    void drawBoid();

    /**
     * Methode isSee
     * Permet de savoir si un vecteur de position peut être vue par ce boid
     * @param pos position de l'empalcement à détécter
     * @return true si il est visible false si il est pas visible
     */
    bool isSee(Vectors pos);

    /**
     * Methode getPositionAndDirection
     * Permet de renvoyer la position actuel du boid sur la grille
     * @return Le vecteur de position actuel du boid
     */
    Vectors getPositionAndDirection();

private:

    /**
     * Methode changeDirection
     * Permet de changer de direction vers un angle definit
     * Ajoutera ou elevera de la vélocité en fonction de l'angle choisie
     * @param angle
     */
    void changeDirection(double angle);

    /**
     * Methode randomDirectionChange
     * Permet de générer une direction alléatoir à partir de la direction actuel
     */
    void randomDirectionChange();
};


#endif //FOULOSCOPIE_LOUIS_VOLAT_BOID_H
