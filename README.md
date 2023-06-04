# cli-mg
cli-mg is a set of minigames designed for play using the command line. <br>
The games are very light on system resources. <br>
## How do I play?
### Linux/BSD:
Install your favorite C++11 compatible compiler, then run `make install` as root (`sudo make install`, `doas make install`). Then you can launch the game by just typing `cli-mg` or selecting it from the application menu. <br>
Note: The Linux/BSD version may work on MacOS (untested). <br>
You can also uninstall it by running `make uninstall` as root (`sudo make uninstall`, `doas make uninstall`). <br>
### Termux:
Install `clang` and `make`, then run `make install-termux` Then you can launch the game by just typing `cli-mg` or selecting it from the application menu. <br>
You can also uninstall it by running `make uninstall-termux`. <br>
### Windows:
Run the executable corresponding to your CPU architecture. <br>
To uninstall, just delete the file. <br>
### Officially supported Windows releases
This program supports Windows XP or newer (Windows XP, Vista, 7, 8, 8.1, 10) officially. <br>
NOTE: If the executables are recompiled there may be issues with compatibility.
## Makefile docummentation
Makefile commands: `make compile, make compile-windows, make install, make   install-termux, make clean, make cleanall, make all, make uninstall, make uninstall-termux` <br>
Note: just running `make` does the same thing as `make compile`.
## Tips and tricks
Want to use command arguments to select the game? Well, you can! <br>
Syntax: `cli-mg *game name*` <br>
Available game and command names: rps (Rock, Paper, Scissors), dice (Dice roll), guessnum (Guess the number game), unscramble (unscramble the words game), license (shows the license) <br>
## Credits
Erik Jakin for adapting my program to the `statichash.h` header. <br>
Lukas S. van der Heeden and Erik Jakin for making the `statichash.h` header. <br>
