#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define START_BONUS 500

void initializeList(LinkedList *list) {
    list->first = NULL;
    list->last = NULL;
    list->size = 0;
}

Node *createNode(Locality *locality) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) return NULL;
    node->locality = locality;
    node->next = NULL;
    return node;
}

void initializeBoard(LinkedList *list) {
    initializeList(list);
    StartLocality *start = (StartLocality *)malloc(sizeof(StartLocality));
    if (!start) {
        perror("Failed to allocate memory for start locality");
        exit(EXIT_FAILURE);
    }

    strcpy(start->address, "START");
    start->numPlayersOnLoc = 0;
    start->playerOnLoc = NULL;
    start->bonus = START_BONUS;

    Locality *startLoc = (Locality *)malloc(sizeof(Locality));
    if (!startLoc) {
        perror("Failed to allocate memory for start locality");
        free(start);
        exit(EXIT_FAILURE);
    }

    initializeLocality(startLoc, start->address, "None", 0, 0);
    insertLocality(list, startLoc);
    free(start);
}

void checkStartBonus(LinkedList *list, Player *player) {
    Locality currentLocality = getLocality(list, player->positionNumber);
    if (strcmp(currentLocality.address, "START") == 0) {
        player->balance += START_BONUS;
        printf("%s has landed on Start and received a bonus of %d\n", player->name, START_BONUS);
    }
}

int insertLocality(LinkedList *list, Locality *locality) {
    Node *node = createNode(locality);
    if (!node) {
        return 0; // Return 0 to indicate failure
    }
    if (list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        list->last = node;
    }
    list->size++;
    return 1;
}

Locality getLocality(LinkedList *list, int index) {
    Node *current = list->first;
    int i = 0;

    while (current != NULL && i < index) {
        current = current->next;
        i++;
    }

    if (current != NULL && i == index) {
        return *(current->locality);
    } else {
        return (Locality){}; // Return an empty locality
    }
}
void advance(LinkedList *list, Player *player, int num) {
    int playerIndex = player->positionNumber;
    Node *node = list->first;
    
    // Remove player from the old location
    for (int j = 0; j < list->size; j++) {
        if (node->locality && node->locality->playerOnLoc) {
            for (int k = 0; k < node->locality->numPlayersOnLoc; k++) {
                if (strcmp(node->locality->playerOnLoc[k].name, player->name) == 0) {
                    removePlayerFromLocality(node->locality, k);
                    break;
                }
            }
        }
        node = node->next;
    }
    
    // Move player to the new location
    node = list->first;
    for (int k = 0; k < num; k++) {
        if (node->next != NULL) {
            node = node->next;
        } else {
            node = list->first;
            checkStartBonus(list, player);
        }
    }

    // Update player's position
    player->positionNumber = playerIndex;

    // Ensure `playerOnLoc` is allocated properly
    Locality *loc = node->locality;
    if (loc->playerOnLoc == NULL) {
        loc->playerOnLoc = malloc(sizeof(Player)); // Initial allocation if NULL
    } else {
        loc->playerOnLoc = realloc(loc->playerOnLoc, (loc->numPlayersOnLoc + 1) * sizeof(Player));
    }
    if (!loc->playerOnLoc) {
        perror("Failed to allocate memory for players on locality");
        exit(EXIT_FAILURE);
    }

    // Add player to the new location
    loc->playerOnLoc[loc->numPlayersOnLoc] = *player;
    loc->numPlayersOnLoc++;
}


void printBoard(LinkedList *list) {
    Node *node = list->first;
    while (node != NULL) {
        printf("%s -->", node->locality->address);
        node = node->next;
    }
    printf("NULL\n");
}
