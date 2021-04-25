//
// Created by louis on 25/04/2021.
//

#include "Boid.h"
#include <math.h>
#include <iostream>

Boid::Boid(Vectors startPos, double velocity,int size,int detectionBox,ALLEGRO_COLOR color) {
    this->vectorPosition = startPos;
    this->velocity = velocity;
    this->size = size;
    this->detectionBox = detectionBox;
    this->color = color;
}

void Boid::step(vector<Vectors> boidsSee, int screenWidth, int screenHeight) {
    // détéction de si nous somme sur le point de passer les bordures
    //en verifiant la position et langle de rotation du boid
    bool outsideHor = ((this->vectorPosition.x > screenWidth) && (cos(this->vectorPosition.angle) > 0))
                      || ((this->vectorPosition.x < 0) && (cos(this->vectorPosition.angle) < 0));
    bool outsideVer = ((this->vectorPosition.y > screenHeight) && sin(this->vectorPosition.angle) > 0)
                      || ((this->vectorPosition.y < 0) && sin(this->vectorPosition.angle) < 0);

    if (outsideHor) {
        //Verification du côter sur lequel on se trouve pour téléporter l'entiter de l'autre coter de l'écran
        if (this->vectorPosition.x > screenWidth + this->size){
            this->vectorPosition.x = 0 - this->size;
        }
        if (this->vectorPosition.x < 0 - this->size){
            this->vectorPosition.x = screenWidth + this->size;
        }
    } else if (outsideVer) {
        //Verification du côter sur lequel on se trouve pour téléporter l'entiter de l'autre coter de l'écran
        if (this->vectorPosition.y > screenHeight + this->size){
            this->vectorPosition.y = 0 - this->size;
        }
        if (this->vectorPosition.y < 0 - this->size){
            this->vectorPosition.y = screenHeight + this->size;
        }
    } else {
        //Si des boid on était vue
        if (!boidsSee.empty()) {
            float distance = MAXFLOAT,avgAngular=0;
            Vectors closestBoid;
            closestBoid.setCoordinate(0, 0);
            for (int i = 0; i < (long) boidsSee.size(); ++i) {
                avgAngular += boidsSee[i].angle;
                float tempVal = this->vectorPosition.distance(boidsSee[i]);
                //Permet de trover le boid le plus proche
                if (tempVal < distance) {
                    closestBoid = boidsSee[i];
                    distance = tempVal;
                }
            }
            //Division de la somme des angle par la taille du tableau pour trouver l'angle moyen
            avgAngular = avgAngular / boidsSee.size();


            //procedure d'évitement
            if (distance < 10) {
                //Colorisation en rouge
                this->color = al_map_rgba(255,0,0,100);
                //On ne veut pas de division par 0 donc rien et fait si les deux vecteur on la même valeurs
                if (this->vectorPosition.x != closestBoid.x) {
                    //Si l'angle et inferieur à 0 donc orianté vers le bas
                    if (closestBoid.x - this->vectorPosition.x < 0){
                        //Si le l'angle entre le vecteur actuel et le vecteur detecter et > pi
                        if ((std::fmod(
                                this->vectorPosition.angle
                                -M_PI - this->vectorPosition.angleBetween(closestBoid),
                                2 * M_PI) > M_PI)) {
                            //On fait tendre notre direction vers - PI (avec un coef pour pas que sa soit trop brusque)
                            this->changeDirection(this->vectorPosition.angle - M_PI / 50);
                        } else {
                            //sion on fait tentre notre angle de direction ver + pi
                            this->changeDirection(this->vectorPosition.angle + M_PI / 50);
                        }
                    }else{
                        //Si l'angle se trouve orianter vers le haut
                        //Si le l'angle entre le vecteur actuel et le vecteur detecter et > pi
                        //(le calcule ici et légérement diférent)
                        if ((std::fmod(
                                this->vectorPosition.angle
                                - this->vectorPosition.angleBetween(closestBoid),
                                2 * M_PI) > M_PI)) {
                            this->changeDirection(this->vectorPosition.angle - M_PI / 50);
                        } else {
                            this->changeDirection(this->vectorPosition.angle + M_PI / 50);
                        }
                    }
                }
            }
            //procedure de raprochement
            //Même principe que pour léloignement mais les valeur son inverser (+PI devient -PI et inversement)
            else if (distance > 40 ) {
                //definition de la couleur en vert
                this->color = al_map_rgba(0,255,0,100);
                if (this->vectorPosition.x != closestBoid.x) {
                    if (closestBoid.x - this->vectorPosition.x < 0){
                        if ((std::fmod(
                                this->vectorPosition.angle
                                -M_PI - this->vectorPosition.angleBetween(closestBoid),
                                2 * M_PI) > M_PI)) {
                            if (rand()%10==5) {
                                this->changeDirection(this->vectorPosition.angle + M_PI / 50);
                            }else{
                                this->changeDirection(this->vectorPosition.angle - M_PI / 50);
                            }
                        } else {
                            this->changeDirection(this->vectorPosition.angle - M_PI / 50);
                        }
                    }else{
                        if ((std::fmod(
                                this->vectorPosition.angle
                                - this->vectorPosition.angleBetween(closestBoid),
                                2 * M_PI) > M_PI)) {
                            this->changeDirection(this->vectorPosition.angle + M_PI / 50);
                        } else {
                            this->changeDirection(this->vectorPosition.angle - M_PI / 50);
                        }
                    }
                }
            //Procedure de suivit
            } else {
                //definition de la couleur en rose
                this->color = al_map_rgba(255,0,255,100);
                //80% de chance que le boid suive l'angle moyen des compagnion qu'il detecte
                if (rand()%10>8) {
                    //mise en place d'une petite variation aléatoir de l'angle moyen pour ajouter un peut de vie
                    double newAngle = ((((double) rand() / RAND_MAX) * M_PI * 2) - M_PI) * M_PI / 500;
                    this->changeDirection(avgAngular+newAngle);
                }else{
                    //20% de chance que le boid fasse un déplacement aléatoire
                    randomDirectionChange();
                }
            }
        } else {
            //Si le boid ne détecte pas de camarade
            this->color = al_map_rgba(0,0,255,150);
            //Il change aléatoirement de direction
            randomDirectionChange();
        }
        //augmentation de la velocité si celle ci et résonable (<5)
        if (velocity<5)
            this->velocity =this->velocity*1.05;
    }

    //Mouvement de la position du boild en fonction de son angle et de sa vélocité
    this->vectorPosition.x += cos(this->vectorPosition.angle) * this->velocity;
    this->vectorPosition.y += sin(this->vectorPosition.angle) * this->velocity;
}

void Boid::drawBoid() {
    float
    phi, //représente langle de la pointe du triangle equilateral
    theta, //représente langle de la medianne passent par la pointe du triangle équilateral par rapport a son cercle circonscrit
    r, //représente le rayon du cercle cironscrit
    x1, y1, x2, y2, x3, y3; //represente les coordonée x y des 3 pointe du triangle

    r = this->size;
    phi = M_PI_4;
    theta = this->vectorPosition.angle;

    //Definition de la position des coordonée de la pointes du triangle par rapport au coordonée du point de gravité de celui ci
    x1 = this->vectorPosition.x + r * cos(theta);
    y1 = this->vectorPosition.y + r * sin(theta);
    //Definition des point de la base du triangle par rapport au coordonée du point de gravité et à langle teta du cercle circonscrit.
    x2 = this->vectorPosition.x + r * cos(phi - M_PI + theta);
    y2 = this->vectorPosition.y + r * sin(phi - M_PI + theta);
    x3 = this->vectorPosition.x + r * cos(M_PI - phi + theta);
    y3 = this->vectorPosition.y + r * sin(M_PI - phi + theta);

    //Affichage du triangle dans alegro
    al_draw_triangle(x1, y1, x2, y2, x3, y3, this->color, this->size);
}

Vectors Boid::getPositionAndDirection() {
    return this->vectorPosition;
}

bool Boid::isSee(Vectors pos) {
    //l'éspace de détéction corespont à la taille du triangle plus sa zone de détéction
    int detectionZone = (int) this->size * this->detectionBox;
    bool inHor = (this->vectorPosition.x + detectionZone) >= pos.x && (this->vectorPosition.x - detectionZone) <= pos.x;
    bool inVer = (this->vectorPosition.y + detectionZone) >= pos.y && (this->vectorPosition.y - detectionZone) <= pos.y;
    //si les deux il et dans la zone vertical et horizontal alors il et vu.
    if (inHor && inVer) {
        return true;
    }
    return false;
}

void Boid::changeDirection(double angle) {
    //Si la vélocité et asser evelver
    if (velocity>1.5)
        //alors on baisse la viteesse du boid en fonction de son nouvelle angle
        this->velocity=this->velocity*abs(cos((this->vectorPosition.angle-angle)/100));
    else
        //Sinon à la réaugmente un bon coup
        this->velocity=this->velocity*1.2;
    //puis on définit l'angle
    this->vectorPosition.angle = angle;
}

void Boid::randomDirectionChange(){
    //Changement de la direction 20% des fois ou la methode et applais
    if ((double) rand() / RAND_MAX < 0.2) {
        //Génération d'un nombre aléatoir compris entre -pi et pi puis application d'un coef pour ne pas trop changer d'angle
        double newAngle = ((((double) rand() / RAND_MAX) * M_PI * 2) - M_PI) * M_PI / 50;
        //Une fois sur 2 on vas ajouter cette angle ou le soustraire
        if ((double) rand() / RAND_MAX < 0.5) {
            this->changeDirection(this->vectorPosition.angle + abs(newAngle));
        } else {
            this->changeDirection(this->vectorPosition.angle - abs(newAngle));
        }
    }
}
