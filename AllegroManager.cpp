//
// Created by louis on 06/04/2021.
//

#include "AllegroManager.h"


AllegroManager::AllegroManager(ALLEGRO_DISPLAY *gDisplay, int gWidth, int gHeight) {
    if(!al_init()) {
        this->crashOnError("failed to initialize allegro!");
    }

    if(!al_init_primitives_addon()) {
        this->crashOnError("failed to initialize allegro primitives addon!");
    }

    al_set_new_display_flags(ALLEGRO_OPENGL_3_0);

    gDisplay = al_create_display(gWidth, gHeight);

    if(!gDisplay) {
        this->crashOnError("failed to initialize allegro display!");
    }

    if(!al_install_keyboard()) {
        this->crashOnError("Failed to initialize allegro keyboard handling!");
    }

    if(!al_install_mouse()) {
        this->crashOnError("Failed to initialize allegro mouse handling!");
    }
}

void AllegroManager::launch(ALLEGRO_KEYBOARD_STATE gKbdstate, unsigned int gStep, BoidsManager entitiesManager) {
    while (true) {
        // Récupération des évenements clavier
        al_get_keyboard_state(&gKbdstate);

        // Sortie si Esc.
        if (al_key_down(&gKbdstate, ALLEGRO_KEY_ESCAPE)) {
            return;
        }

        // Comportement des individus
        entitiesManager.step(gStep);

        // On efface tout (dans le backbuffer)
        al_clear_to_color(al_map_rgb(250, 250, 250));

        // Dessin des individus (dans le backbuffer)
        entitiesManager.drawBoids();

        // On affiche le backbuffer
        al_flip_display();

        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        gStep++;
    }
}

void AllegroManager::crashOnError(std::string message) {
    cerr << message << endl;
    exit(-1);
}
