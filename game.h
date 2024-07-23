#include "board.h"
typedef struct {
    linkedList *board;
    Player **players;
    int numPlayers;
} Game;



void fillBoard(Game *game);
void addPlayers(Game *game);
int rollDice(Game *game);
void movePlayer(Game *game, int playerIndex);
void buyProperty(Game *game, int playerIndex);
void payRent(Game *game, int playerIndex);
void build(Game *game, int playerIndex);
void verifyBankruptcy(Game *game);
void nextRound(Game *game);
void printGame(Game *game);