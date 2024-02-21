#ifndef __GRAPHIQUE_H_
#define __GRAPHIQUE_H_

#include <ncurses.h>

#include "Position.h"

int init_ncurses();
int afficher_position(Position pos);

#endif
