#include "locality.h"




//creating the structure for the linked list 
//that will handle the localities from the boards

typedef struct {
 Locality *Locality;
 struct node *next;   
}Node;
Locality createLocality();
void insertLocality(Node* head,Locality *Locality);
void printBoard(Node *node);
void advance(Node *node, int num);
