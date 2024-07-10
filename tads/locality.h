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

}Locality;
