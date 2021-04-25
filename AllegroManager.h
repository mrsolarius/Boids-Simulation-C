//
// Created by louis on 06/04/2021.
//

#ifndef FOULOSCOPIE_LOUIS_VOLAT_ALLEGROMANAGER_H
#define FOULOSCOPIE_LOUIS_VOLAT_ALLEGROMANAGER_H

#include <iostream>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "thread"
#include "BoidsManager.h"

using namespace std;

class AllegroManager {
public:
    AllegroManager(ALLEGRO_DISPLAY* gDisplay, int gWidth, int gHeight);
    void launch(ALLEGRO_KEYBOARD_STATE gKbdstate, unsigned int gStep, BoidsManager entitiesManager);
private:
    void crashOnError(std::string message);
};


#endif //FOULOSCOPIE_LOUIS_VOLAT_ALLEGROMANAGER_H
