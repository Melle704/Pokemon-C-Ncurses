#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

#include "menu.h"
#include "rooster.h"
#include "colors.h"

// Voer de toets uit in de menu functie.
int menu_toets(int toets, int positie) {
    // Bij pijltje naar benden tel je 1 bij positie op en vice versa.
    switch (toets) {
        case KEY_DOWN:  positie++; break;
        case KEY_UP:    positie--; break;
    }

    // Als de positie minder is dan 1 of meer dan 4, dan moet de positie
    // aan de andere kant weer terug loopen.
    if (positie < 1) {
        positie = 4;
    } else if (positie > 4) {
        positie = 1;
    }
    return positie;
}


// Render een menu op het scherm met verschillende opties.
void menu(void) {
    // Beginpositie en begin render positie van de cursor
    int positie = 1;
    int cursor_x = 46;
    int cursor_y = 49;

    // Laad de titlescreen zien en wacht op een input.
    render128("assets/main/titlescreen.txt");
    refresh();
    getch();

    // Display een zwart scherm voor 1 seconde voordat het menu word geladen.
    clear();
    refresh();
    sleep(1);

    while(1) {
        // Render het main startmenu.
        render128("assets/main/startmenu.txt");
        // Render de cursor op het startmenu.
        object_var(cursor_x, cursor_y, 5,"assets/main/cursor_grijs.txt");
        refresh();

        int toets = getch();

        // Als de input een enter is, kijk wat de huidige cursor positie is en
        // voer het daarbij horende commando uit.
        if (toets == '\n') {
            switch (positie) {
                case 1:     return;                           // Start het spel
                case 2:     game_color(1); kleuren(); break;    // kleuren
                case 3:     render128("assets/main/controls_1lijn.txt");
                            getch();
                            break;                            // Controls.
                case 4:     endwin(); delwin(stdscr); exit(0);// Exit het spel
            }
        }

        // Bepaal de nieuwe cursor posite aan de hand van de spelers input.
        if (toets == KEY_UP || toets == KEY_DOWN) {
            positie = menu_toets(toets, positie);
        }

        // Verander de cursor positie aan de hand van de nieuwe positie.
        switch (positie) {
            case 1: cursor_x = 46; cursor_y = 49; break;
            case 2: cursor_x = 46; cursor_y = 59; break;
            case 3: cursor_x = 46; cursor_y = 69; break;
            case 4: cursor_x = 46; cursor_y = 79; break;
        }
    }
}