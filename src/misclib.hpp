#ifndef MISCLIB_HPP
#define MISCLIB_HPP

#include <iostream>
#include <ostream>
#include <random>
#include <algorithm>

namespace misc {

#ifdef _WIN32

#include <windows.h>

inline int getrow() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int row;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    row = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return row;
}

inline int getcol() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int col;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    col = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    return col;
}

inline void cls() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD coordScreen = {0, 0};    // home for the cursor
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    // Get the number of character cells in the current buffer.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return;
    }

    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire screen with blanks.
    if (!FillConsoleOutputCharacter(hConsole,        // Handle to console screen buffer
                                    (TCHAR)' ',      // Character to write to the buffer
                                    dwConSize,       // Number of cells to write
                                    coordScreen,     // Coordinates of first cell
                                    &cCharsWritten)) // Receive number of characters written
    {
        return;
    }

    // Get the current text attribute.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return;
    }

    // Set the buffer's attributes accordingly.
    if (!FillConsoleOutputAttribute(hConsole,         // Handle to console screen buffer
                                    csbi.wAttributes, // Character attributes to use
                                    dwConSize,        // Number of cells to set attribute
                                    coordScreen,      // Coordinates of first cell
                                    &cCharsWritten))  // Receive number of characters written
    {
        return;
    }

    // Put the cursor at its home coordinates.
    SetConsoleCursorPosition(hConsole, coordScreen);
}

inline void printc(std::string line, char color = 'w') {
    // uses the windows api for color in the terminal
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int col;

    switch(color) {
        // blue
        case 'b': 
            col = 1;
            break;
        // green
        case 'g': 
            col = 2;
            break;
        // cyan
        case 'c':
            col = 3; 
            break;
        // red
        case 'r':
            col = 4;
            break;
        // magenta
        case 'm':
            col = 5;
            break;
        // yellow
        case 'y':
            col = 6;
            break;
        // white
        default:
            col = 7;
            break;
    }

    SetConsoleTextAttribute(hConsole, col);
    std::cout << line;
    SetConsoleTextAttribute(hConsole, 7);
}

#else

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

inline int getrow() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    return w.ws_row;
}

inline int getcol() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    return w.ws_col;
}

inline void cls() {
    std::cout << "\e[1;1H\e[2J"; // regular expression that clears the screen on unix and unix-like systems
}

inline void printc(std::string str, char color = 'w') {
    // uses ansi escape codes for color in the terminal
    std::string col;

    switch(color) {
        // blue
        case 'b':
            col = "\033[0;34m";
            break;
        // green
        case 'g':
            col = "\033[0;32m";
            break;
        // cyan
        case 'c':
            col = "\033[0;36m";
            break;
        case 'r':
        // red
            col = "\033[0;31m";
            break;
        // magenta
        case 'm':
            col = "\033[0;35m";
            break;
        // yellow
        case 'y':
            col = "\033[0;33m";
            break;
        // white
        default:
            col = "\033[0m";
            break;
    }

    std::cout << col << str << "\033[0m";
}

#endif

inline void pass() {}

inline void waitenter() {
    std::cout << "Press Enter to continue.\n";
    std::cin.ignore();
    std::cin.get();
}

inline int randint(int from, int to) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(from,to);
    int rngResult = dist6(rng);
    return rngResult;
}

inline std::string scramblestr(std::string str) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(str.begin(), str.end(), g);
    return str;
}

inline std::string upper(std::string str) {
    int length = str.length();
    for (int i = 0; i < length; i++) {
        int c = str[i];
        str[i] = toupper(c);  
    }
    return str;
}

inline std::string lower(std::string str) {
    int length = str.length();
    for (int i = 0; i < length; i++) {
        int c = str[i];
        str[i] = tolower(c);  
    }
    return str;
}

}

#endif