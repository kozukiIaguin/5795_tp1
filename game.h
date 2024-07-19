#include "board.h"



void fillBoard(linkedList *list);
void addPlayer(Player *player[]);
int rollDice();
void movePlayer(linkedList *list,Player *player);
void buyProperty(linkedList *list,Player *player);
void payRent(Player *player,Node *node);
void build(Node *node,Player *player);
//bool verifyCollapse(Player *player);
void nextRound();
void printGame();


