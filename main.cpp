#include <iostream>
#include <vector>
#include <thread>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "BoidsManager.h"
#include "AllegroManager.h"

using namespace std;

//inisialisation des paramètre de simulation
int displayWidth = 1920;
int displayHeight = 800;
int totalEntities = 10;

ALLEGRO_KEYBOARD_STATE keyboardState;
ALLEGRO_DISPLAY* displayWindows = nullptr;

int main(int argc, char **argv) {

    //Création de l'objet de gestion de la fenêtre
    auto allegroManager = new AllegroManager(displayWindows, displayWidth, displayHeight);

    //Création de l'objet de gestion des oisoïde
    BoidsManager boidsManager(totalEntities, displayWidth, displayHeight);

    //Démarage de la boucle de simulation
    allegroManager->launch(keyboardState, 0, boidsManager);

    //Si la boucle et couper on ferme la fenetre et le programe
    al_destroy_display(displayWindows);
    al_shutdown_primitives_addon();

    return 0;
}


