#include <iostream>
#include <vector>
#include <thread>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include "BoidsManager.h"
#include "AllegroManager.h"

using namespace std;

int displayWidth = 1920;
int displayHeight = 800;
int totalEntities = 1000;

ALLEGRO_KEYBOARD_STATE keyboardState;
ALLEGRO_DISPLAY* displayWindows = nullptr;

int main(int argc, char **argv) {

    auto allegroManager = new AllegroManager(displayWindows, displayWidth, displayHeight);

    BoidsManager entitiesManager(totalEntities, displayWidth, displayHeight);

    allegroManager->launch(keyboardState, 0, entitiesManager);

    al_destroy_display(displayWindows);
    al_shutdown_primitives_addon();

    return 0;
}


