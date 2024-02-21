#include <stdio.h>
#include <stdlib.h>

#include "Position.h"
#include "Graphique.h"

/*int boucle_jeu(Position attaque[]){
    if (!init_ncurses())
        return 0;

    for (int i = 0; i < 64; i++){
        afficher_position(attaque[i]);
        getch();
        clear();
    }

    endwin();

    return 1;
}

int main(int argc, char * argv[]){
    Position attaque[64];
    Position dame = 0ULL;

    for(int i = 0; i < 64; i++){
        calculer_cases_attaquees(&attaque[i], i);
        //calculer_cases_attaquees_cav(&attaque[i], i);
    }

    placer_dame_position(&dame, 35);
    placer_dame_position(&dame, 28);

    printf("Dame s'attaque mutuellement : %d\n", !est_sans_attaque_mutuelle(dame, attaque));

    // calculer_cases_attaquees_cav(&dame, atoi(argv[1]));

    // init_ncurses();
    // afficher_position(dame);
    // getch();



    //boucle_jeu(attaque);
    return 0;
}*/

int popcount(Position pos) {
    // Utilise la fonction intégrée __builtin_popcountll pour compter le nombre de bits à 1 dans la position
    return __builtin_popcountll(pos);
}

int init_jeu(Position attaque[]){
    // Initialise la bibliothèque ncurses
    if (!init_ncurses()) {
        fprintf(stderr, "Erreur : impossible d'initialiser ncurses.\n");
        return 0;
    }

    // Initialise le tableau des cases attaquées
    for (int i = 0; i < 64; i++) {
        calculer_cases_attaquees(&attaque[i], i);
    }
    return 1;
}

void boucle_du_jeu(Position pos, Position attaque[]){
    int colonne, ligne, result;
    Case c;
    MEVENT event;
    attrset(COLOR_PAIR(2));
    mvprintw(LINES-1, 0, "Cliquez sur la case où vous voulez placer une dame : ");
    // Boucle principale : permet à l'utilisateur de placer les huit dames
    while (1) {
        // Efface l'écran et affiche la position actuelle
        afficher_position(pos);

        // Vérifie si la position est gagnante
        if (popcount(pos) == 8 && est_sans_attaque_mutuelle(pos, attaque)) {
            attrset(COLOR_PAIR(2));
            mvprintw(LINES-1, 0, "Vous avez gagné ! Appuyez sur une touche pour quitter.");
            refresh();
            getch();
            break;
        }

        getch();
        clear();

        // Attend un clic de souris de l'utilisateur
        attrset(COLOR_PAIR(2));
        mvprintw(LINES-1, 0, "Cliquez sur la case où vous voulez placer une dame : ");
        result = getmouse(&event);
        if (result != OK) {
            // Erreur lors de la récupération de l'événement de clic de souris, affiche un message d'erreur
            attrset(COLOR_PAIR(1));
            mvprintw(LINES-1, 0, "Erreur : impossible de récupérer l'événement de clic de souris. Appuyez sur une touche pour continuer.");
            continue;
        }

        // Convertit le clic de souris en une case de l'échiquier
        colonne = event.x / 3; 
        ligne = 7 - (event.y / 2);
        c = colonne + ligne * 8;

        if (colonne > 8 || ligne > 8 || c > 63)
            continue;

        // Place la dame sur la case correspondante 
        if (!placer_dame_position(&pos, c)) {
            // La case est déjà occupée, affiche un message d'erreur
            attrset(COLOR_PAIR(1));
            mvprintw(LINES-1, 0, "Erreur : cette case est déjà occupée. Appuyez sur une touche pour continuer.");
        } else if (!est_sans_attaque_mutuelle(pos, attaque)) {
            // La position est illégale, affiche un message d'erreur
            attrset(COLOR_PAIR(1));
            mvprintw(LINES-1, 0, "Erreur : cette position est illégale. Appuyez sur une touche pour continuer.");
            // Enlève la dame placée sur la case c
            pos &= ~(1ULL << c);
        }
    }
}


int main() {
    Position pos = 0ULL; // initialise la position à 0 
    Position attaque[64]; // tableau pour stocker les cases attaquées par chaque dame 

    // initialisation du jeu 
    init_jeu(attaque);

    // La boucle du jeu et affichage 
    boucle_du_jeu(pos,attaque);

    // // Attend une saisie de l'utilisateur pour continuer
    // mvprintw(LINES-1, 0, "Appuyez sur une touche pour continuer.");
    // getch();
    // Ferme la bibliothèque ncurses
    endwin();

    return EXIT_SUCCESS;
}
