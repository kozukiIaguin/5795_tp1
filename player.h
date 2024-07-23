#include <stdbool.h>

#define PLAYER_H


typedef struct 
{
    char name[100];
    int num;
    int balance;
    int positionNumber;
    bool played;
}Player;


void updateBalance(Player *p, int amount);
