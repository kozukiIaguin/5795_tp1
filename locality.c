#include "locality.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Locality initializeLocality(Locality *loc, char *address, char *color, int cost, int rentalPrice) {
    strcpy(loc->address, address);
    strcpy(loc->color, color);
    loc->Cost = cost;
    loc->rentalPrice = rentalPrice;
    loc->houseAmount = 0;
    loc->hotelAmount = 0;
    strcpy(loc->owner.name, "");
    loc->purchased = 0;
    loc->numPlayersOnLoc = 0;
    loc->playerOnLoc = NULL; 

    return *loc;
}

void buyLocality(Player *player, Locality *locality) {
    if (player->balance < locality->Cost || locality->purchased == 1) {
        printf("Not enough balance or locality already purchased\n");
        return;
    }
    strcpy(locality->owner.name, player->name);
    player->balance -= locality->Cost;
    locality->purchased = 1;
}

void removePlayerFromLocality(Locality *locality, int index) {
    for (int i = index; i < locality->numPlayersOnLoc - 1; i++) {
        locality->playerOnLoc[i] = locality->playerOnLoc[i + 1];
    }
    locality->numPlayersOnLoc -= 1;
}
