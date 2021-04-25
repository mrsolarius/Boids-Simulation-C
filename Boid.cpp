//
// Created by louis on 25/04/2021.
//

#include "Boid.h"
#include <math.h>
#include <iostream>

Boid::Boid(std::vector<double> startPos, double velocity, int size, double direction, int detectionBox,ALLEGRO_COLOR col) {
    this->position = startPos;
    this->velocity = velocity;
    this->direction = direction;
    this->size = size;
    this->detectionBox = detectionBox;
    this->color = col;
}

void Boid::step(unsigned int step, std::vector<std::vector<double>> boidSee, int screenWidth, int screenHeight) {
    bool outsideHor = (((this->position[0] + this->size - 1) > screenWidth) && (cos(this->direction) > 0))
                      || (((this->position[0] - this->size + 1) < 0) && (cos(this->direction) < 0));
    bool outsideVer = (((this->position[1] + this->size - 1) > screenHeight) && sin(this->direction) > 0)
                      || (((this->position[1] - this->size + 1) < 0) && sin(this->direction) < 0);

    if (outsideHor) {
        if ((this->position[0] + this->size - 1) > screenWidth) {
            printf("hint left\npostion : %f,%f\nscreenWidth:%f\n\n", this->position[0], this->position[1], screenWidth);
        }
        changeDirection(this->direction - M_PI);
    } else if (outsideVer) {
        changeDirection(this->direction - M_PI);
    } else {
        if (!boidSee.empty()) {

            float distance = MAXFLOAT;
            int closeItem = 0;
            float avgAngular = 0;
            for (int i = 0; i < boidSee.size(); ++i) {
                avgAngular += boidSee[i][2];
                float tempVal = sqrt(
                        pow(boidSee[i][0] - this->position[0], 2) + pow(boidSee[i][1] - this->position[1], 2));
                if (tempVal < distance) {
                    distance = tempVal;
                    closeItem = i;
                }
            }
            avgAngular = avgAngular / boidSee.size();


            //procedure d'évitement
            if (distance < 40) {
                if (std::fmod(avgAngular, 2 * M_PI) > std::fmod(this->direction, 2 * M_PI)) {
                    this->changeDirection(this->direction - M_PI / 100);
                } else {
                    this->changeDirection(this->direction + M_PI / 100);
                }
            }
                //procedure de raprochement
            else if (distance > 60) {
                if (std::fmod(avgAngular, 2 * M_PI) > std::fmod(this->direction, 2 * M_PI)) {
                    this->changeDirection(this->direction + M_PI / 100);
                } else {
                    this->changeDirection(this->direction - M_PI / 100);
                }
                //suivit
            } else {
                if ((double) rand() / RAND_MAX < 0.05)
                    this->changeDirection(std::fmod(rand(), M_PI * 2 + 1) * M_PI / 100);
            }
        } else if ((double) rand() / RAND_MAX < 0.05) {
            this->changeDirection(std::fmod(rand(), M_PI * 2 + 1) * M_PI / 100);
        }
        //this->velocity =this->velocity*1.0005;
    }

    this->position[0] += cos(this->direction) * this->velocity;
    this->position[1] += sin(this->direction) * this->velocity;
}

void Boid::drawBoid() {
    float phi, theta, r, x1, y1, x2, y2, x3, y3;
    r = this->size;
    phi = M_PI_4;
    theta = this->direction;
    x1 = this->position[0] + r * cos(theta);
    y1 = this->position[1] + r * sin(theta);
    x2 = this->position[0] + r * cos(phi - M_PI + theta);
    y2 = this->position[1] + r * sin(phi - M_PI + theta);
    x3 = this->position[0] + r * cos(M_PI - phi + theta);
    y3 = this->position[1] + r * sin(M_PI - phi + theta);
    //al_draw_filled_ellipse(this->position[0], this->position[1], this->detectionBox*this->size/2, this->detectionBox*this->size/2, al_map_rgba(255,0,0,10));
    al_draw_triangle(x1, y1, x2, y2, x3, y3, this->color, this->size);
}

std::vector<double> Boid::getPositionAndDirection() {
    return {this->position[0], this->position[1], this->direction};
}

bool Boid::isDetected(std::vector<double> pos) {
    int space = (int) this->size * this->detectionBox; // 1.5
    bool inHor = (this->position[0] + space) >= pos[0] && (this->position[0] - space) <= pos[0];
    bool inVer = (this->position[1] + space) >= pos[1] && (this->position[1] - space) <= pos[1];
    if (inHor && inVer) {
        return true;
    }
    return false;
}

void Boid::changeDirection(double angle) {
    //this->velocity=this->velocity*abs(cos((this->direction-angle)/10));
    this->direction = angle;
}
