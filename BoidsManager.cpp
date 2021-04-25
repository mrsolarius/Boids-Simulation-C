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
    generateBoid();
}

void BoidsManager::step(unsigned int step) {
    //Génération de boid tant que l'étape et impaire et que le nombre maximal de boid n'est pas dépasser
    if (this->currentBoids < this->totalBoids && step%2==1) {
        this->generateBoid();
    }
    //parcour de tous les boid pour savoirs ceux qu'il vois
    for (int i = 0; i < (int) this->boids.size(); i++) {
        std::vector<Vectors> boidsDetected = {};
        //parcour de tous les boid pour savoir si le boid detecte un autre boid
        for (int j = 0; j < (int) this->boids.size(); j++) {
            //si un boid et detecter et que se n'est pas le boid actuel
            if (i != j && this->boids[i].isSee(this->boids[j].getPositionAndDirection())) {
                boidsDetected.push_back(this->boids[j].getPositionAndDirection());
            }
        }
        //l'ancement de l'étape du boid avec sa colection de boid détécter
        this->boids[i].step(boidsDetected, this->screenWidth, this->screenHeight);
    }
}

void BoidsManager::drawBoids() {
    //Dessin de tous les boids
    for (auto &e: this->boids) {
        e.drawBoid();
    }
}

void BoidsManager::generateBoid() {
    currentBoids++;
    //Génération des Boid au centre de l'écran
    int x = screenWidth / 2;
    int y = screenHeight / 2;
    //Avec un angle aléatoir compris entre -pi et pi
    double angle = (((double) rand() / RAND_MAX) * M_PI * 2) - M_PI;
    Vectors vectors;
    vectors.setAll(x,y,angle);
    this->boids.emplace_back(vectors,
                               3,
                               5,
                               10,
                               al_map_rgba(0, 0, 255, 150));
}

