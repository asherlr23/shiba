#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int init() {
    struct stat sb;

    if (stat("~/.local/share/aurHelper", &sb) == 0 && S_ISDIR(sb.st_mode)) {
        printf("if you are seeing this, c is being indecicive. try running me again maybe? \n");
    } else {
        printf("Looks like this is your first time using this. \n I'll setup some files that i need\n");

        system("mkdir ~/.local/share/aurHelper"); // Local directory for aurHelper
        system("mkdir ~/.local/share/aurHelper/packages/"); // This is where the packages will be stored
        system("touch ~/.local/share/aurHelper/config"); // Config file
        
        printf("Done!\n");
    }
    return 0;
}
int main(int argc, char *argv[]) {
    struct stat sb;

    if (stat("~/.local/share/aurHelper", &sb) == 0 && S_ISDIR(sb.st_mode)) {
        printf("aurPackages directory exists!\n");
    } else {
        init();
    }

    if (argv[1] == NULL) {
        printf("I dont have any arguments, i dont know what you want me to do!", argv[0]);
        exit(1);
    } else if (argv[1] == "help") {
            printf("Welcome to Shiba! This is an all-in-one package manager for Arch Linux.\n");

            printf("Usage: shiba [command] [package]\n");
            printf("Commands:\n");
            printf("help - Shows this message\n");
            printf("version - Shows the version of Shiba.\n");
            printf("install - Downloads and installs a package.\n");
            printf("download - Downloads a package without installing it. Usefull if you need custom build configs with makepkg.\n");
        exit(0);
    } else if (argv[1] == "version") {
        printf("I'm on version 0.1.0.\n");
        exit(0);
    } else if (argv[0] == "install") {
        if (argv[2] == NULL) {
            printf("I dont know what you want me to install!");
            exit(1);
        }

        printf("OK! I'll install %s for you!\n", argv[2]);

        if (access("~/.local/share/shiba", F_OK)) {
            printf("Looks like you already have %s installed! I'll just update it for you!\n", argv[2]);
            system("cd ~/.local/share/aurHelper/packages/%s && git pull");
            system("cd ~/.local/share/aurHelper/packages/%s && makepkg -si");

        } else {
            printf("Looks like you dont have %s installed! I'll install it for you!\n", argv[2]);

            if (argv[3] == NULL) {
                printf("Is the package in the AUR or github? You can also specify a URL to a git repo!");
                scanf("%s", argv[3]);

                if (argv[3] == "--aur") {
                    system("cd ~/.local/share/aurHelper/packages/ && git clone https://aur.archlinux.org/%s.git");
                    system("cd ~/.local/share/aurHelper/packages/%s && makepkg -si");
                } else if (argv[3] == "--github") {
                    system("cd ~/.local/share/aurHelper/packages/ && git clone %s");
                    system("cd ~/.local/share/aurHelper/packages/%s && makepkg -si");
                } else if (argv[3] == "--url") {
                    system("cd ~/.local/share/aurHelper/packages/ && git clone %s");
                    system("cd ~/.local/share/aurHelper/packages/%s && makepkg -si");
                } else {
                    printf("I dont know what %s is! You can specify a package from the AUR, github, or a git URL.", argv[3]);
                    exit(1);
                }
            }

            if (argv[3] == "--aur") {
                system("cd ~/.local/share/aurHelper/packages/ && git clone https://aur.archlinux.org/%s.git");
                system("cd ~/.local/share/aurHelper/packages/%s && makepkg -si");
            } else if (argv[3] == "--github") {
                system("cd ~/.local/share/aurHelper/packages/ && git clone https://github.com/%s.git");
                system("cd ~/.local/share/aurHelper/packages/%s && makepkg -si");
            } else if (argv[3] == "--url") {
                system("cd ~/.local/share/aurHelper/packages/ && git clone %s");
                system("cd ~/.local/share/aurHelper/packages/%s && makepkg -si");
            } else {
                printf("I dont know what %s is! You can specify a package from the AUR, github, or a git URL.", argv[3]);
                exit(1);
            }

        }



        printf("I dont know what you want me to do!");
        exit(1);
    }
}
