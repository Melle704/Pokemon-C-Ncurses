/*
 * Naam : Kas Visser
 * UvAnetID : 14625954
 * Studie : BSc Informatica
 *
 * header.h:
 * Dit bestand is de header file van het pokemon_uva.c main game bestand
 * Deze header maakt het mogelijk voor pokemon_uva.c om de functies
 * uit rooster_en_render.c te gebruiken.
 */

#ifndef _ROOSTER_H
#define _ROOSTER_H

#include <stdio.h>

// Struct van de rooster data voor de game map.
struct rooster_data;
typedef struct rooster_data rooster;

// Status van het spel.
typedef enum {
    BEGIN, AAN_HET_SPELEN, EINDE
} toestand;

// Maak een rooster op basis van het gegeven bestand.
rooster *rooster_lees(FILE *fh);

// Print de speler.
void speler(char *richting);

// Print een 16x16 object
void object16(int render_x, int render_y, char *filename);

// Render een huis.
void object_var(int render_x, int render_y, int breedte, char *filename);

// Render een volledig scherm van 128x128.
void render128(char *filename);

// Render elk kleuren character.
void render_kleur(int c);

// Sla een rooster op met de gegeven bestandsnaam in de subdirectory "assets".
void rooster_schrijf(const rooster *rp, FILE *fh);


// Vraag de huidige toestand van het spel op.
toestand rooster_vraag_toestand(const rooster *rp);


// Verander de huidige toestand van het spel.
void rooster_zet_toestand(rooster *rp, toestand t);


// Geef alle resources vrij die zijn gealloceerd voor een rooster.
void rooster_klaar(rooster *rp);


// Geef de breedte van het rooster, dat wil zeggen, het aantal kolommen.
int rooster_breedte(const rooster *rp);


// Geef de hoogte van het rooster, dat wil zeggen, het aantal rijen.
int rooster_hoogte(const rooster *rp);


// Kijk welk object er staat op een bepaalde positie in het rooster.
char rooster_kijk(const rooster *rp, int x, int y);


// Schrijf een bepaald object op een bepaalde positie in het rooster.
int rooster_plaats(rooster *rp, int x, int y, char c);


// Zoek een bepaald object in het rooster, en geef de coordinaten van het.
//  object terug via de gegeven pointers.
void rooster_zoek(const rooster *rp, char c, int *x, int *y);


#endif