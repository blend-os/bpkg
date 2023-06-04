#include <iostream>
#include <string>
#include <vector>
#include "statichash.h"
#include "misclib.hpp"
#include "games.hpp"

using std::cout;
using std::cin;
using std::string;
using misc::cls;
using misc::waitenter;
using misc::printc;

string version = "0.2.1";

int help(int id) {
    cls();
    std::vector<string> text;

    switch (id) {
        case 4: // rps
            text = {
                "CLI-MG HELP - RPS\n",

                "rps is a digital version of \"Rock paper scissors\" where you play against the computer.",
                "Upon entering rps you will be asked to select a move.",
                "You can select it just like you would a game in the main menu.",
                "If you need help with such menu navigation, please refer to the Menu help topic.\n",
                "After selecting your move the computer will make its move and tell you the results.",
                "You will be prompted with a y/n prompt asking you whether you want to play again or not.",
                "By pressing \"y\" and pressing ENTER the game will start over.",
                "By pressing \"n\" and pressing ENTER the game will return to the main menu."
            };
            break;
        case 1: // guessnum
            text = {
                "CLI-MG HELP - GUESSNUM\n",

                "Guessnum is a \"guess the number\" style game.",
                "Upon entering guessnum you will be asked to select a difficulty.",
                "There are currently 3 difficulties available: Easy, medium and hard.",
                "You can select it just like you would a game in the main menu.",
                "If you need help with such menu navigation, please refer to the Menu help topic.\n",
                "After selecting a difficulty, the game will tell you the possible range of the number you are guessing.",
                "You can guess a number by typing the number in and pressing ENTER.",
                "If the number is wrong, the game will tell you if the desired number is bigger or smaller than the number you inputted.",
                "If the number is right, the game will end and the number of attempts the guessing took you will be displayed.",
                "The inputting will loop until you guess the number."
            };
            break;
        case 2: // unscramble
            text = {
                "CLI-MG HELP - UNSCRAMBLE\n",

                "Unscramble is a game where you need to unscramble scrambled letters (anagrams).",
                "Upon entering unscramble you will be asked to select a gamemode.",
                "There are currently 2 gamemodes available: Classic and practise.",
                "You can select a gamemode just like you would a game in the main menu.",
                "If you need help with such menu navigation, please refer to the Menu help topic.",
                "In classic if you guess wrong, the game is over. Each correct answer gives you 1 point and each word skip deducts 1 point.",
                "The minimum number of points is 0 and the game will not deduct points below that point.",
                "In practise mode the game goes on forever until you exit and it exists for practising your skills.",
                "Afterwards you will be asked to select a difficulty.",
                "There are currently 3 difficulties available: Easy, medium and hard.",
                "As you increase the diffcitulty, the average length of the words inscreases.\n",
                "Alright, we can now start playing!",
                "The game will tell you the scrambled word and you can input your unscrambled word.",
                "Let's list some other options available while playing unscramble.",
                "You can type \"showword\" in case you want to show the scrambled word again.",
                "You can also type \"skip\" to skip the word you are currently on, or you can type \"exit\" to exit the game.",
            };
            break;
        case -1: // menu
            text = {
                "CLI-MG HELP - MENU\n",

                "The cli-mg menu is command line based, but simple.",
                "To select a game, you can either type the game's name or its ID and press ENTER.",
                "If you want to select \"guessnum\", you can type either \"guessnum\" or \"1\".",
                "The game IDs and their names are shown in the main manu game list.",
                "In the cli-mg menu \"guessnum\" which has the ID of 1 is defined as: \"1) Guessnum\".",
                "One more thing worth mentioning is that if your command line column resolution is less than 70, ASCII art will not be displayed."
            };
            break;
        case 8: // license
            if (misc::getcol() >= 70) {
                cout    
                << "  _      _\n"
                << " | |    (_)\n"
                << " | |     _  ___ ___ _ __  ___  ___\n"
                << " | |    | |/ __/ _ \\ '_ \\/ __|/ _ \\\n"
                << " | |____| | (_|  __/ | | \\__ \\  __/\n"
                << " |______|_|\\___\\___|_| |_|___/\\___|\n\n";
            }
            text = {
                "MIT License\nCopyright (c) 2022, 2023 svgaming234",
                "Permission is hereby granted, free of charge, to any person obtaining a copy",
                "of this software and associated documentation files (the \"Software\"), to deal",
                "in the Software without restriction, including without limitation the rights",
                "to use, copy, modify, merge, publish, distribute, sublicense, and/or sell",
                "copies of the Software, and to permit persons to whom the Software is",
                "furnished to do so, subject to the following conditions:\n",

                "The above copyright notice and this permission notice shall be included in all",
                "copies or substantial portions of the Software.\n",

                "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR",
                "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,",
                "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE",
                "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER",
                "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,",
                "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE",
                "SOFTWARE.\n",

                "The statichash.h file is licenced seperately using a modified BSD-2-Clause licence shown below:\n",

                "Copyright (c) 2015 by Lukas S. van der Heeden",
                "All rights reserved.\n",

                "Modified by Erik Jakin on 6.7.2022.\n",

                "Modified by Sven Kovač on 8/13/2022.\n",

                "Use license: Modified from standard BSD license.",
                "Redistribution and use in source and binary forms are permitted",
                "provided that the above copyright notice and this paragraph are",
                "duplicated in all such forms and that any documentation, advertising",
                "materials, Web server pages, and other materials related to such",
                "distribution and use acknowledge that the software was developed",
                "by Lukas S. van der Heeden. The name \"Lukas S. van der Heeden\" may",
                "not be used to endorse or promote products derived from this",
                "software without specific prior written permission.\n",

                "THIS SOFTWARE IS PROVIDED \"AS IS\" AND WITHOUT ANY EXPRESS OR",
                "IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED",
                "WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE."
            };
            break;
        default:
            return 1; // help topic not found
    }

    cout << "Press ENTER to scroll.\n";
    cin.ignore();

    // scroll on enter being pressed until everything is scrolled through
    for (int i = 0; i <= text.size() - 1; i++) {
        cin.get();
        cout << text[i];
    }
    cout << "\n";

    waitenter();
    return 0;
}

int main(int argc, char *argv[]) {
    bool playedarg = false;
    int exitcode;
    string choice, gamename;
    cls();
    while (true) {
        exitcode = 0;
        // if a game argument is provided and we haven't played this session yet, launch the game with the name from the argument
        if (argc >= 2 && playedarg != true) {
            choice = argv[1];
            playedarg = true;
        }
        else {
            if (misc::getcol() < 70) {
                cout 
                << "Welcome to cli-mg! (v" << version << ")\n"
                << "Type the ID of the game\n"
                << "you want to play (or its\n"
                << "title) and press ENTER.\n"
                << "Enjoy!\n\n";
            }
            else {
                cout 
                << "   _____ _      _____      __  __  _____\n"
                << "  / ____| |    |_   _|    |  \\/  |/ ____|  Welcome to cli-mg! (v" << version << ")\n"
                << " | |    | |      | |______| \\  / | |  __   Type the ID of the game\n"
                << " | |    | |      | |______| |\\/| | | |_ |  you want to play (or its\n"
                << " | |____| |____ _| |_     | |  | | |__| |  title) and press ENTER.\n"
                << "  \\_____|______|_____|    |_|  |_|\\_____|  Enjoy!\n\n";
            }

            printc("1) ", 'y'); printc("guessnum\n");
            printc("2) ", 'y'); printc("unscramble\n");
            printc("3) ", 'y'); printc("dice\n");
            printc("4) ", 'y'); printc("rps\n\n");

            printc("8) ", 'y'); printc("Read license\n");
            printc("9) ", 'y'); printc("Help\n");
            printc("0) ", 'y'); printc("Exit game\n");

            cin >> choice;
            choice = misc::lower(choice);
        }
        
        switch(hashString(choice.c_str())) {
            case HASH_S4("3"):
            case HASH_S4("dice"):
                gamename = "dice";
                exitcode = dice();
                cls();
                break;
            case HASH_S4("1"):
            case HASH_S16("guessnum"):
                gamename = "guessnum";
                exitcode = guessnum();
                cls();
                break;
            case HASH_S4("2"):
            case HASH_S16("unscramble"):
                gamename = "unscramble";
                exitcode = unscramble();
                cls();
                break;
            case HASH_S4("4"):
            case HASH_S4("rps"):
                gamename = "rps";
                exitcode = rps();
                cls();
                break;
            case HASH_S4("8"):
            case HASH_S16("license"):
                gamename = "license";
                exitcode = help(8);
                cls();
                break;
            case HASH_S4("9"):
            case HASH_S16("help"):
                gamename = "help";
                exitcode = help(-1);
                cls();
                break;
            case HASH_S4("0"):
            case HASH_S4("exit"):
                return 0;
            default:
                cls();
                printc("Please enter a valid game choice/argument.\n", 'r');
        }
        if (exitcode != 0) {
            printc("ERROR: ", 'r');
            printc(gamename, 'r');
            printc(" exited with exit code ", 'r');
            printc(std::to_string(exitcode), 'r');
            printc("\n");
        }
    }
    return 0;
}