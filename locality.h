
#define LOCALITY_H

#include "player.h"



typedef enum {
    RED,BLUE,GREEN,YELLOW
}Color;

typedef struct 
{
    char address[100];
    Color color;
    int Cost;
    int rentalPrice;
    char owner[100];
    int purchased;
    int houseAmount;
    int hotelAmount;
    Player playerOnLoc[];
}Locality;
Locality initializeLocality(Locality *loc,char *address[100], Color *color,int *cost,int *rentalPrice);
//bool purchased(Locality *locality);
void buyLocality(Player *player, Locality *locality);



