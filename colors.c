#include <ncurses.h>

#include "colors.h"

int spelkleur = 1;

void game_color(int change) {
    spelkleur += change;
}

// Laad de gekozen spelkleuren en kleuren paren in.
void kleuren(void) {
    // Alle 'standaard kleuren paren. magenta is standaard licht grijs
    // en geel is donker grijs.
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(2, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(3, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(4, COLOR_WHITE, COLOR_WHITE);
    init_pair(5, COLOR_BLUE, COLOR_BLUE);
    init_pair(6, COLOR_RED, COLOR_RED);

    init_color(COLOR_BLUE, 0, 0, 900);
    init_color(COLOR_RED, 850, 0, 0);
    init_color(COLOR_WHITE, 999, 999, 999);

    // Laad de spelkleur weer terug lopen van 4 naar 1.
    if (spelkleur == 4) {
        spelkleur = 1;
    }

    // Alle verschillende kleuren paletten om uit te kiezen.
    switch (spelkleur) {
        case 1:
            init_color(COLOR_MAGENTA, 300, 300, 300);
            init_color(COLOR_YELLOW, 700, 700, 700);
            break;
        case 2:
            init_color(COLOR_MAGENTA, 920, 480, 600);
            init_color(COLOR_YELLOW, 460, 820, 860);
            break;
        case 3:
            init_color(COLOR_MAGENTA, 620, 820, 310);
            init_color(COLOR_YELLOW, 640, 820, 999);
            break;
    }
}