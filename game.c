#include "game.h"
#include <stdio.h>
#include <stdlib.h>

void fillBoard(linkedList *list){
    FILE *file = fopen("/files/localidades.txt","r");
    if (!file)printf("ERROR\n");return;
    char line[512];//buffer to read the lines from the code
    Locality loc;
    while (fgets(line,512,file)){
        char address[100];
        char color[50];
        int cost;
        int rentalprice;
        //extract the information from the line
        sscanf(line, "%s %s %d %d",address,color,cost,rentalprice);
        //create a new node to add to the board
        initializeLocality(&loc,&address,&color,&cost,&rentalprice);
        Node *node = createNode(&loc);
        if(!node)printf("ERROR\n");continue;
        insertLocality(list,&loc);
    }
    
    fclose(file);
}
void addPlayer(Player *player[]){
    FILE *file = fopen("/files/jogadores.txt","r");
    if(!file)printf("ERROR\n");return;
    char line[512];
    Player p;
    int count=0;
    while(fgets(line,512,file)){
    sscanf(line,"%s %d %d",p.name,p.balance,p.num); 
    player[count]=&p;
    count++;
    }
    int numPlayers=count;
}
int rollDice(){
    int numOfHouses;
    int n1 = rand()%6;
    int n2 = rand()%6;
    numOfHouses = n1+n2;
    return numOfHouses;
}
/*Verifica se o jogador passou pela casa de in´ıcio e, se sim, adiciona o bˆonus de In´ıcio ao saldo
do jogador.*/
void movePlayer(linkedList *list,Player *player){
    int housesToWalk;
    housesToWalk = rollDice();
    advance(list,player,housesToWalk);
     Node *node;
    *node->locality= getLocality(list,player->positionNumber);
    //check if there is a house and buy it if doesnt have one yet
    if(node->locality->owner==NULL){
        printf("Doesnt have a owner, wanna buy it for %d R$?\n y/n");
        char option[2];
        scanf("%c",&option);
        if(strcmp(option,"y")){
              buyProperty(list,player);
        }
            else if(strcmp(option,"n")){
                return;
            }        
    }
    
}

void buyProperty(linkedList *list,Player *player){
 Node *node;
    *node->locality= getLocality(list,player->positionNumber);
    //check if there is a house and buy it if doesnt have one yet
    if(node->locality->owner==NULL){
        printf("Doesnt have a owner, wanna buy it for %d R$?\n y/n");
        char option[2];
        scanf("%c",&option);
        if(strcmp(option,"y")){
                player->balance-=node->locality->Cost;
                *node->locality->owner=player->name;
        }
            else if(strcmp(option,"n")){
                return;
            }        
    }

}
