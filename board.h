
#define BOARD_H
#include "locality.h"





//creating the structure for the linked list 
//that will handle the localities from the boards
typedef struct 
{
   Locality *locality;
    struct Node *next;
}Node;

typedef struct 
{
    Node first;      
    Node last;
    int size;
}linkedList;
Node *createNode(Locality *locality);

void createList(linkedList *list);
int insertLocality(linkedList *list,Locality *locality);
void printBoard(linkedList *list);
void advance(linkedList *list,Player *player,int num);
Locality getLocality(linkedList *list,int index);

