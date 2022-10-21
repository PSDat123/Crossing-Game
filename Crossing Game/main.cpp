#include "Console.h"

using namespace std;

int main(){
    FixConsoleWindow();
    while (true) {
        if (KeyHit('a')) {
            cout << "a";
        }
        Sleep(10);
    }
}