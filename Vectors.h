//
// Created by louis on 25/04/2021.
//

#ifndef FOULOSCOPIE_LOUIS_VOLAT_VECTORS_H
#define FOULOSCOPIE_LOUIS_VOLAT_VECTORS_H

#include <math.h>

class Vectors {
public:
    int x;
    int y;
    double angle;
    void setAll(int x, int y, double angle);
    void setCoordinate(int x, int y);
    double distance(Vectors v2);
    Vectors subtractTwoVector(Vectors v1, Vectors v2);
    void normalize();
    float magnitude();

    void divScalar(float s);

    void addVector(Vectors vectors);

    float angleBetween(Vectors vectors);
};


#endif //FOULOSCOPIE_LOUIS_VOLAT_VECTORS_H
