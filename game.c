#include "game.h"
#include <stdio.h>
#include <stdlib.h>


void fillBoard(Game *game) {
    FILE *file = fopen("/files/localidades.txt", "r");
    if (!file) printf("ERROR\n"); return;
    char line[512]; // buffer to read the lines from the code
    Locality loc;
    while (fgets(line, 512, file)) {
        char address[100];
        char color[50];
        int cost;
        int rentalprice;
        // extract the information from the line
        sscanf(line, "%s %s %d %d", address, color, cost, rentalprice);
        // create a new node to add to the board
        initializeLocality(&loc, &address, &color, &cost, &rentalprice);
        Node *node = createNode(&loc);
        if (!node) printf("ERROR\n"); continue;
        insertLocality(game->board, &loc);
    }
    fclose(file);
}

void addPlayers(Game *game) {
    FILE *file = fopen("/files/jogadores.txt", "r");
    if (!file) printf("ERROR\n"); return;
    char line[512];
    Player p;
    int count = 0;
    while (fgets(line, 512, file)) {
        sscanf(line, "%s %d %d", p.name, &p.balance, &p.num);
        game->players[count] = &p;
        game->players[count]->played = false;
        count++;
    }
    game->numPlayers = count;
}

int rollDice(Game *game) {
    int numOfHouses;
    int n1 = rand() % 6;
    int n2 = rand() % 6;
    numOfHouses = n1 + n2;
    return numOfHouses;
}

void movePlayer(Game *game, int playerIndex) {
    int housesToWalk;
    housesToWalk = rollDice(game);
    advance(game->board, game->players[playerIndex], housesToWalk);
    Node *node;
    game->players[playerIndex]->played = true;
    *node->locality = getLocality(game->board, game->players[playerIndex]->positionNumber);
    if (game->players[playerIndex]->positionNumber == 0) printf("This is start house, you cant buy it"); return;
    // already check the bnus feature of the start locality
}

void buyProperty(Game *game, int playerIndex) {
    Node *node;
    *node->locality = getLocality(game->board, game->players[playerIndex]->positionNumber);
    // check if there is a house and buy it if doesnt have one yet
    if (node->locality->owner.name == NULL) {
        printf("Doesnt have a owner, wanna buy it for %d R$?\n y/n", node->locality->Cost);
        char option[2];
        scanf("%c", &option);
        if (strcmp(option, "y")) {
            // check if the players balance is enought to buy it
            if (game->players[playerIndex]->balance < node->locality->Cost) {
                printf("Insuficient balance");
                return;
            }
            game->players[playerIndex]->balance -= node->locality->Cost;
            *node->locality->owner.name = game->players[playerIndex]->name;
        } else if (strcmp(option, "n")) {
            return;
        }
    } else {
        printf("Already has a owner");
    }
}

void payRent(Game *game, int playerIndex) {
    Locality currentLocality = getLocality(game->board, game->players[playerIndex]->positionNumber);
    if (currentLocality.owner.name != NULL) {
        printf("this locality has a owner(%s), you have to pay him the rent of %d R$", currentLocality.owner, currentLocality.rentalPrice);
        // add the bankruptcy process
        if (game->players[playerIndex]->balance < currentLocality.rentalPrice) printf("You dont have cash to pay the rent, you lost the game"); return;
        // transfer the values
        currentLocality.owner.balance += currentLocality.rentalPrice;
        game->players[playerIndex]->balance -= currentLocality.rentalPrice;
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
    }
    if (currentLocality.owner.name == game->players[playerIndex]->name && game->players[playerIndex]->balance >= currentLocality.Cost && currentLocality.houseAmount == 1 && currentLocality.hotelAmount == 0) {
        printf("You can build a hotel here, do you wanna do it? y/n \n");
        char option[2];
        scanf("%c", &option);
        if (strcmp(option, "y")) {
            currentLocality.hotelAmount = 1;
            game->players[playerIndex]->balance -= currentLocality.Cost * 2;
            currentLocality.rentalPrice = currentLocality.rentalPrice * 10;
        } else if (strcmp(option, "n")) {
            return;
        }
    }
}
void verifyBankruptcy(Game *game) {
    int i = 0;
    while (game->players[i]->name!= NULL) {
        if (game->players[i]->balance < 0) {
            printf("%s has gone bankrupt! Game over.\n", game->players[i]->name);
            removePlayerFromGame(game, i);
        }
        i++;
    }
}

void removePlayerFromGame(Game *game, int index) {
    int i = 0;
    while (game->players[i]->name!= NULL) {
        game->players[i] = game->players[i + 1];
        i++;
        // remove the player from his localities
    }
}

void nextRound(Game *game) {
    int i = 0;
    while (game->players[i]->name!= NULL) {
        if (game->players[i]->played) {
            game->players[i]->played = false;
        }
        i++;
    }
}
void printGame(Game *game) {
    printf("Current Game State:\n");
    printf("Players:\n");
    for (int i = 0; i < game->numPlayers; i++) {
        printf("Player %d: %s - Balance: %d\n", i, game->players[i]->name, game->players[i]->balance);
    }
    printf("Properties:\n");
    Node *node = &game->board->first;
    while (node != NULL) {
        Locality *locality = node->locality;
        printf("Property %d: %s - Owner: %s - Rental Price: %d\n", locality->owner, locality->address, locality->owner.name, locality->rentalPrice);
        node = node->next;
    }
    printf("\n");
}