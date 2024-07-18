#include "game.h"
#include <stdio.h>

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
        scanf(line, "%s %s %d %d",address,color,cost,rentalprice);
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
    scanf(line,"%s %d %d",p.name,p.balance,p.num); 
    player[count]=&p;
    count++;
    }
    int numPlayers=count;
}
