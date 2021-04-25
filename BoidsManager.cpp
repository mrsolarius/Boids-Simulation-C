//
// Created by louis on 06/04/2021.
//

#include "BoidsManager.h"
#include <iostream>
#include <vector>
#include <allegro5/allegro.h>
#include <cmath>

BoidsManager::BoidsManager(int totalBoids, int screenWidth, int screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->totalBoids = totalBoids;
    this->currentBoids = 0;
    generateEntity();
}

void BoidsManager::step(unsigned int step) {
    if (this->currentBoids < this->totalBoids && step%2==1) {
        this->generateEntity();
        printf("%i\n", this->currentBoids);
    }
    for (int i = 0; i < (int) this->boids.size(); i++) {

        std::vector<Vectors> boidsDetected = {};
        for (int j = 0; j < (int) this->boids.size(); j++) {
            if (i != j && this->boids[i].isDetected(this->boids[j].getPositionAndDirection())) {
                boidsDetected.push_back(this->boids[j].getPositionAndDirection());
            }
        }

        this->boids[i].step(step, boidsDetected, this->screenWidth, this->screenHeight);
    }
}

void BoidsManager::drawBoids() {
    for (auto &e: this->boids) {
        e.drawBoid();
    }
}

void BoidsManager::generateEntity() {
    currentBoids++;
    int x = screenWidth / 2;
    int y = screenHeight / 2;
    double angle = (((double) rand() / RAND_MAX) * M_PI * 2) - M_PI;
    printf("angle : %f",angle);
    Vectors vectors;
    vectors.setAll(x,y,angle);
    this->boids.push_back(Boid(vectors,
                               3,
                               5,
                               20,
                               al_map_rgba(0, 0, 255, 150)));
}

