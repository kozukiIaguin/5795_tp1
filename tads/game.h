#ifdef GAME_H
#define GAME_H
#include "board.h"
void fillBoard(Node *node, Locality *locality);
void addPlayer(Player *player);
void rollDice();
void movePlayer(Node *node,Player *player);
void buyProperty(Node* node,Player *player);
void payRent(Player *player,Node *node);
void build(Node *node,Player *player);
//bool verifyCollapse(Player *player);
void nextRound();
void printGame();

#endif
