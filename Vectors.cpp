//
// Created by louis on 25/04/2021.
//

#include "Vectors.h"


void Vectors::setAll(int x, int y, double angle) {
    this->x = x;
    this->y = y;
    this->angle = angle;
}

void Vectors::setCoordinate(int x, int y) {
    this->x = x;
    this->y = y;
}

double Vectors::distance(Vectors v) {
    //Utilisation du téoreme de pytagore
    double x = pow(v.x-this->x,2);
    double y = pow(v.y-this->y,2);
    return sqrt(x+y);
}

double Vectors::angleBetween(Vectors v) {
    return atan((v.y-y)/(v.x-x));
}

