//
// Created by louis on 06/04/2021.
//

#include "BoidsManager.h"
#include <iostream>
#include <vector>
#include <allegro5/allegro.h>
#include <cmath>

BoidsManager::BoidsManager(int totalEntities, int screenWidth, int screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    this->totalEntities = totalEntities;
    this->currentEntities = 0;
    generateEntity();
}

void BoidsManager::step(unsigned int step) {
    if (this->currentEntities < this->totalEntities) {
        this->generateEntity();
        printf("%i\n", this->currentEntities);
    }
    for (int i = 0; i < (int) this->entities.size(); i++) {

        std::vector<std::vector<double>> boidDetected = {};
        for (int j = 0; j < (int) this->entities.size(); j++) {
            if (i != j && this->entities[i].isDetected(this->entities[j].getPositionAndDirection())) {
                boidDetected.push_back(this->entities[j].getPositionAndDirection());
            }
        }

        this->entities[i].step(step, boidDetected, this->screenWidth, this->screenHeight);
    }
}

void BoidsManager::drawAllegro() {
    for (auto &e: this->entities) {
        e.drawBoid();
    }
}

void BoidsManager::generateEntity() {
    currentEntities++;
    int x = screenWidth / 2;
    int y = screenHeight / 2;
    double angle = std::fmod(rand(), ((M_PI * 2 - 0) + 1) + 0);

    this->entities.push_back(Boid({static_cast<double>(x), static_cast<double>(y)},
                                  3,
                                  5,
                                  angle,
                                  20,
                                  al_map_rgba(0, 0, 255, 150)));
}

