#include "locality.h"
#include <string.h>

Locality initializeLocality(Locality *loc,char *address[100], Color *color,int *cost,int *rentalPrice){
    strcpy(loc->address,address);
    loc->color=color;
    loc->Cost=cost;
    loc->rentalPrice=rentalPrice;
    loc->hotelAmount=0;
    loc->houseAmount=0;
    strcpy(loc->owner,"");
    loc->purchased=0;
    

    return *loc;

}
void buyLocality(Player *player,Locality *locality){
    //check if player has cash to buy the locality
    int playerBalance= player->balance;

    if (playerBalance < locality->Cost && locality->purchased=0)
    {
        printf("not enought balance");
        return 0;
    }
    strcpy(locality->owner,player->name);
    player->balance-=locality->Cost;
    locality->purchased=1;

}