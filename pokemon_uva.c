/* pokemon_uva.c:
 * Een pokemon gen1 'inspired' game, waarin je eerst een starter pokemon kiest
 * bij professor Oak, waarna je toegang krijgt tot een 'route', waar je doel is
 * zoveel mogelijk pokemons te defeaten. Na zelf te zijn gedefeat krijg je je
 * score te zien. Probeer een zo hoog mogelijke score te halen!
 */

// Nodig voor de nanosleep functie, Bron 'nanosleep(2) Linux manual page'
#define _POSIX_C_SOURCE 199309L

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

#include "rooster.h"
#include "render.h"
#include "menu.h"
#include "colors.h"
#include "animations.h"
#include "sprites.h"


// Huidige player positie in het level.
int pos_x;
int pos_y;

// De spelers huidige pokemons health.
int player_health = 20;

// Originele health van de spelers pokemon.
int originele_player_health = 20;

// De huidige score van de speler.
int score = 0;

// Starter pokemon gekozen door de speler
int starter_pokemon = 0;

// Hoeveel nanoseconde een bepaalde struct is voor nanosleep().
struct timespec time22 = {
    .tv_sec = 0,
    .tv_nsec = 9999999,
};

// Alle pokemons data opgeslagen in een struct.
struct pokemon {
    int health;
    int attack;
    int breedte;
    char* filename;
};

// Struct array van alle pokemons in de game.
struct pokemon pokemon_array[6] = {
    {10, 10, 33, "assets/pokemons/pidgey33_1lijn.txt"},
    {20, 5, 25,  "assets/pokemons/weedle25_1lijn.txt"},
    {20, 5, 38, "assets/pokemons/diglet38_1lijn.txt"},
    {20, 5, 28, "assets/pokemons/charmander_achter_1lijn.txt"},
    {20, 5, 28, "assets/pokemons/bulbasaur_achter_1lijn.txt"},
    {20, 5, 28, "assets/pokemons/squirtle_achter_1lijn.txt"},
};

// Initialiseer ncurses en de kleuren van het spel.
void initialiseer() {
    // Initialiseer ncurses
    initscr();
    cbreak();             // zodat je kunt onderbreken met Ctrl+C
    keypad(stdscr, TRUE); // luister ook naar extra toetsen zoals pijltjes
    noecho();             // druk niet de letters af die je intypt
    curs_set(0);          // maakt de cursor onzichtbaar.

    // Print een korte 'no color' wanneer de terminal geen kleuren heeft.
    if (!has_colors()) {
        printw("Your terminal doesn't support color. Please restart.\n");
        refresh();
        sleep(2);
        exit(1);
    }

    // Laad de kleuren en palette in.
    kleuren();
}


// Toon het gegeven rooster van sprites wat meebeweegd met de player (ncursus).
void toon_rooster(rooster *rp, int richting) {
    erase();

    // Zet het begin van de renderpositie op 0, 0.
    int render_x = 0;
    int render_y = 0;

    // Ga door alle objecten in de grid, om ze te printen.
    for (int y = pos_y-3; y < pos_y+4; y++) {
        for (int x = pos_x-5; x < pos_x+6; x++) {

            // Begin met renderen van een nieuw object op de nieuwe render pos.
            move(render_y, render_x);

            // Render de 16x16 sprite behorend bij dit object in de grid.
            object16(render_x, render_y, sprites[rooster_kijk(rp, x, y)]);

            if (render_x == 80 && render_y == 48) {
                // Render speler in de juiste richting, op de vaste locatie.
                switch (richting) {
                    case 1: speler("assets/speler/speler_up.txt"); break;
                    case 2: speler("assets/speler/speler_down.txt"); break;
                    case 3: speler("assets/speler/speler_left.txt"); break;
                    case 4: speler("assets/speler/speler_right.txt"); break;
                }
            }
            // Schuif 16 x naar rechts voor de goede startpositie van
            // het volgende object.
            render_x += 16;
        }
        // Begin weer vooraan met printen en schuif 16 y naar beneden.
        render_x = 0;
        render_y += 16;
    }
    // Wacht even en zorg dat het scherm ook echt getoond wordt
    nanosleep(&time22, NULL);
    refresh();
}


// Render de cursor in de battle op de juiste plek.
void battle_cursor(int cursor_pos) {
    // Render de cursor op de juiste plek aan de hand van de cursor positie.
    if (cursor_pos == 0) {
        object_var(14, 83, 5, "assets/main/cursor_wit_1lijn.txt");
        object_var(14, 94, 5, "assets/sprites/wit_1lijn.txt");
    } else {
        object_var(14, 94, 5, "assets/main/cursor_wit_1lijn.txt");
        object_var(14, 80, 5, "assets/sprites/wit_1lijn.txt");
    }
}


// Render de battle healthbars van de speler en tegenstander.
void battle_healthbars(int originele_health, int tegenstander_health) {
    // Render de dynamische health bar van de tegenstander.
    for (int i = 0; i < 36; i++) {
        if (i < ((tegenstander_health * 36) / originele_health)) {
            if (10 > ((tegenstander_health * 36) / originele_health)) {
                object_var(24+i, 14, 1, "assets/battle/hp2_1lijn.txt");
            } else {
                object_var(24+i, 14, 1, "assets/battle/hp1_1lijn.txt");
            }
        } else {
            object_var(24+i, 14, 1, "assets/battle/hp0_1lijn.txt");
        }
    }


    // Render de dynamische health bar van de speler.
     for (int i = 0; i < 36; i++) {
        if (i < ((player_health * 36) / originele_player_health)) {
            if (10 > ((player_health * 36) / originele_player_health)) {
                object_var(83+i, 56, 1, "assets/battle/hp2_1lijn.txt");
            } else {
                object_var(83+i, 56, 1, "assets/battle/hp1_1lijn.txt");
            }
        } else {
            object_var(83+i, 56, 1, "assets/battle/hp0_1lijn.txt");
        }
    }
}


// Speel de beurt van de tegenstander in de battle.
void beurt_tegen(int tegenstander_health,
int tegenstander_attack,int originele_health) {
    // Bepaal 'random' wat de volgende zet van de tegenstander is.
    if (rand() % 2 == 1) {
        object_var(1, 74, 126, "assets/battle/tackle_enemy_1lijn.txt");
        player_health -= tegenstander_attack;
        if (player_health < 0) {
            player_health = 0;
        }
    } else {
        object_var(1, 74, 126, "assets/battle/leer_enemy_1lijn.txt");
    }

    // Render de health bar van de speler en tegenstander.
    battle_healthbars(originele_health, tegenstander_health);

    refresh();
    sleep(2);
}


// Einde van de battle, wanneer de speler of tegenstander defeated is.
void battle_end(void) {
    // Check wie er defeated is.
    if (player_health < 1) {
        object_var(1, 74, 126, "assets/main/player_defeated_1lijn.txt");
        object_var(12, 38, 38, "assets/pokemons/wit_1lijn.txt");
    } else {
        object_var(1, 74, 126, "assets/main/enemy_defeated_1lijn.txt");
        object_var(85, 10, 38, "assets/pokemons/wit_1lijn.txt");
    }

    // Refresh en sluit de battle met een gradient animatie.
    refresh();
    sleep(2);

    animatie_gradient();
    clear();
}


// 'Turn based combat' mechaniek van het spel.
void battle(void) {
    // Breedte en string pointer van de sprite, samen met de hp en attack van
    // de tegenstander.
    int tegenstander_health;

    // Genereer eem 'random' tegenstander, uit een groep van 3 pokemons.
    time_t t;
    srand((unsigned) time(&t));
    int c = rand() % 3;
    // Laad de goede waarde in voor de tegenstanders health.
    tegenstander_health = pokemon_array[c].health;

    // Health multiplier voor de rendering van de tegenstanders health bar.
    int originele_health = pokemon_array[c].health;

    // Zet de startpositie van de cursor op 0.
    int cursor_pos = 0;

    // Display een zwart scherm voor 1 seconde, voor effect.
    clear();
    sleep(1);

    // Main battle loopt zolang speler en tegenstander > 0 health hebben.
    while (player_health > 0 && pokemon_array[c].health > 0) {
        // Render het main battle scherm met alle standaard objecten erop.
        render128("assets/main/battle_1lijn.txt");
        // Render de spelers pokemon
        object_var(12, 50, 28, pokemon_array[starter_pokemon+2].filename);
        // Render de enemy pokemon
        object_var(85, 10,pokemon_array[c].breedte, pokemon_array[c].filename);
        // Render de health bar van de speler en tegenstander.
        battle_healthbars(originele_health, tegenstander_health);
        // Render de cursor op de juiste plek.
        battle_cursor(cursor_pos);
        refresh();

        // Loop voor de beurt van de speler.
        while(1) {
            // Clear the inputs buffer.
            flushinp();

            int input = getch();
            // Bij een 'enter' input, voer de gekozen attack uit voor de
            // huidige cursor positie uit.
            if (input == '\n') {
                // Voer de gekozen attack uit door de speler.
                if (cursor_pos == 0) {
                    // Voer de spelers attack uit
                    object_var(1, 74, 126, "assets/battle/tackle_player.txt");
                    tegenstander_health -= pokemon_array[starter_pokemon+2].attack;
                    if (tegenstander_health < 0) {
                        tegenstander_health = 0;
                    }
                } else {
                    // Doe 'leer', dus geen damage.
                    object_var(1, 74, 126, "assets/battle/leer_player.txt");
                }

                // Render de health bar van de speler en tegenstander en wacht 2 seconde.
                battle_healthbars(originele_health, tegenstander_health);

                refresh();
                sleep(2);
                break;

            // Bij de key up of down inverseer cursor pos.
            } else if (input == KEY_UP || input == KEY_DOWN) {
                cursor_pos = 1 - cursor_pos;
            }

            // Render de cursor opnieuw op de juiste plek.
            battle_cursor(cursor_pos);
            refresh();
        }
        // Als de speler de tegenstander heeft gedefeat, laat de tegenstander
        // dan niet nog een turn doen.
        if (tegenstander_health < 1) {
            break;
        }
        // Speel de beurt van de tegenstander.
        beurt_tegen(tegenstander_health, pokemon_array[c].attack, originele_health);
    }
    // Einde van de battle, wanneer de speler of tegenstander defeated is.
    battle_end();
}


// Functie om een interactie tussen de speler en het object voor zich
// uit te voeren.
void interactie(rooster *rp, int richting) {
    char c;
    // Bepaal het object waarmee word geinteracteerd gebasseerd op de richting
    switch (richting) {
        case 1:   c = rooster_kijk(rp, pos_x, pos_y-1); break;
        case 2:   c = rooster_kijk(rp, pos_x, pos_y+1); break;
        case 3:   c = rooster_kijk(rp, pos_x-1, pos_y); break;
        case 4:   c = rooster_kijk(rp, pos_x+1, pos_y); break;
    }

    // Zolang er nog geen starter is gekozen, mag de speler er 1 kiezen en zijn
    // er bepaalde interacties mogelijk.
    if (starter_pokemon == 0) {
        switch (c) {
            case 'a':
                starter_pokemon = 1; rooster_plaats(rp, 50, 26, '>'); break;
            case 'b':
                starter_pokemon = 2; rooster_plaats(rp, 51, 26, '>'); break;
            case 'c':
                starter_pokemon = 3; rooster_plaats(rp, 52, 26, '>'); break;
            case '+':
                object_var(25, 72, 126,"assets/main/choose_starter_1lijn.txt");
                refresh(); getch(); break;
            case ':':
                object_var(25, 72, 126, "assets/main/goto_professor_oak.txt");
                refresh(); getch(); break;
        }
        // Als je een starter hebt gekozen, dan kan je verder naar de route.
        if (starter_pokemon != 0) {
            rooster_plaats(rp, 14, 25, ' ');
            rooster_plaats(rp, 15, 25, ' ');
        }
    }
}


// Voert de benodigde veranderingen in het rooster door als de speler beweegt.
int beweeg(rooster *rp, int dx, int dy, int richting) {
    // Kijk in het rooster naar welk object er op die positie staat
    // en wat er daarna moet gebeuren.
    // Break bij een non-solid, positie en richting bij een tp, toestanden.
    char c = rooster_kijk(rp, pos_x + dx, pos_y + dy);

    // Als het een laag muurtje is kan je er aan 1 kant overheen springen.
    if (c == '_' && richting == 2) {
        pos_y += dy + 1;
        pos_x = pos_x + dx;
        return 2;
    }

    // Voer een actie uit aan de hand van waar de speler op beweegt.
    // Break voor non solid objecten, animatie voor een deur en w en ; zijn
    // informatieve tekst boxen.
    switch (c) {
        case ' ':   break;
        case 'S':   break;
        case 'n':   break;
        case 'G':   break;
        case 'V':   break;
        case '>':   break;
        case 'J':   break;
        case '=':   break;
        case 'T':   animatie_gradient(); pos_x = 53; pos_y = 35; return 3;
        case '-':   animatie_gradient(); pos_x = 10; pos_y = 32; return 2;
        case '<':   animatie_gradient(); pos_x = 18; pos_y = 37; return 2;
        case 'K':   animatie_gradient(); pos_x = 41; pos_y = 36; return 2;
        case 'j':   animatie_gradient(); pos_x = 50; pos_y = 40; return 1;
        case 'q':   animatie_gradient(); pos_x = 47; pos_y = 30; return 1;
        case 'w':   object_var(25, 72, 126, "assets/main/door_locked.txt");
                    refresh(); getch(); return richting;
        case ';':   object_var(25, 72, 126, "assets/main/starter_first.txt");
                    refresh(); getch(); return richting;
        default:    return richting;
    }

    // Maak de nieuwe positie de huidige positie.
    pos_x = pos_x + dx;
    pos_y = pos_y + dy;

    return richting;
}


// Speelt het spel met een gegeven rooster tot de toestand niet langer
// AAN_HET_SPELEN is.
void speel(rooster *rp) {
    int richting = 2;
    while (rooster_vraag_toestand(rp) == AAN_HET_SPELEN) {
        int rel_x = 0;
        int rel_y = 0;

        // Wissel elke movement van water texture, wat op een animatie lijkt.
        if ((pos_x+pos_y) % 2 == 1) {
            sprites['W'] = "assets/sprites/water/water_1lijn.txt";
        } else {
            sprites['W'] = "assets/sprites/water/water2_1lijn.txt";
        }

        // Render het huidige frame.
        toon_rooster(rp, richting);

        // Als de speler op hoog gras staat en een random nummer delbaar is
        // door 6, dan komt de speler een pokemon tegen.
        if (rooster_kijk(rp, pos_x, pos_y) == 'S' && rand() % 6 == 0) {

            // Random kans op 1 van de 2 animaties.
            if (rand() % 2 == 0) {
                animatie_topdown();
            } else {
                animatie_spiral();
            }

            battle();
            // Als de speler geen health meer heeft is het spel over.
            if (player_health < 1) {
                rooster_zet_toestand(rp, EINDE);
                return;
            } else {
                score++;
                toon_rooster(rp, richting);
            }
        }

        flushinp();

        // Vraag een karakter, om daarna de relatieve positie te bepalen.
        int toets = getch();
        switch (toets) {
            case KEY_UP:    rel_y--; richting = 1; break;
            case KEY_DOWN:  rel_y++; richting = 2; break;
            case KEY_LEFT:  rel_x--; richting = 3; break;
            case KEY_RIGHT: rel_x++; richting = 4; break;
            case '\n':      interactie(rp, richting); continue;
            default:        continue;
        }
        // Voer de beweging uit, behorend bij de toets.
        richting = beweeg(rp, rel_x, rel_y, richting);
    }
}


// Het einde van het spel, met je score van hoeveel pokemons je hebt gebeat
void einde(void) {
    // Clear het huidige scherm en render de endscreen met score.
    clear();
    sleep(1);
    render128("assets/main/endscreen_1lijn.txt");
    object_var(5, 5, 28, "assets/main/score.txt");

    // Render de juiste score van de speler.
    switch (score) {
        case 0: object_var(35, 5, 5, "assets/main/0.txt"); break;
        case 1: object_var(35, 5, 5, "assets/main/1.txt"); break;
        case 2: object_var(35, 5, 5, "assets/main/2.txt"); break;
        case 3: object_var(35, 5, 5, "assets/main/3.txt"); break;
        case 4: object_var(35, 5, 5, "assets/main/4.txt"); break;
        case 5: object_var(35, 5, 5, "assets/main/5.txt"); break;
        case 6: object_var(35, 5, 5, "assets/main/6.txt"); break;
        case 7: object_var(35, 5, 5, "assets/main/7.txt"); break;
        case 8: object_var(35, 5, 5, "assets/main/8.txt"); break;
        case 9: object_var(35, 5, 5, "assets/main/9.txt"); break;
    }

    // Clear de input buffer.
    flushinp();

    refresh();
    getch();
    getch();
}


int main(void) {
    // Opent de file en zet het in de pointer.
    FILE *fh = fopen("assets/main/game_map.txt", "r");
    rooster *rp = rooster_lees(fh);

    // Start positie van de speler.
    pos_x = 37;
    pos_y = 37;

    // Initialiseer het scherm en kleuren.
    initialiseer();

    // Laad alle sprites in een char pointer array.
    sprite_array();

    // Start menu.
    menu();

    // Zet de toestand op aan het spelen en start het spel.
    rooster_zet_toestand(rp, AAN_HET_SPELEN);
    speel(rp);

    // Het einde van het spel, met je score van hoeveel pokemons je hebt gebeat
    einde();

    // Verwijder het rooster uit de memory.
    rooster_klaar(rp);

    // Sluit ncurses af
    endwin();
    delwin(stdscr);

    return 0;
}
