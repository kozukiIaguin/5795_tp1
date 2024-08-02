#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

int main() {
    printf("testte");
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    Game game;
    startGame(&game);

    // Libera a memória alocada
    for (int i = 0; i < game.numPlayers; i++) {
        free(game.players[i]);
    }
    free(game.players);
    // Implementar liberação de memória para o tabuleiro em `board.c`

    return 0;
}
