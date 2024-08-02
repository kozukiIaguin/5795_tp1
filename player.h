#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

typedef struct {
    char name[100];
    int num;
    int balance;
    int positionNumber;
    bool played;
} Player;

void updateBalance(Player *p, int amount);

#endif
