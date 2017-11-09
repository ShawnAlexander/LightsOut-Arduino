/* Read, Eval, Print, Loop for testing. */

#include <iostream>
#include <cstdint>
#include "Board.h"

using namespace std;

int main(int argc, char **argv) {

    Board gb;

    const char BANNER[] = "\n"
            "\n"
            "      ___                    ___           ___                         ___                    ___           ___                   \n"
            "     /  /\\       ___        /  /\\         /  /\\          ___          /  /\\                  /  /\\         /  /\\          ___     \n"
            "    /  /:/      /__/\\      /  /::\\       /  /:/         /__/\\        /  /::\\                /  /::\\       /  /:/         /__/\\    \n"
            "   /  /:/       \\__\\:\\    /  /:/\\:\\     /  /:/          \\  \\:\\      /__/:/\\:\\              /  /:/\\:\\     /  /:/          \\  \\:\\   \n"
            "  /  /:/        /  /::\\  /  /:/  \\:\\   /  /::\\ ___       \\__\\:\\    _\\_ \\:\\ \\:\\            /  /:/  \\:\\   /  /:/            \\__\\:\\  \n"
            " /__/:/      __/  /:/\\/ /__/:/_\\_ \\:\\ /__/:/\\:\\  /\\      /  /::\\  /__/\\ \\:\\ \\:\\          /__/:/ \\__\\:\\ /__/:/     /\\      /  /::\\ \n"
            " \\  \\:\\     /__/\\/:/~~  \\  \\:\\__/\\_\\/ \\__\\/  \\:\\/:/     /  /:/\\:\\ \\  \\:\\ \\:\\_\\/          \\  \\:\\ /  /:/ \\  \\:\\    /:/     /  /:/\\:\\\n"
            "  \\  \\:\\    \\  \\::/      \\  \\:\\ \\:\\        \\__\\::/     /  /:/__\\/  \\  \\:\\_\\:\\             \\  \\:\\  /:/   \\  \\:\\  /:/     /  /:/__\\/\n"
            "   \\  \\:\\    \\  \\:\\       \\  \\:\\/:/        /  /:/     /__/:/        \\  \\:\\/:/              \\  \\:\\/:/     \\  \\:\\/:/     /__/:/     \n"
            "    \\  \\:\\    \\__\\/        \\  \\::/        /__/:/      \\__\\/          \\  \\::/                \\  \\::/       \\  \\::/      \\__\\/      \n"
            "     \\__\\/                  \\__\\/         \\__\\/                       \\__\\/                  \\__\\/         \\__\\/               ";

    const char INFO[] = "Commands\n\'q\' - Quit.\n\'n\' - New Game/Reset.\n\'i\' - Is Solvable?\n";
    const char GRID[] = "| 1| 2| 3| 4| 5|\n"
            "| 6| 7| 8| 9|10|\n"
            "|11|12|13|14|15|\n"
            "|16|17|18|19|20|\n"
            "|21|22|23|24|25|";

    char buffer[2];
    bool persist = true;
    cout << BANNER << endl;
    cout << INFO << endl;
    cout << GRID << endl;
    while(persist) {
        cin.getline(buffer, 2);
        if(cin.good()) {
            if(isalpha(buffer[0])) {
                char c = buffer[0];
                if(c == 'q') {
                    persist = false;
                }
                else if(c == 'n') {
                    cout << "New Game!" << endl;
                    gb.randomize();
                    gb.printConsole();
                }else if(c == 'i'){
                    if(gb.isSolvable()) {
                        cout << "The board is solvable!" << endl;
                    }
                    else {
                        cout << "The board is NOT solvable!" << endl;
                    }
                }else {
                    cout << "Error! Invalid input!" << endl;
                }
            }else if(isdigit(buffer[0])){
                int n = atoi(buffer);
                if(n > 25 || n < 1) {
                    cout << "Error! Invalid input!" << endl;
                }
                else {
                    byte i = (byte) n;
                    gb.toggle(i);
                    gb.printConsole();
                }
            }
            else {
                cout << "Error! Invalid input!" << endl;
            }
        }
        else {
            cout << "Input stream error!" << endl;
            exit(1);
        }
    }


    return 0;
}