#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

int main() {
    printf("testte");
    srand(time(NULL)); 

    Game game;
    startGame(&game);

    
    for (int i = 0; i < game.numPlayers; i++) {
        free(game.players[i]);
    }
    free(game.players);
    

    return 0;
}
