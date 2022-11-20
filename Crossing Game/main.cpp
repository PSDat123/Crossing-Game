#include <ctime>
#include <fcntl.h>
#include <io.h>
#include "Game.h"

int wmain(){
    int _ = _setmode(_fileno(stdout), _O_U16TEXT);
    fastIO();
    Game game;
    game.startGame();
    return 0;
}