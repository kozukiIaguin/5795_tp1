#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para inicializar o jogo
void initializeGame(Game *game, int numPlayers) {
    game->numPlayers = numPlayers;
    game->players = (Player **)malloc(numPlayers * sizeof(Player *));
    if (!game->players) {
        perror("Failed to allocate memory for players");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numPlayers; i++) {
        game->players[i] = (Player *)malloc(sizeof(Player));
        if (!game->players[i]) {
            perror("Failed to allocate memory for player");
            exit(EXIT_FAILURE);
        }
        // Inicialize cada jogador conforme necessário
        strcpy(game->players[i]->name, "");
        game->players[i]->balance = 1500; // Saldo inicial padrão
        game->players[i]->positionNumber = 0;
        game->players[i]->played = false;
    }

    game->board = (LinkedList *)malloc(sizeof(LinkedList));
    if (!game->board) {
        perror("Failed to allocate memory for board");
        exit(EXIT_FAILURE);
    }
    initializeBoard(game->board);
}

// Função para preencher o tabuleiro com localidades
void fillBoard(Game *game) {
    FILE *file = fopen("localidades.txt", "r");
    if (!file) {
        perror("Failed to open localidades.txt");
        exit(EXIT_FAILURE);
    }

    char address[100];
    char color[50];
    int cost, rentalPrice;

    while (fscanf(file, "%99s %49s %d %d", address, color, &cost, &rentalPrice) == 4) {
        Locality *loc = (Locality *)malloc(sizeof(Locality));
        if (!loc) {
            perror("Failed to allocate memory for locality");
            exit(EXIT_FAILURE);
        }
        initializeLocality(loc, address, color, cost, rentalPrice);
        insertLocality(game->board, loc);
    }
    fclose(file);
}

// Função para adicionar jogadores ao jogo
void addPlayers(Game *game) {
    FILE *file = fopen("jogadores.txt", "r");
    if (!file) {
        perror("Failed to open jogadores.txt");
        exit(EXIT_FAILURE);
    }

    char name[100];
    int numPlayers = 0;

    while (fscanf(file, "%99s", name) == 1) {
        if (numPlayers < game->numPlayers) {
            strcpy(game->players[numPlayers]->name, name);
            numPlayers++;
        }
    }
    fclose(file);
}

// Função para mover o jogador
void movePlayer(Game *game, int playerIndex) {
    Player *player = game->players[playerIndex];
    int diceRoll = rand() % 6 + 1; // Simula o lançamento de um dado (1 a 6)
    int newPosition = (player->positionNumber + diceRoll) % game->board->size;
    advance(game->board, player, diceRoll);
    player->positionNumber = newPosition;
}

// Função para pagar aluguel
void payRent(Game *game, int playerIndex) {
    Player *player = game->players[playerIndex];
    Locality currentLoc = getLocality(game->board, player->positionNumber);

    if (currentLoc.purchased && strcmp(currentLoc.owner.name, player->name) != 0) {
        int rent = currentLoc.rentalPrice;
        Player *owner = NULL;

        for (int i = 0; i < game->numPlayers; i++) {
            if (strcmp(game->players[i]->name, currentLoc.owner.name) == 0) {
                owner = game->players[i];
                break;
            }
        }

        if (owner) {
            updateBalance(player, -rent);
            updateBalance(owner, rent);
            printf("%s paid %d in rent to %s\n", player->name, rent, owner->name);
        }
    }
}

// Função para construir propriedades
void build(Game *game, int playerIndex) {
    // Lógica para construir casas e hotéis
}

// Função para verificar falência
void verifyBankruptcy(Game *game) {
    for (int i = 0; i < game->numPlayers; i++) {
        if (game->players[i]->balance < 0) {
            printf("%s is bankrupt!\n", game->players[i]->name);
            // Remover jogador do jogo
            // Atualizar o tabuleiro e outras estruturas conforme necessário
        }
    }
}

// Função para imprimir o estado do jogo
void printGame(Game *game) {
    printf("Players:\n");
    for (int i = 0; i < game->numPlayers; i++) {
        printf("Name: %s, Balance: %d, Position: %d\n", game->players[i]->name, game->players[i]->balance, game->players[i]->positionNumber);
    }
    printf("Board:\n");
    printBoard(game->board);
}

// Função principal para iniciar o jogo
void startGame(Game *game) {
    fillBoard(game);
    addPlayers(game);

    while (game->numPlayers > 1) {
        for (int i = 0; i < game->numPlayers; i++) {
            if (!game->players[i]->played) {
                movePlayer(game, i);
                payRent(game, i);
                build(game, i);
                verifyBankruptcy(game);
                printGame(game);
                game->players[i]->played = true; // Marca o jogador como jogado
                // Aqui pode-se implementar a lógica para passar a vez
            }
        }
    }

    printf("Game Over!\n");
}
