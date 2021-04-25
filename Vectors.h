//
// Created by louis on 25/04/2021.
//

#ifndef FOULOSCOPIE_LOUIS_VOLAT_VECTORS_H
#define FOULOSCOPIE_LOUIS_VOLAT_VECTORS_H

#include <math.h>

class Vectors {
public:
    //Position sur la grille
    int x;
    int y;
    //Angle de rotation par raport a x
    double angle;
    /**
     * Methode setAll
     * Permet de definir tous les paramettre d'un vecteur d'un coup
     * @param x
     * @param y
     * @param angle
     */
    void setAll(int x, int y, double angle);

    /**
     * Methode setCoordinate
     * Permet de definir uniquement les coordonées du vecteur
     * @param x
     * @param y
     */
    void setCoordinate(int x, int y);

    /**
     * Methode distance
     * Permet de renvoyer la distance en px entre le vecteur actif et un autre vecteur
     * @param v2
     * @return double
     */
    double distance(Vectors v);

    /**
     * Methode angleBetween
     * Permet de faire l'arctanjent entre le vecteur actuel et le vecteur passer en paramettre
     * @param vectors
     * @return
     */
    double angleBetween(Vectors v);
};


#endif //FOULOSCOPIE_LOUIS_VOLAT_VECTORS_H
