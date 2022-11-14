#include <ctime>
#include <fcntl.h>
#include <io.h>
#include "Game.h"

int wmain(){
    int _ = _setmode(_fileno(stdout), _O_U16TEXT);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    Game game;
    game.startGame();
    return 0;
}