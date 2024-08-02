#ifndef LOCALITY_H
#define LOCALITY_H

#include "player.h"

typedef struct {
    char address[100];
    char color[50];
    int Cost;
    int rentalPrice;
    Player owner;
    int purchased;
    int houseAmount;
    int hotelAmount;
    int numPlayersOnLoc;
    Player *playerOnLoc;
} Locality;

typedef struct {
    char address[100];
    int numPlayersOnLoc;
    Player *playerOnLoc;
    int bonus;
} StartLocality;

Locality initializeLocality(Locality *loc, char *address, char *color, int cost, int rentalPrice);
StartLocality initializeStart(StartLocality *start);
void buyLocality(Player *player, Locality *locality);
void removePlayerFromLocality(Locality *locality, int index);

#endif
