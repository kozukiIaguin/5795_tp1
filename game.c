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
    if(player->positionNumber==0)printf("This is start house, you cant buy it");return;
    
    //already check the bnus feature of the start locality
    
}

void buyProperty(linkedList *list,Player *player){
 Node *node;
    *node->locality= getLocality(list,player->positionNumber);
    //check if there is a house and buy it if doesnt have one yet
    if(node->locality->owner.name==NULL){
        printf("Doesnt have a owner, wanna buy it for %d R$?\n y/n");
        char option[2];
        scanf("%c",&option);
        if(strcmp(option,"y")){
            //check if the players balance is enought to buy it
            if(player->balance<node->locality->Cost){
                printf("Insuficient balance");
                return;
            }
                player->balance-=node->locality->Cost;
                *node->locality->owner.name=player->name;
        }
            else if(strcmp(option,"n")){
                return;
            }        
    }
    else{
        printf("Already has a owner");
    }

}
void payRent(linkedList *list, Player *player){
    Locality currentLocality = getLocality(list,player->positionNumber);
    if(currentLocality.owner.name!=NULL){
        printf("this locality has a owner(%s), you have to pay him the rent of %d R$",currentLocality.owner,currentLocality.rentalPrice);
        //add the bankruptcy process
        if(player->balance<currentLocality.rentalPrice)printf("You dont have cash to pay the rent, you lost the game");return;
        //transfer the values
        currentLocality.owner.balance+=currentLocality.rentalPrice;
        player->balance-=currentLocality.rentalPrice;
    }
}
void build(linkedList *list, Player *player){
    Locality currentLocality = getLocality(list,player->positionNumber);
    if(currentLocality.owner.name==player->name && player->balance>=currentLocality.Cost && currentLocality.houseAmount==0 &&currentLocality.hotelAmount==0){
        printf("You can build a house here, do you wanna do it? y/n \n");
        char option[2];
        scanf("%c",&option);
        if(strcmp(option,"y")){
            currentLocality.houseAmount=1;
            player->balance-=currentLocality.Cost;
            currentLocality.rentalPrice=currentLocality.rentalPrice*5;
        }
            else if(strcmp(option,"n")){
                return;
            }        
    }
     if(currentLocality.owner.name==player->name && player->balance>=currentLocality.Cost && currentLocality.houseAmount==1 &&currentLocality.hotelAmount==0){
         printf("You can build a hotel here, do you wanna do it? y/n \n");
        char option[2];
        scanf("%c",&option);
        if(strcmp(option,"y")){
            currentLocality.hotelAmount=1;
            player->balance-=currentLocality.Cost*2;
            currentLocality.rentalPrice=currentLocality.rentalPrice*10;
        }
            else if(strcmp(option,"n")){
                return;
            }      

     }
}
void verifyBankruptcy(Player *player[]){
    int i=0;
    while (strcmp(*player[i]->name!=NULL)){
       if (player[i]->balance<0){
        printf("%s has gone bankrupt! Game over.\n", player[i]->name);
        removePlayerFromGame(player,i);
        

    }
    i++;
    }
}
void removePlayerFromGame(Player *player[], int index){
    int i=0;
    while(strcmp(*player[i]->name!=NULL)){
        player[i]=player[i+1];
        i++;
    }

}