//
// Created by louis on 25/04/2021.
//

#include "Boid.h"
#include <math.h>
#include <iostream>

Boid::Boid(Vectors startPos, double velocity, int size, int detectionBox,ALLEGRO_COLOR col) {
    this->position = startPos;
    this->velocity = velocity;
    this->size = size;
    this->detectionBox = detectionBox;
    this->color = col;
}

void Boid::step(unsigned int step, vector<Vectors> boidsSee, int screenWidth, int screenHeight) {
    bool outsideHor = ((this->position.x > screenWidth) && (cos(this->position.angle) > 0))
                      || ((this->position.x < 0) && (cos(this->position.angle) < 0));
    bool outsideVer = ((this->position.y > screenHeight) && sin(this->position.angle) > 0)
                      || ((this->position.y < 0) && sin(this->position.angle) < 0);

    if (outsideHor) {
        changeDirection(M_PI - this->position.angle);
    } else if (outsideVer) {
        changeDirection(-this->position.angle);
    } else {
        if (!boidsSee.empty()) {

            float distance = MAXFLOAT;
            float avgAngular = 0;
            for (int i = 0; i < (long) boidsSee.size(); ++i) {
                avgAngular += boidsSee[i].angle;
                float tempVal = this->position.distance(boidsSee[i]);
                if (tempVal < distance) {
                    distance = tempVal;
                }
            }
            avgAngular = avgAngular / boidsSee.size();


            //procedure d'évitement
            if (distance < 40) {
                this->color = al_map_rgba(255,0,0,100);
                if (std::fmod(avgAngular, 2 * M_PI) > std::fmod(this->position.angle, 2 * M_PI)) {
                    this->changeDirection(this->position.angle - M_PI / 100);
                } else {
                    this->changeDirection(this->position.angle + M_PI / 100);
                }
            }
                //procedure de raprochement
            else if (distance > 60) {
                this->color = al_map_rgba(0,255,0,100);
                if (std::fmod(avgAngular, 2 * M_PI) > std::fmod(this->position.angle, 2 * M_PI)) {
                    this->changeDirection(this->position.angle + M_PI / 100);
                } else {
                    this->changeDirection(this->position.angle - M_PI / 100);
                }
                //suivit
            } else {
                this->color = al_map_rgba(255,0,255,100);
                randomDirectionChange();
            }
        } else {
            this->color = al_map_rgba(0,0,255,150);
            randomDirectionChange();
        }
        if (velocity<5)
            this->velocity =this->velocity*1.005;
    }

    this->position.x += cos(this->position.angle) * this->velocity;
    this->position.y += sin(this->position.angle) * this->velocity;
}

void Boid::drawBoid() {
    float phi, theta, r, x1, y1, x2, y2, x3, y3;
    r = this->size;
    phi = M_PI_4;
    theta = this->position.angle;
    x1 = this->position.x + r * cos(theta);
    y1 = this->position.y + r * sin(theta);
    x2 = this->position.x + r * cos(phi - M_PI + theta);
    y2 = this->position.y + r * sin(phi - M_PI + theta);
    x3 = this->position.x + r * cos(M_PI - phi + theta);
    y3 = this->position.y + r * sin(M_PI - phi + theta);
    //al_draw_filled_ellipse(this->position[0], this->position[1], this->detectionBox*this->size/2, this->detectionBox*this->size/2, al_map_rgba(255,0,0,10));
    al_draw_triangle(x1, y1, x2, y2, x3, y3, this->color, this->size);
}

Vectors Boid::getPositionAndDirection() {
    return this->position;
}

bool Boid::isDetected(Vectors pos) {
    int space = (int) this->size * this->detectionBox; // 1.5
    bool inHor = (this->position.x + space) >= pos.x && (this->position.x - space) <= pos.x;
    bool inVer = (this->position.y + space) >= pos.y && (this->position.y - space) <= pos.y;
    if (inHor && inVer) {
        return true;
    }
    return false;
}

void Boid::changeDirection(double angle) {
    if (velocity>1.5)
        this->velocity=this->velocity*abs(cos((this->direction-angle)/100));
    this->position.angle = angle;
}

void Boid::randomDirectionChange(){
    if ((double) rand() / RAND_MAX < 0.3) {
        double newAngle = ((((double) rand() / RAND_MAX) * M_PI * 2) - M_PI) * M_PI / 100;
        if ((double) rand() / RAND_MAX < 0.5) {
            this->changeDirection(this->position.angle + abs(newAngle));
        } else {
            this->changeDirection(this->position.angle - abs(newAngle));
        }
    }
}
