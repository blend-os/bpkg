#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ostream>
#include "statichash.h"
#include "misclib.hpp"

using std::cout;
using std::string;
using misc::printc;

string version = "0.1.0";

int pkgcheck(string pkgname) {
    // package availability check
    // PACKAGE MANAGER IDs: 0 - none, 1 - system pacman, 2 - pacman container, 3 - apt container, 4 - dnf container
    // CONFIG FILE LETTER IDs: s - system pacman, p - pacman container, a - apt container, d - dnf container
    int exitcode;
    string command, confstr;

    // open config file to find out package manager priority
    std::ifstream conf("/etc/bpkg.conf");
    std::getline(conf, confstr);
    conf.close();

    if (confstr.length() < 4) {
        printc("WARNING: The \"/etc/bpkg.conf\" config file does not exist. Using \"psad\" configuration.\n", 'y');
        confstr = "psad";
    }
    // world's worst text parser incoming
    for (int i = 0; i < 4; i++) {
        switch (confstr[i]) {
            case 's':
                // system pacman
                command = "pacman -Si " + pkgname + " >/dev/null 2>/dev/null";
                exitcode = system(command.c_str());
                if (exitcode == 0) {
                    return 1;
                }
                break;
            case 'p':
                // pacman container
                command = "pacman.arch -Si " + pkgname + " >/dev/null 2>/dev/null";
                exitcode = system(command.c_str());
                if (exitcode == 0) {
                    return 2;
                }
                break;
            case 'a':
                // apt container
                command = "apt.ubuntu show " + pkgname + " >/dev/null 2>/dev/null";
                exitcode = system(command.c_str());
                if (exitcode == 0) {
                    return 3;
                }
                break;
            case 'd':
                // dnf container
                command = "dnf.fedora info " + pkgname + " >/dev/null 2>/dev/null";
                exitcode = system(command.c_str());
                if (exitcode == 0) {
                    return 4;
                }
                break;
            default:
                printc("ERROR: bpkg internal error.\n", 'r');
                exit(-1);
                break;
        }
    } 
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) { // check for argument count
        printc("ERROR: Not enough arguments.", 'r');
        cout << "\n";
        return -1;
    }

    std::ofstream log("/var/bpkg.log");
    string pkgstring;

    switch (hashString(argv[1])) {
        case HASH_S16("install"):
            switch (pkgcheck(string(argv[2]))) {
                case 0:
                    printc("ERROR: Package not found.", 'r');
                    cout << "\n";
                    return 1;
                    break;
                case 1:
                    pkgstring = "pacman -S " + string(argv[2]);
                    system(pkgstring.c_str());
                    break;
                case 2:
                    pkgstring = "pacman.arch -S " + string(argv[2]);
                    system(pkgstring.c_str());
                    break;
                case 3:
                    pkgstring = "apt.ubuntu install " + string(argv[2]);
                    system(pkgstring.c_str());
                    break;
                case 4:
                    pkgstring = "dnf.fedora install " + string(argv[2]);
                    system(pkgstring.c_str());
                    break;
                default:
                    printc("ERROR: Package availability check returned an invalid value.\n", 'r');
                    return 2;
                    break;
            }
            break;
        case HASH_S16("upgrade"):
            log << "BPKG LOG FILE\nCommand: upgrade\n\nNOTE: The package manager update logs may look a bit messed up in text editors like nano becauee of ANSI escape sequences. In that case use cat to read the logs instead.\nPACKAGE MANAGER UPDATE LOGS:\n";
            log.close();
            printc("WARNING: This feature is experimental. I am not responsible for any damages (read license file for more information)!\n", 'y');
            cout << "Upgrading system pacman..." << std::flush;
            system("pacman -Syu --noconfirm >> /var/bpkg.log");
            cout << "done.\nUpgrading pacman container..." << std::flush;
            log << "\nARCH CONTAINER UPDATING:\n";
            system("pacman.arch -Syu --noconfirm >> /var/bpkg.log");
            cout << "done.\nUpgrading apt container..." << std::flush;
            log << "\nAPT CONTAINER UPDATING:\n";
            system("apt-get.ubuntu update >> /var/bpkg.log");
            system("apt-get.ubuntu upgrade -y >> /var/bpkg.log");
            cout << "done.\nUpgrading dnf container..." << std::flush;
            log << "\nFEDORA CONTAINER UPDATING:\n";
            system("dnf.fedora upgrade -y --refresh >> /var/bpkg.log");
            cout << "done.\nUpdate logs available in \"/var/bpkg.log\".\n";
            
            break;
        case HASH_S16("search"):
            cout << "pacman search results:\n";
            pkgstring = "pacman -Ss " + string(argv[2]);
            system(pkgstring.c_str());

            cout << "apt search results:\n";
            pkgstring = "apt search " + string(argv[2]);
            system(pkgstring.c_str());

            cout << "dnf search results:\n";
            pkgstring = "dnf search " + string(argv[2]);
            system(pkgstring.c_str());
            break;
        case HASH_S16("about"):
            cout << "bpkg v" << version << " by SvGaming\n"
            << "Git repository: https://fossfor.serveo.net/SvGaming/bpkg\n";
            break;
    }
    
    return 0;
}
