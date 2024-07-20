
#define LOCALITY_H

#include "player.h"





typedef struct 
{
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
}Locality;
typedef struct 
{
    char address[100];
    int numPlayersOnLoc;
    Player *playerOnLoc;
    int bonus;
}startLocality;

Locality initializeLocality(Locality *loc,char *address[100], char *color[],int *cost,int *rentalPrice);
startLocality initializeStart(startLocality *start);
//bool purchased(Locality *locality);
void buyLocality(Player *player, Locality *locality);
void removePlayerFromLocality(Locality *locality, int index);



