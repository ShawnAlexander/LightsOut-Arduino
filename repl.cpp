/* Read, Eval, Print, Loop for testing. */

#include <iostream>
#include <cstdint>
#include <string>
#include <algorithm>
#include "Board.h"

using namespace std;

Board gb;

void isSolvable(bool (&p)[(uint8_t) 25]) {
    if(!gb.dot(gb.SOLVABLE1, p) && !gb.dot(gb.SOLVABLE2, p)) {
        cout << "Solvable!" << endl;
    }
    else {
        cout << "Not Solvable!" << endl;
    }
}

void reset(bool (&p)[(uint8_t) 25]) {
    for (uint8_t i = 0; i < (uint8_t) 25; ++i) {
        p[i] = false;
    }
}

void comb(int n, int r, int *arr, int sz) {
    for (int i = n; i >= r; i --) {
        arr[r - 1] = i;
        if (r > 1) {
            comb(i - 1, r - 1, arr, sz);
        } else {
            char OUT_STR[26] = "0000000000000000000000000";
            for (int j = 0; j < sz; j++) {
                OUT_STR[arr[j] - 1] = '1';
            }
            cout << OUT_STR << endl;
        }
    }
}


int main(int argc, char **argv) {

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

    const char INFO[] = "Commands\n\'q\' - Quit.\n\'n\' - New Game/Reset.\n\'i\' - Is Solvable?\n\'t\' - Run Tests.\n";
    const char GRID[] = "| 0| 1| 2| 3| 4|\n"
            "| 5| 6| 7| 8| 9|\n"
            "|10|11|12|13|14|\n"
            "|15|16|17|18|19|\n"
            "|20|21|22|23|24|";

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
                    cout << "Randomization Choice?" << endl;
                    cin.getline(buffer, 1);
                    if(isdigit(buffer[0])) {
                        int n = atoi(buffer);
                        if(n == 1) {
                            gb.reset();
                            gb.randomize(1);
                            gb.printConsole();
                        }
                        else if(n == 2) {
                            gb.reset();
                            gb.randomize(2);
                            gb.printConsole();
                        }
                        else {
                            cout << "Error! Invalid input!" << endl;
                        }
                    }
                    else {
                        cout << "Error! Invalid input!" << endl;
                    }
                }
                else if(c == 'i'){
                    if(gb.isSolvable()) {
                        cout << "The board is solvable!" << endl;
                    }
                    else {
                        cout << "The board is NOT solvable!" << endl;
                    }
                }
                else if(c == 't') {
                    /*
                    if(!gb.add(false, false)) {
                        cout << "Test #1 Passed!" << endl;
                    }else{
                        cout << "Test #1 Failed!" << endl;
                    }
                    if(gb.add(true, false)) {
                        cout << "Test #2 Passed!" << endl;
                    }else{
                        cout << "Test #2 Failed!" << endl;
                    }
                    if(gb.add(false, true)) {
                        cout << "Test #3 Passed!" << endl;
                    }else{
                        cout << "Test #3 Failed!" << endl;
                    }
                    if(!gb.add(true, true)) {
                        cout << "Test #4 Passed!" << endl;
                    }else{
                        cout << "Test #4 Failed!" << endl;
                    }*/
                    bool solvable[gb.RC] = {false, true, false, false, false,
                                             false, false, true, false, false,
                                             false, true, false, true, false,
                                             false, true, true, false, true,
                                             true, false, false, false, false};
                    bool notsolvable1[gb.RC] = {true, false, false, true, false,
                                                       false, false, true, false, false,
                                                       false, true, true, false, true,
                                                       false, true, false, false, false,
                                                       true, false, false, false, false};

                    isSolvable(solvable);
                    isSolvable(notsolvable1);

                    bool temp[gb.RC] = {false, false, false, false, false,
                                        false, false, false, false, false,
                                        false, false, false, false, false,
                                        false, false, false, false, false,
                                        false, false, false, false, false};
                    bool test[gb.RC] = {true, true, true, true, false,
                                        false, false, false, false, false,
                                        false, false, false, false, false,
                                        false, false, false, false, false,
                                        false, false, false, false, false};

                    gb.mvm(gb.A, test, temp);
                    gb.printConsole(temp);
                    isSolvable(temp);
                    reset(temp);
                    cout << "Begin Solution Space Test!" << endl;
                    for(int i = 1; i < 25; ++i) {
                        int buf[i];
                        comb(25, i, buf, i);
                        cout << "WARNING! This procedure consumes a lot of time and space! Continue with next iteration?" << endl;
                        cin.getline(buffer,2);
                        char pe = buffer[0];
                        if(!cin.good() || tolower(pe) != 'y'){
                            break;
                        }
                    }
                }
                else {
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