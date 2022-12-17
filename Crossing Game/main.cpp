#include "Game.h"

int main(){
    int _ = _setmode(_fileno(stdout), _O_U16TEXT);
    Console screen;
    Game game(&screen);
    game.startGame();
    return 0;
}