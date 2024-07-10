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
    int purshcased=0;
    int houseAmount=0;
    int hotelAmount=0;
}Locality;
Locality initializeLocality();
bool isPurshcased(Locality *locality);
void buyLocality(Player *player, Locality *locality);



