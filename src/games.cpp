#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include "statichash.h"
#include "misclib.hpp"
#include "menu.hpp"
#include "games.hpp"

using std::cout;
using std::cin;
using std::string;
using misc::cls;
using misc::waitenter;
using misc::randint;
using misc::printc;

int dice() {
    beggining:
    cls();

    if (misc::getcol() >= 70) {
        cout
        << "  _____  _\n"
        << " |  __ \\(_)\n"
        << " | |  | |_  ___ ___\n"
        << " | |  | | |/ __/ _ \\\n"
        << " | |__| | | (_|  __/\n"
        << " |_____/|_|\\___\\___|\n\n";
    }

    // pick a random number between 1 and 6 and print it
    int rngResult = randint(1, 6);
    cout << "You rolled ";
    printc(std::to_string(rngResult) + "\n", 'y');

    // print corresponding ascii art
    switch(rngResult) {
        case 1:
            cout
            << " -----------------\n"
            << "|                 |\n"
            << "|                 |\n"
            << "|                 |\n"
            << "|        O        |\n"
            << "|                 |\n"
            << "|                 |\n"
            << "|                 |\n"
            << " -----------------\n";
            break;
        case 2:
            cout
            << " -----------------\n"
            << "| O               |\n"
            << "|                 |\n"
            << "|                 |\n"
            << "|                 |\n"
            << "|                 |\n"
            << "|                 |\n"
            << "|               O |\n"
            << " -----------------\n";
            break;
        case 3:
            cout
            << " -----------------\n"
            << "|               O |\n"
            << "|                 |\n"
            << "|                 |\n"
            << "|        O        |\n"
            << "|                 |\n"
            << "|                 |\n"
            << "| O               |\n"
            << " -----------------\n";
            break;
        case 4:
            cout
            << " -----------------\n"
            << "| O             O |\n"
            << "|                 |\n"
            << "|                 |\n"
            << "|                 |\n"
            << "|                 |\n"
            << "|                 |\n"
            << "| O             O |\n"
            << " -----------------\n";
            break;
        case 5:
            cout
            << " -----------------\n"
            << "| O             O |\n"
            << "|                 |\n"
            << "|                 |\n"
            << "|        O        |\n"
            << "|                 |\n"
            << "|                 |\n"
            << "| O             O |\n"
            << " -----------------\n";
            break;
        case 6:
            cout
            << " -----------------\n"
            << "| O             O |\n"
            << "|                 |\n"
            << "|                 |\n"
            << "| O             O |\n"
            << "|                 |\n"
            << "|                 |\n"
            << "| O             O |\n"
            << " -----------------\n";
            break;
    }

    // y/n screen
    cout << "Do you want to roll again? (y/n)\n";
    std::string yn;
    cin >> yn;
    if (yn == "y" || yn == "Y") {
        goto beggining;
    }
    return 0;
}






int guessnum() {
    cls();
    difficultyscreen:

    if (misc::getcol() >= 70) {
        cout
        << "   _____\n"
        << "  / ____|\n"
        << " | |  __ _   _  ___  ___ ___ _ __  _   _ _ __ ___\n"
        << " | | |_ | | | |/ _ \\/ __/ __| '_ \\| | | | '_ ` _ \\\n"
        << " | |__| | |_| |  __/\\__ \\__ \\ | | | |_| | | | | | |\n"
        << "  \\_____|\\__,_|\\___||___/___/_| |_|\\__,_|_| |_| |_|\n\n";
    }

    cout << "Select a difficulty.\nOptions: \n\n";

    printc("1) ", 'y'); printc("Easy\n");
    printc("2) ", 'y'); printc("Medium\n");
    printc("3) ", 'y'); printc("Hard\n");
    printc("4) ", 'y'); printc("Custom\n\n");

    printc("9) ", 'y'); printc("Help\n");
    printc("0) ", 'y'); printc("Exit to menu\n");

    string difficulty;
    cin >> difficulty;
    difficulty = misc::lower(difficulty);
    int maxnum;
    int attempts = 0;

    // defines max. posssible number based on difficulty
    switch (hashString(difficulty.c_str())) {
        case HASH_S4("1"):
        case HASH_S4("easy"):
            maxnum = 100;
            break;
        case HASH_S4("2"):
        case HASH_S16("medium"):
            maxnum = 1000;
            break;
        case HASH_S4("3"):
        case HASH_S4("hard"):
            maxnum = 10000;
            break;
        case HASH_S4("4"):
        case HASH_S16("custom"):
            cout << "Enter a max. guess number for the game.\n";
            cin >> maxnum;
            break;
        case HASH_S4("9"):
        case HASH_S16("help"):
            help(1);
            cls();
            goto difficultyscreen;
            break;
        case HASH_S4("0"):
        case HASH_S4("exit"):
            cls();
            return 0;
        default:
            cls();
            printc("Invalid option.\n", 'r');
            goto difficultyscreen;
    }

    cls();
    cout << "Guess the random number from 1 to " << maxnum << "!\n";

    int rngResult = randint(1, maxnum);
    string answer;
    int answerint;

    guesser:
    cin >> answer;

    if (answer == "exit") {
        cls();
        return 0;
    }
    else if (answer == "igiveup") { // easter egg :)
        cout << "You found an easter egg! The answer is ";
        printc(std::to_string(rngResult), 'y');
        cout << "\n";
        goto guesser;
    }

    int numcount = 0;
    for (int i = 0; i < strlen(answer.c_str()); i++) { // check if string contains a number or a word
        if (isdigit(answer[i])) {
            numcount++; // when a digit is detected increase value of variable
        }
    }
    if (numcount == strlen(answer.c_str())) {
        answerint = std::stoi(answer); // if number of digits matches up with length of the string, we have a number
    }
    else {
        printc("Please enter a number.\n", 'y');
        goto guesser;
    }

    if (answerint == rngResult) {
        attempts++;
        printc("You guessed right! Congrats!\n", 'g');
        cout << "It took you ";
        printc(std::to_string(attempts), 'y');
        if (attempts == 1) {
            cout << " attempt.\n";
        }
        else {
            cout << " attempts.\n";
        }
        waitenter();
        cls();
        return 0;
    }
    else {
        attempts++;
        printc("That's not the right answer.\n", 'y');
        if (rngResult < answerint) {
            printc("The desired number is smaller.\n", 'y');
        }
        else {
            printc("The desired number is bigger.\n", 'y');
        }
        goto guesser;
    }

    return 0;
}






int rps() {
    cls();
    beggining:
    
    if (misc::getcol() >= 70) {
        cout
        << "  _____  _____   _____ \n"
        << " |  __ \\|  __ \\ / ____|\n"
        << " | |__) | |__) | (___  \n"
        << " |  _  /|  ___/ \\___ \\ \n"
        << " | | \\ \\| |     ____) |\n"
        << " |_|  \\_\\_|    |_____/ \n\n";
    }

    cout << "Type the play you want to do. \nOptions: \n\n";

    printc("1) ", 'y'); printc("Rock\n");
    printc("2) ", 'y'); printc("Paper\n");
    printc("3) ", 'y'); printc("Scissors\n\n");

    printc("9) ", 'y'); printc("Help\n");
    printc("0) ", 'y'); printc("Exit to menu\n");

    string plplay;
    cin >> plplay;
    plplay = misc::lower(plplay);

    switch (hashString(plplay.c_str())) {
        case HASH_S4("1"):
        case HASH_S4("rock"):
            plplay = "rock";
            break;
        case HASH_S4("2"):
        case HASH_S16("paper"):
            plplay = "paper";
            break;
        case HASH_S4("3"):
        case HASH_S16("scissors"):
            plplay = "scissors";
            break;
        case HASH_S4("9"):
        case HASH_S16("help"):
            help(4);
            cls();
            goto beggining;
            break;
        case HASH_S4("0"):
        case HASH_S16("exit"):
            return 0;
            break;
        default:
            cls();
            printc("Invalid option.\n", 'r');
            goto beggining;
            break;
    }

    cls();
    cout << "Rock, Paper, Scissors!\n\n";

    // pick randomly between rock, paper and scissors
    int rngResult = randint(1, 3);
    string play;
    switch (rngResult) {
        case 1:
            play = "rock";
            break;
        case 2:
            play = "paper";
            break;
        case 3:
            play = "scissors";
            break;
    }

    // decide who won
    switch (hashString(plplay.c_str())) {
        case HASH_S4("rock"): 
            switch(hashString(play.c_str())) {
                case HASH_S16("paper"):
                    printc("You lose!\n", 'r');
                    break;
         
                case HASH_S16("scissors"):
                    printc("You win!\n", 'g');
                    break;
               
                case HASH_S4("rock"):
                    printc("It's a tie!\n", 'y');
                    break;
            }
            break;
        case HASH_S16("paper"): 
            switch(hashString(play.c_str())) {
                case HASH_S4("rock"):
                    printc("You win!\n", 'g');
                    break;
            
                case HASH_S16("scissors"):
                    printc("You lose!\n", 'r');
                    break;
              
                case HASH_S16("paper"):
                    printc("It's a tie!\n", 'y');
                    break;
            }
            break;
        case HASH_S16("scissors"): 
            switch(hashString(play.c_str())) {
                case HASH_S4("rock"):
                    printc("You lose!\n", 'r');
                    break;

                case HASH_S16("paper"):
                    printc("You win!\n", 'g');
                    break;
   
                case HASH_S16("scissors"):
                    printc("It's a tie!\n", 'y');
                    break;
            }
            break;
        default:
            break;
    }

    cout 
    << "\nYou played: " << plplay << "\n"
    << "The computer played: " << play << "\n\n";

    cout << "Do you want to play again? (y/n)\n";
    std::string yn;
    cin >> yn;
    if (yn == "y" || yn == "Y") {
        cls();
        goto beggining;
    }
    return 0;
}






int unscramble() {
    std::vector<string> words;
    string input, mode;
    int maxnum;

    cls();

    modes:
    if (misc::getcol() >= 70) {
        cout
        << "  _    _                                    _     _\n"
        << " | |  | |                                  | |   | |\n"
        << " | |  | |_ __  ___  ___ _ __ __ _ _ __ ___ | |__ | | ___\n"
        << " | |  | | '_ \\/ __|/ __| '__/ _` | '_ ` _ \\| '_ \\| |/ _ \\\n"
        << " | |__| | | | \\__ \\ (__| | | (_| | | | | | | |_) | |  __/\n"
        << "  \\____/|_| |_|___/\\___|_|  \\__,_|_| |_| |_|_.__/|_|\\___|\n\n";
    }

    cout << "Select a mode.\nOptions: \n\n";

    printc("1) ", 'y'); printc("Classic\n");
    printc("2) ", 'y'); printc("Practise\n\n");

    printc("9) ", 'y'); printc("Help\n");
    printc("0) ", 'y'); printc("Exit to menu\n");

    cin >> input;
    input = misc::lower(input);

    switch (hashString(input.c_str())) {
        case HASH_S4("1"):
        case HASH_S16("classic"):
            mode = "classic";
            break;
        case HASH_S4("2"):
        case HASH_S16("practise"):
            mode = "practise";
            break;
        case HASH_S4("9"):
        case HASH_S16("help"):
            help(2);
            cls();
            goto modes;
            break;
        case HASH_S4("0"):
        case HASH_S4("exit"):
            return 0;
            break;
        default:
            cout << "Invalid option.\n";
            goto modes;
    }

    cls();

    difficulties:
    if (misc::getcol() >= 70) {
        cout
        << "  _    _                                    _     _\n"
        << " | |  | |                                  | |   | |\n"
        << " | |  | |_ __  ___  ___ _ __ __ _ _ __ ___ | |__ | | ___\n"
        << " | |  | | '_ \\/ __|/ __| '__/ _` | '_ ` _ \\| '_ \\| |/ _ \\\n"
        << " | |__| | | | \\__ \\ (__| | | (_| | | | | | | |_) | |  __/\n"
        << "  \\____/|_| |_|___/\\___|_|  \\__,_|_| |_| |_|_.__/|_|\\___|\n\n";
    }

    cout << "Select a difficulty.\nOptions: \n\n";

    printc("1) ", 'y'); printc("Easy\n");
    printc("2) ", 'y'); printc("Medium\n");
    printc("3) ", 'y'); printc("Hard\n\n");

    printc("9) ", 'y'); printc("Help\n");
    printc("0) ", 'y'); printc("Exit to menu\n");

    cin >> input;
    input = misc::lower(input);

    // define words based on difficulty
    switch (hashString(input.c_str())) {
        case HASH_S4("1"):
        case HASH_S4("easy"):
            words = {
                "Cope",
                "Lazy",
                "Belt",
                "Bury",
                "Tire",
                "Good",
                "Crop",
                "Mess",
                "Hate",
                "Sick",
                "Sand",
                "Rage",
                "Side",
                "Cane",
                "High",
                "Cow",
                "Tire",
                "Oral",
                "Rule",
                "Palm",
                "Sale",
                "Riot",
                "Job",
                "Stab",
                "Pick",
                "Maze",
                "Fuss",
                "Hall",
                "Put",
                "Pie",
                "Fork",
                "God",
                "Film",
                "Jam",
                "Lamb",
                "Chew",
                "Bee",
                "Dare",
                "Care",
                "Dump",
                "Wing",
                "Taxi",
                "Wave",
                "Pile",
                "Doll",
                "Lose",
                "Twin",
                "Help",
                "Flat",
                "Yard",
                "Cook",
                "Rub",
                "Bush",
                "Duty",
                "Gem",
                "Deep",
                "Blue",
                "Late",
                "Dash",
                "Love",
                "Cry",
                "Kit",
                "Year",
                "Drop",
                "Clay",
                "Pool",
                "Golf",
                "Task",
                "Slap",
                "Jam",
                "Have",
                "Hay",
                "Get",
                "File",
                "Rent",
                "Fuel",
                "Hit",
                "Hero",
                "Zone",
                "Mold",
                "Size",
                "Face",
                "Gear",
                "Trap",
                "Pest",
                "Mess",
                "Tick",
                "Pass",
                "Year",
                "Node",
                "Cave",
                "Ant",
                "Rice",
                "Bean",
                "Tin",
                "Grip",
                "Read"
            };
            break;
        case HASH_S4("2"):
        case HASH_S16("medium"):
            words = {
                "Letter",
                "Relax",
                "Bottom",
                "New",
                "Prison",
                "Punish",
                "Wander",
                "Wrist",
                "Dirty",
                "Seek",
                "Tip",
                "Sand",
                "Shape",
                "Grass",
                "Global",
                "Like",
                "Insist",
                "Row",
                "Deer",
                "Museum",
                "Movie",
                "Leader",
                "Refuse",
                "Friend",
                "Troop",
                "Owl",
                "Era",
                "Tongue",
                "Dance",
                "Beg",
                "Pain",
                "Woman",
                "Fuss",
                "Watch",
                "Old",
                "Shelf",
                "Brink",
                "Crop",
                "Career",
                "End",
                "Cook",
                "Clue",
                "Sense",
                "Stage",
                "Sacred",
                "Ideal",
                "Flower",
                "Union",
                "Single",
                "Unfair"
            };
            break;
        case HASH_S4("3"):
        case HASH_S4("hard"):
            words = {
                "Journal", 
                "Intelligence", 
                "Insight", 
                "Manufacture",
                "Regulation",
                "Conception",
                "Concentration",
                "Evaluate",
                "Football",
                "Federation",
                "Interest",
                "Reflection",
                "Hallway",
                "Green",
                "Wilderness",
                "Complete",
                "Failure",
                "Disposition",
                "Yellow",
                "Conventional",
                "Explosion",
                "Handicap",
                "Overcharge",
                "Survivor",
                "Elaborate",
                "Legislature",
                "Calculation",
                "Knowledge",
                "Represent",
                "Dependence",
                "Publisher",
                "Content",
                "Biography",
                "Fluctuation",
                "Helpless",
                "Feather",
                "Credibility",
                "Insistence",
                "Relevance",
                "Display",
                "Detector",
                "Suggest",
                "Timetable",
                "Affinity",
                "Despise",
                "Legislation",
                "Publish",
                "Mechanism",
                "Squeeze"
            };
            break;
        case HASH_S4("9"):
        case HASH_S16("help"):
            help(2);
            cls();
            goto difficulties;
            break;
        case HASH_S4("0"):
        case HASH_S4("exit"):
            return 0;
            break;
        default:
            cout << "Invalid option.\n";
            goto difficulties;
    }

    cls();
    cout << "Unscramble the words!\n\n";

    int wordn;
    int points = 0;
    string word;
    string word_scrambled;
    string word_skip;

    gamebegin:

    // pick a random word and scramble it
    wordn = randint(0, words.size() - 1);
    word = words[wordn];
    word_scrambled = misc::scramblestr(word);

    // if the scrambler didn't scramble the word successfully, try again
    if (word == word_scrambled) {
        goto gamebegin;
    }

    cout << "Unscramble this: ";
    printc(word_scrambled, 'y');
    cout << "\nType ";
    printc("\"showword\" ", 'y');
    cout << "to show the scrambled word, type ";
    printc("\"skip\" ", 'y');
    cout << "to skip the word or type ";
    printc("\"exit\" ", 'y');
    cout << "to exit the game.\n";

    word_skip = word;
    while(true) {
        cin >> input;
        // put both the inputted and the unscrambled word into lowercase to make input non case sensitive
        input = misc::lower(input); 
        word = misc::lower(word);

        if (input == word) {
            if (mode == "classic") {
                printc("Correct! (+1 point)\n", 'g');
                points++;
            }
            else {
                printc("Correct!\n", 'g');
            }
            cout << "Moving on to the next word...\n";
            goto gamebegin;
        }
        else {
            switch(hashString(input.c_str())) {
                case HASH_S4("exit"):
                    if (mode == "classic") {
                        if (points == 1) {
                            cout << "You got "; printc("1", 'y'); cout << " point.\n";
                        }
                        else {
                            cout << "You got "; printc(std::to_string(points), 'y'); cout << " points.\n";
                        }
                        waitenter();
                    }
                    return 0;
                    break;
                case HASH_S4("skip"):
                    cout << "Skipping...\nThe answer was ";
                    printc(word_skip, 'y');
                    cout << ".\n";
                    if (mode == "classic" || points > 1) {
                        printc("-1 point.\n\n", 'r');
                        points--;
                    }
                    else {
                        cout << "\n";
                    }
                    goto gamebegin;
                    break;
                case HASH_S16("showword"):
                    cout << "The scrambled word is: ";
                    printc(word_scrambled, 'y');
                    cout << "\n";
                    break;
                // another easter egg :)
                case HASH_S16("climgftw"):
                    printc("You just found an easter egg!\n", 'g');
                    cout << "The answer is: ";
                    printc(word_skip, 'y');
                    cout << "\n";
                    break;
                default:
                    printc("Incorrect.\n", 'r');
                    if (mode == "classic") {
                        printc("Game over!\n", 'r');
                        cout << "You got "; printc(std::to_string(points), 'y'); cout << " points.\n";
                        waitenter();
                        return 0;
                        break;
                    }
        }
        }
    }

    return 1;
}