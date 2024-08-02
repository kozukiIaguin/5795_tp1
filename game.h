#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "board.h"

// Estrutura do jogo
typedef struct {
    Player **players;    // Array de ponteiros para jogadores
    int numPlayers;      // Número de jogadores
    LinkedList *board;   // Tabuleiro do jogo
} Game;

// Funções para gerenciar o jogo
void initializeGame(Game *game, int numPlayers);
void fillBoard(Game *game);
void addPlayers(Game *game);
void movePlayer(Game *game, int playerIndex);
void payRent(Game *game, int playerIndex);
void build(Game *game, int playerIndex);
void verifyBankruptcy(Game *game);
void printGame(Game *game);
void startGame(Game *game);

#endif
