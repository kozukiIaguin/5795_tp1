#define PLAYER_H


typedef struct 
{
    char name[100];
    int num;
    int balance;
    int positionNumber;
}Player;


void updateBalance(Player *p, int amount);
