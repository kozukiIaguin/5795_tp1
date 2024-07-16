
#include "board.h" 
#include <stddef.h>

void initializeList(linkedList *list){
    list->first = malloc(sizeof(Node));
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
Locality getLocality(linkedList *list){
  Node *current = &(list->first);
  int i=0;
  
  while (current !=NULL && i<list->size)
  {
    current = current->next;
    i++;
    if (current!=NULL)
    {
      return *current->locality;
    }else return *current;
  }
}
void advance(linkedList *list,int num){
    
}