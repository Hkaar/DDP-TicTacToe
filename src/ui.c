#include <stdbool.h>
#include <stdio.h>

#include "utils.h"

void printLogo();
void gameMenu();
void settingsMenu();
void helpMenu();

void mainMenu() {
    bool running = true;
    int menu = 0;

    while (running) {
        printLogo();

        printf("\n[1] Play Game\n");
        printf("[2] Settings\n");
        printf("[3] Help\n");
        printf("[4] Quit\n\n");

        printf(">> ");
        scanf("%d", &menu);

        printf("%d\n", menu);

        fflush(stdin);

        switch (menu) {
        case 1:
            gameMenu();
            break;

        case 2:
            settingsMenu();
            break;
        
        case 3:
            helpMenu();
            break;

        case 4:
            running = false;
            break;

        default:
            printf("Menu code %d doesn't exist!", menu);
            break;
        }
    }
}

void gameMenu() {
    clear_console();
    printf("Game menu:\n");
    printf("Press [enter] to return...");
    getchar();
    fflush(stdin);
}

void settingsMenu() {
    clear_console();
    printf("Settings menu:\n");
    printf("Press [enter] to return...");
    getchar();
    fflush(stdin);
}

void helpMenu() {
    clear_console();
    printf("Help menu:\n");
    printf("Press [enter] to return...");
    getchar();
    fflush(stdin);
}

void printLogo() {
    printf("$$$$$$$$\\ $$\\        $$$$$$$$\\               $$$$$$$$\\         "
           "         \n");
    printf("\\__$$  __|\\_|       \\__$$  __|              \\__$$  __|         "
           "        \n");
    printf("   $$ |   $$\\  $$$$$$$\\ $$ | $$$$$$\\   $$$$$$$\\ $$ | $$$$$$\\  "
           " $$$$$$\\  \n");
    printf("   $$ |   $$ |$$  _____|$$ | \\____$$\\ $$  _____|$$ |$$  __$$\\ "
           "$$  __$$\\ \n");
    printf("   $$ |   $$ |$$ /      $$ | $$$$$$$ |$$ /      $$ |$$ /  $$ "
           "|$$$$$$$$ |\n");
    printf("   $$ |   $$ |$$ |      $$ |$$  __$$ |$$ |      $$ |$$ |  $$ |$$   "
           "____|\n");
    printf("   $$ |   $$ |\\$$$$$$$\\ $$ |\\$$$$$$$ |\\$$$$$$$\\ $$ |\\$$$$$$  "
           "|\\$$$$$$$\\ \n");
    printf("   \\__|   \\__| \\_______|\\_| \\_______| \\_______|\\__| "
           "\\______/  \\_______|\n");
}