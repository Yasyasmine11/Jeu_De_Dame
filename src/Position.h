#ifndef __POSITION_H_
#define __POSITION_H_

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

typedef unsigned long long Position;

typedef enum{
    A1 = 0, B1, C1, D1, E1, F1, G1, H1,
    A2 = 8, B2, C2, D2, E2, F2, G2, H2,
    A3 = 16, B3, C3, D3, E3, F3, G3, H3,
    A4 = 24, B4, C4, D4, E4, F4, G4, H4,
    A5 = 32, B5, C5, D5, E5, F5, G5, H5,
    A6 = 40, B6, C6, D6, E6, F6, G6, H6,
    A7 = 48, B7, C7, D7, E7, F7, G7, H7,
    A8 = 56, B8, C8, D8, E8, F8, G8, H8
} Case;

int est_case_occupee(Position pos, Case c);
int placer_dame_position(Position *pos, Case c);
int calculer_cases_attaquees(Position *pos, Case c);
int est_sans_attaque_mutuelle(Position pos, Position attaque[]);
int calculer_cases_attaquees_cav(Position *pos, Case c);

#endif