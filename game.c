#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para inicializar o jogo
void initializeGame(Game *game, int numPlayers) {
    game->numPlayers = numPlayers;
    game->players = (Player **)malloc(numPlayers * sizeof(Player *));
    if (!game->players) {
        printf("Failed to allocate memory for players");
    }

    for (int i = 0; i < numPlayers; i++) {
        game->players[i] = (Player *)malloc(sizeof(Player));
        if (!game->players[i]) {
            printf("Failed to allocate memory for player");

        }
        // Inicialize cada jogador conforme necessário
        strcpy(game->players[i]->name, "");
        game->players[i]->balance = 1500; // Saldo inicial padrão
        game->players[i]->positionNumber = 0;
        game->players[i]->played = false;
    }

    game->board = (LinkedList *)malloc(sizeof(LinkedList));
    if (!game->board) {
        printf("Failed to allocate memory for board");
      
    }
    initializeBoard(game->board);
}


Locality* readLocalityFromFile(FILE* file) {
    char address[100];
    char color[50];
    int cost, rentalPrice;

    if (fscanf(file, "%99s %49s %d %d", address, color, &cost, &rentalPrice) != 4) {
        // Handle fscanf error, possibly return NULL
        return NULL;
    }

    Locality* loc = (Locality*)malloc(sizeof(Locality));
    if (!loc) {
        printf("Failed to allocate memory for locality");
        

    }
    initializeLocality(loc, address, color, cost, rentalPrice);
    return loc;
}

void fillBoard(Game* game) {
    FILE* file = fopen("localidades.txt", "r");
    if (!file) {
        printf("Failed to open localidades.txt");
        
    }

    Locality* loc;
    while ((loc = readLocalityFromFile(file)) != NULL) {
        insertLocality(game->board, loc);
        // Ensure memory is properly managed here, free if necessary
    }
    fclose(file);
}


// Function to read a player name from a file
char* readPlayerNameFromFile(FILE* file) {
    char name[100];
    if (fscanf(file, "%99s", name) != 1) {
        // Handle fscanf error, possibly return NULL
        return NULL;
    }
    // Dynamically allocate memory for the name to prevent buffer overflows
    char* playerName = (char*)malloc(strlen(name) + 1);
    if (!playerName) {
        printf("Failed to allocate memory for player name");
        
    }
    strcpy(playerName, name);
    return playerName;
}

void addPlayers(Game* game) {
    FILE* file = fopen("jogadores.txt", "r");
    if (!file) {
        printf("Failed to open jogadores.txt");
        
    }

    int numPlayers = 0;
    char* playerName;
    while ((playerName = readPlayerNameFromFile(file)) != NULL) {
        if (numPlayers < game->numPlayers) {
            // Ensure the player's name field is large enough to hold the name
            strcpy(game->players[numPlayers]->name, playerName);
            numPlayers++;
        }
        free(playerName); 
    }
    fclose(file);
}


void movePlayer(Game *game, int playerIndex) {
    Player *player = game->players[playerIndex];
    int diceRoll = rand() % 6 + 1;
    int newPosition = (player->positionNumber + diceRoll) % game->board->size;
    advance(game->board, player, diceRoll);
    player->positionNumber = newPosition;
}


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


void build(Game *game, int playerIndex) {
      Locality currentLocality = getLocality(game->board, game->players[playerIndex]->positionNumber);
    if (currentLocality.owner.name == game->players[playerIndex]->name && game->players[playerIndex]->balance >= currentLocality.Cost && currentLocality.houseAmount == 0 && currentLocality.hotelAmount == 0) {
        printf("You can build a house here, do you wanna do it? y/n \n");
        char option[2];
        scanf("%c", &option);
        if (strcmp(option, "y")) {
            currentLocality.houseAmount = 1;
            game->players[playerIndex]->balance -= currentLocality.Cost;
            currentLocality.rentalPrice = currentLocality.rentalPrice * 5;
        } else if (strcmp(option, "n")) {
            return;
        }
}}


void verifyBankruptcy(Game *game) {
    for (int i = 0; i < game->numPlayers; i++) {
        if (game->players[i]->balance < 0) {
            printf("%s is bankrupt!\n", game->players[i]->name);
            
        }
    }
}

void printGame(Game *game) {
    printf("Players:\n");
    for (int i = 0; i < game->numPlayers; i++) {
        printf("Name: %s, Balance: %d, Position: %d\n", game->players[i]->name, game->players[i]->balance, game->players[i]->positionNumber);
    }
    printf("Board:\n");
    printBoard(game->board);
}


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
                game->players[i]->played = true; 
            }
        }
    }

    printf("Game Over!\n");
}
