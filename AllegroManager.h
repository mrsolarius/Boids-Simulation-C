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
    /**
     * Constructeur
     * @param windows ALLEGRO_DISPLAY*
     * @param screenWidth largeur de la fenêtre en px
     * @param screenHeight hauteur de la fenêtre en px
     */
    AllegroManager(ALLEGRO_DISPLAY* windows, int screenWidth, int screenHeight);
    /**
     * Boucle principal
     * @param keyboardState ALLEGRO_KEYBOARD_STATE
     * @param boidsManager objet de gestion des boids
     */
    void mainLoop(ALLEGRO_KEYBOARD_STATE keyboardState, BoidsManager boidsManager);
private:
    /**
     * Fonction de crash
     * @param message
     */
    void crashOnError(std::string message);
};


#endif //FOULOSCOPIE_LOUIS_VOLAT_ALLEGROMANAGER_H
