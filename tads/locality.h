#ifdef LOCALITY_H
#define LOCALITY_H

#include "player.h"



typedef enum {
    RED,BLUE,GREEN,YELLOW
}Color;

typedef struct 
{
    char address[100];
    Color color;
    int purchcaseCost;
    int rentalPrice;
    char owner[100];
    int purshcased;
    int houseAmount;
    int hotelAmount;
}Locality;
Locality initializeLocality();
//bool isPurshcased(Locality *locality);
void buyLocality(Player *player, Locality *locality);

#endif

