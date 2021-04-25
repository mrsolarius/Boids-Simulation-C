//
// Created by louis on 06/04/2021.
//

#include "AllegroManager.h"


AllegroManager::AllegroManager(ALLEGRO_DISPLAY *windows, int screenWidth, int screenHeight) {

    //Gestion des possible de alegros à l'inisialisation
    if(!al_init()) {
        this->crashOnError("failed to initialize allegro!");
    }

    if(!al_init_primitives_addon()) {
        this->crashOnError("failed to initialize allegro primitives addon!");
    }

    al_set_new_display_flags(ALLEGRO_OPENGL_3_0);

    //Création de la fenêtres
    windows = al_create_display(screenWidth, screenHeight);

    if(!windows) {
        this->crashOnError("failed to initialize allegro display!");
    }

    if(!al_install_keyboard()) {
        this->crashOnError("Failed to initialize allegro keyboard handling!");
    }

    if(!al_install_mouse()) {
        this->crashOnError("Failed to initialize allegro mouse handling!");
    }
}

void AllegroManager::mainLoop(ALLEGRO_KEYBOARD_STATE keyboardState, BoidsManager boidsManager) {
    unsigned short currentStep = 0;
    while (true) {
        // Récupération des évenements clavier
        al_get_keyboard_state(&keyboardState);

        // Sortie si Esc.
        if (al_key_down(&keyboardState, ALLEGRO_KEY_ESCAPE)) {
            return;
        }

        // Comportement des boids
        boidsManager.step(currentStep);

        // On efface tout (dans le backbuffer)
        al_clear_to_color(al_map_rgb(0, 0, 0));

        // Dessin des boids (dans le backbuffer)
        boidsManager.drawBoids();

        // On affiche le backbuffer
        al_flip_display();

        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        currentStep++;
    }
}

void AllegroManager::crashOnError(std::string message) {
    cerr << message << endl;
    exit(-1);
}
