# Simulation de Boids
**Louis VOLAT**

## État d'avancement
* Encapsulation d'Allegro : Fait (Classe AllegroManager)
* Création d'une classe pour les individues : Fait (Classe Boid)
* Séparation des responsabilité : Fait (Classe BoidsManager)
* Découplage des responsabilités : Fait (Pas de include de BoidsManager dans AlegroManager)

## Extension
Tentative de mise en place d'une simulation de boids. Cette simulation vise à représenter les banc d'oiseau ou de poisson avec leur comportement très social. Ici les oiseaux (boids) son représenter par des triangle équilatéral.

La tentative n'est que partiellement réussie car la mise à jour de l'angle ne se fait que en fonction du boid le plus proche détecter et non pas en fonction de tous les boids détecter.

*Note : chez moi la simulation arrive à correctement gérer 1000 boild au delà sa commence à ralentire* 
### Légende :

* boid bleu : Aucun comportement sociaux c'est déplacement sont aléatoire
* boid vert : Le boid à vue un compagnons et souhaite l’accompagner, il tente de se rapprocher
* boid rose : Le boid est à bonne distance de ces compagnons et tente de suivre la même trajectoire
* boid rouge: le boid est trop proche de ces camarades il tente de les évités



## Difficulté

* Compréhension du système de backbuffer pour savoir quand il était possible de dessiné.
* Utilisation du type auto dans le alegro manager
* Trigonometry :
    * Dessin de triangle en fonction de leurs centre et de leur angle de rotation.
    * Mise en place des procédure d'évitement et de rapprochement.
* Visualisation des emplacement de détections.