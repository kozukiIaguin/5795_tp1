#include "board.h"



void fillBoard(linkedList *list);
void addPlayer(Player *player[]);
int rollDice();
void movePlayer(linkedList *list,Player *player);
void buyProperty(linkedList *list,Player *player);
void payRent(linkedList *list, Player *player);
void build(linkedList *list,Player *player);
void verifyBankruptcy(Player *player[]);
void nextRound();
void printGame();


