#include "Position.h"

/*La fonction prend en entrée une position pos et une case c de l'échiquier.
Elle utilise la constante 1ULL pour créer un masque avec un bit à 1 à la position de la case c,
puis elle effectue un ET bit à bit entre le masque et la position pos. Si le résultat est différent de zéro,
cela signifie que le bit correspondant à la case c est à 1 dans pos, donc que la case est occupée par une dame.
La fonction renvoie 1 dans ce cas, sinon elle renvoie 0.*/

int est_case_occupee(Position pos, Case c) {
    Position masque = 1ULL << c;
    return (pos & masque) != 0;
}

/* La fonction prend en entrée un pointeur vers une position pos et une case c de l'échiquier.
 Elle commence par vérifier si la case est déjà occupée par une dame en appelant la fonction est_case_occupee.
 Si c'est le cas, la fonction renvoie -1 pour signaler une erreur. Sinon,
  elle utilise l'opérateur |= pour placer un bit à 1 à la position de la case c dans la position pos, ce qui 
  revient à placer une dame sur cette case. La fonction renvoie 0 pour indiquer qu'il n'y a pas eu d'erreur. Notez que la position pointée par pos est modifiée directement,
 sans qu'il soit nécessaire de la renvoyer en sortie de la fonction.*/

int placer_dame_position(Position *pos, Case c) {
    if (est_case_occupee(*pos, c)) {
        return 0; // la case est déjà occupée par une dame
    }
    *pos |= (1ULL << c); // place une dame sur la case c
    return 1; // pas d'erreur
}

int calculer_cases_attaquees(Position *pos, Case c){
    if (c > 63 || c < 0)
        return 0;
        
    *pos = 0b11111111LL << (c - (c%8));
    int temp;
    
    for (int i = 0; i < 8; i++){
        *pos = 1LL << ((i * 8) + (c%8)) | *pos;
        
        temp = (c%8 - c/8 + i) + (i * 8);
        if (temp >= (i * 8) && temp < (i+1) * 8)
            *pos = 1LL << temp | *pos;

        temp = (c%8 + c/8 - i) + (i * 8);
        if (temp >= (i * 8) && temp < (i+1) * 8)
            *pos = 1LL << temp | *pos;
    }

    *pos = (*pos & ~(1LL << c));

    return 1;
}

int calculer_cases_attaquees_cav(Position *pos, Case c){
    if (c > 63 || c < 0)
        return 0;

    *pos = 0ULL;
    int temp = c - 16;
    if (temp > 0){
        if (temp -1 >= (c-c%8 - 16))
            *pos |= (1ULL << (c-16)) >> 1;

        if (temp +1 < (c-c%8 - 8))
            *pos |= (1ULL << (c-16)) << 1;
    }

    temp = c-8;
    if (temp > 0){
        if (temp -2 >= (c-c%8 - 8))
            *pos |= (1ULL << (c-8)) >> 2;

        if (temp +2 < (c-c%8))
            *pos |= (1ULL << (c-8)) << 2;
    }

    temp = c + 8;
    if (temp < 64){
        if (temp -2 >= (c-c%8 + 8))
            *pos |= (1ULL << (c+8)) >> 2;

        if (temp +2 < (c-c%8 + 16))
            *pos |= (1ULL << (c+8)) << 2;
    }

    temp += 8;
    if (temp < 64){
        if (temp -1 >= (c-c%8 + 16))
            *pos |= (1ULL << (c+16)) >> 1;

        if (temp +1 < (c-c%8 + 24))
            *pos |= (1ULL << (c+16)) << 1;
    }

    return 1;
    
}

int est_sans_attaque_mutuelle(Position pos, Position attaque[]){
    for (int bit = 0; bit < 64; bit ++){
        if ( !((pos >> bit) & 1))
            continue;

        if ((attaque[bit] ^ pos) != (attaque[bit] | pos))
            return 0;
        
    }
    
    return 1;
}