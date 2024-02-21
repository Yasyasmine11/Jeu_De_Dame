#include "Graphique.h"

int init_ncurses(){
    if (initscr() == NULL)
        return 0;    
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(FALSE);
    start_color();    
    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    mousemask(BUTTON1_CLICKED, NULL);

    return 1;
}

int afficher_position(Position pos){    
    char c;
    for (int i = 0; i < 64; i++) {
        if (est_case_occupee(pos, i)){
            attrset(COLOR_PAIR(1));
            c = '+';
        }
        else{
            attrset(COLOR_PAIR(2));
            c = '.';
        }
        mvprintw((7-i/8)*2, i%8*3, "   ");
        mvprintw((7-i/8)*2+1, i%8*3, " %c ", c);
    }
    refresh();
    return 1; // pas d'erreur
}