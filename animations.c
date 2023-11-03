// Nodig voor de nanosleep functie, Bron 'nanosleep(2) Linux manual page'
#define _POSIX_C_SOURCE 199309L

#include <ncurses.h>
#include <unistd.h>
#include <time.h>

#include "colors.h"
#include "rooster.h"

// Hoeveel nanoseconde een bepaalde struct is voor nanosleep().
struct timespec time2 = {
    .tv_sec = 0,
    .tv_nsec = 9999999,
};

struct timespec time3 = {
    .tv_sec = 0,
    .tv_nsec = 99999999,
};

// Top down animatie, die van lingsboven tot rechts onder alle sprites
// vervangt met zwarte vlakken.
void animatie_topdown() {
    // Render op alle plekken een zwart vlak, stuk voor stuk.
    for (int y = 0; y < 7; y++) {
        for (int x = 0; x < 11; x++) {
            object16(x*16, y*16, "assets/sprites/niks.txt");

            // Kleine delay voor het effect.
            nanosleep(&time2, NULL);
            refresh();
        }
    }
    // Refresh het ncurses scherm.
    refresh();
}


// Spiraal animatie, die naar binnen toe draait.
void animatie_spiral() {
    // Huidige x en y coorodinaat voor het renderen.
    int x = 0;
    int y = 0;
    // Huidige maximale waarde om te renderen.
    int x_max = 10;
    int y_max = 6;
    // Hudige minimale waarde om te renderen.
    int x_min = 0;
    int y_min = 1;

    for (int i = 0; i < 7; i++) {
        // Render lege objecten van linksboven naar rechtsboven.
        for (;x < x_max; x++) {
            object16(x*16, y*16, "assets/sprites/niks.txt");

            nanosleep(&time2, NULL);
            refresh();
        }
        // Render lege objecten van rechtsboven naar rechtsonder.
        for (;y < y_max; y++) {
            object16(x*16, y*16, "assets/sprites/niks.txt");

            nanosleep(&time2, NULL);
            refresh();
        }
        // Render lege objecten van rechtsonder naar linksonder.
        for (;x > x_min; x--) {
            object16(x*16, y*16, "assets/sprites/niks.txt");

            nanosleep(&time2, NULL);
            refresh();
        }
        // Render lege objecten van linksonder naar linksboven.
        for (;y > y_min; y--) {
            object16(x*16, y*16, "assets/sprites/niks.txt");

            nanosleep(&time2, NULL);
            refresh();
        }

        // Haal 1 van het huidige maximum af en tel 1 bij het minimum op,
        // waardoor de spriaal steeds kleiner word.
        x_max--;
        y_max--;
        x_min++;
        y_min++;
    }
    // Refresh het ncurses scherm.
    refresh();
}


// Gradient animatie, die langzaam de kleuren steeds donkerder maakt.
// (gebruikt tussen tp's)
void animatie_gradient() {
    nanosleep(&time3, NULL);

    // Print het hudige frame in een steeds donkere toon af.
    // Met een korte delay tussen elke verandering voor het effect.
    init_color(COLOR_MAGENTA, 0, 0, 0);
    init_color(COLOR_YELLOW, 300, 300, 300);
    init_color(COLOR_WHITE, 700, 700, 700);
    init_color(COLOR_BLUE, 0, 0, 400);
    init_color(COLOR_RED, 400, 0, 0);

    refresh();
    nanosleep(&time3, NULL);

    init_color(COLOR_YELLOW, 0, 0, 0);
    init_color(COLOR_WHITE, 300, 300, 300);
    init_color(COLOR_BLUE, 0, 0, 0);
    init_color(COLOR_RED, 0, 0, 0);

    refresh();
    nanosleep(&time3, NULL);

    init_color(COLOR_WHITE, 0, 0, 0);

    refresh();
    sleep(1);

    // Reset weer terug naar de gekozen kleuren.
    kleuren();
}
