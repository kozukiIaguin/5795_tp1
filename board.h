#ifndef BOARD_H
#define BOARD_H

#include "locality.h"

// Node for the linked list
typedef struct Node {
    Locality *locality;
    struct Node *next;
} Node;

// LinkedList for the board
typedef struct {
    Node *first;
    Node *last;
    int size;
} LinkedList;

Node *createNode(Locality *locality);
void initializeList(LinkedList *list);
int insertLocality(LinkedList *list, Locality *locality);
void printBoard(LinkedList *list);
void advance(LinkedList *list, Player *player, int num);
Locality getLocality(LinkedList *list, int index);
void initializeBoard(LinkedList *list);
void checkStartBonus(LinkedList *list, Player *player);

#endif
