#include "application.h"
#include "sdl2.h"
#include <stdio.h>

int main() {
    // Initialisation of the application
    struct Application *application = Application_initialize();
    if (application != NULL) {
        Application_run(application);
    } else {
        fprintf(stderr, "Failed to initialize the application...");
        return -1;
    }

    //Ending the application
    Application_shutDown(application);
    return 0;
}

// I leave this here to let you see the progress

// N'utilisez que les événements clavier de l'utilisateur (pas d'événement
// souris, sauf quand on clique sur le x qui ferme la fenêtre du jeu);
// Utilisez les ressources graphiques que je vous fournis (mais n'hésitez pas
// à les modifier ou à en ajouter si vous êtes motivés, à la toute fin);
// Assurez-vous d'abord d'avoir une version fonctionnelle dans laquelle les
// objets sont statiques pour ensuite les animer.


//GESTION**********************************************************************

// Les modifications devraient être ajoutées par requêtes d'intégration,
// afin de bien structurer le développement. Notez que le texte qui explique la
// requête d'intégration n'a pas à être aussi détaillé que pour le 2e travail
// pratique, une courte explication étant suffisante.

// Si vous travaillez seul, vous devez tout de même structurer vos
// modifications à l'aide de requêtes d'intégration, que vous accepterez
// vous-même. C'est sûr que c'est un peu plus artificiel, mais ça permet au
// moins de bien étudier, rétroactivement, le développement de votre
// programme. En particulier, assurez-vous de laisser toutes les branches que
// vous avez utilisées et fusionnées sur le dépôt afin qu'on puisse les
// étudier si nécessaire.


//****STEPS**************
// What is the First step?
// when the player clicks on PLAY, it should start the game on a static state.
// How to manage state transitions? Do i have to add game.c/game.h ?
// ex. betwen Menu State -> to a Playing state.

//Once this is done, try to draw all the elements of the game (statics)
//How do i need to display them around the middle circle?
//How to handle the physics?
//How to make the cursor move around the circle?

//lookup game.c for next steps
