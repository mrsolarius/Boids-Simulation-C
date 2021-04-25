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

double Vectors::distance(Vectors v2) {
    double x = pow(v2.x-this->x,2);
    double y = pow(v2.y-this->y,2);
    return sqrt(x+y);
}

Vectors Vectors::subtractTwoVector(Vectors v1,Vectors v2) {
    Vectors v;
    v1.x -= v2.x;
    v1.y -= v2.y;
    v.setCoordinate(v1.x,v1.y);
    return v;
}

void Vectors::normalize() {
    float m = magnitude();

    if (m > 0) {
        setCoordinate(x / m, y / m);
    }
    else {
        setCoordinate(x, y);
    }
}

float Vectors::magnitude() {
    return sqrt(x*x + y*y);;
}

void Vectors::divScalar(float s) {
    x /= s;
    y /= s;
}

void Vectors::addVector(Vectors v) {
    x += v.x;
    y += v.y;
}

float Vectors::angleBetween(Vectors v) {
    if (x == 0 && y == 0) return 0.0f;
    if (v.x == 0 && v.y == 0) return 0.0f;

    double dot = x * v.x + y * v.y;
    double v1mag = sqrt(x * x + y * y);
    double v2mag = sqrt(v.x * v.x + v.y * v.y);
    double amt = dot / (v1mag * v2mag);
    if (amt <= -1) {
        return M_PI;
    }
    else if (amt >= 1) {
        return 0;
    }
    float tmp = acos(amt);
    return tmp;
}

