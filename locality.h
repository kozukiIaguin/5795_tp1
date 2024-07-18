
#define LOCALITY_H

#include "player.h"





typedef struct 
{
    char address[100];
    char color[50];
    int Cost;
    int rentalPrice;
    char owner[100];
    int purchased;
    int houseAmount;
    int hotelAmount;
    int numPlayersOnLoc;
    Player *playerOnLoc;
}Locality;
Locality initializeLocality(Locality *loc,char *address[100], char *color[],int *cost,int *rentalPrice);
//bool purchased(Locality *locality);
void buyLocality(Player *player, Locality *locality);
void removePlayerFromLocality(Locality *locality, int index);



