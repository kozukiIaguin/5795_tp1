
#include "board.h" 
#include <stddef.h>

void initializeList(linkedList *list){
    list->last = list->first; 
    list->first.next = NULL; 
    list->first.locality = NULL; 
    list->size=0;
}

//create a cell of the linked list
Node *createNode(Locality *locality) {
   Node *node = malloc(sizeof(Node));
   if(!node)return NULL;
   node->locality = locality;
   node->next=NULL;
   return node;
}

////////////////////////////////////////////
int insertLocality(linkedList *list, Locality *locality) {
    Node *node = createNode(locality);
    if (!node) {
        return 0; // Return 0 to indicate failure
    }
    if (list->first.locality == NULL) {
        list->first = *node;
        list->last = *node;
    } else {
        list->last.next = node;
        list->last = *node;
    }
    list->size++; 
    return 1; 
}
Locality getLocality(linkedList *list,int index){
  Node *current = &(list->first);
  int i=0;
  
  while (current !=NULL && i<index)
  {
    current = current->next;
    i++;
    if (current!=NULL && i==index)
    {
      return *current->locality;
    }else // Handle the case when the index is out of bounds
        return (Locality){}; // Return an empty locality
  }
}
void advance(linkedList *list,Player *player, int num){
    int playerIndex;
    Locality *currentLocality=list->first.locality, *nextLocality;
    for (int j = 0; j < list->size; j++){
      //compare and remove the player from the locality
      if (strcmp(currentLocality->playerOnLoc[0].name,player->name)==0){
          removePlayerFromLocality(&currentLocality,j);
          playerIndex=j;
          player->positionNumber=playerIndex;
      }
    }
     //moves it to the location
      Node *node = &(list->first);
      for (int k = 0; k < num; k++)
      {
        node = node->next;
        if(node==NULL){
          node=&(list->first);
        }
      }
      int numOnThisLoc = node->locality->numPlayersOnLoc;
      node->locality->playerOnLoc[numOnThisLoc]=*player;
      node->locality->numPlayersOnLoc++;
}
void printBoard(linkedList *list){
  Node *node = &(list->first);
  while (node->next!=NULL)
  {
    printf("%s -->",node->locality->address);
    node = node->next;
  } 
}