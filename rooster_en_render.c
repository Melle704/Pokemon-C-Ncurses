/* rooster_en_render.c:
 * Dit bestand bestaat uit de hulp functies voor het rooster waar het spel op
 * is gebasseerd. Ondere andere het lezen van het rooster en alle informatie
 * om het rooster heen staan hier uitgewerkt.
 * Daarnaast is het ook verantwoordelijk voor het hele renderings systeem
 * gebruikt om een simpele grid van characters om te zetten in een wereld
 * bestaand uit sprites en textures.
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>

#include "rooster.h"

// Max grootte van een 'grid' bestand.
#define MAX_LINE 1000
#define MAX_COLUMN 1000


// De struct van het rooster, van de game map.
struct rooster_data {
   int toestand;
   int hoogte;
   int breedte;
   char grid[MAX_COLUMN][MAX_LINE];
};

typedef struct rooster_data rooster;


// Laad het rooster van de game map in, om te gebruiken voor het renderen
// en spelen van het spel.
rooster *rooster_lees(FILE *fh) {
   // Als de file niet bestaat, print: file not found.
   if (fh == NULL) {
      printf("file not found\n");
      return NULL;
   }

   // Zoek de lengte van een line en rewind het bestand.
   int lijn = 0;
   while (fgetc(fh) != '\n') {
      lijn++;
   }
   rewind(fh);

   // Zoek het einde van de file, bereken de grootte en rewind de file weer.
   fseek(fh, 0L, SEEK_END);
   long int grootte = ftell(fh);
   rewind(fh);

   // De hoogte = het oppervlak of grootte gedeeld door de lengte van een line.
   int kolom = grootte / lijn;

   // Allocate memory voor het rooster.
   rooster *rp = malloc(sizeof(rooster));

   // Definieer dimensies van het rooster.
   rp->hoogte = kolom;
   rp->breedte = lijn;

   // Zet line voor line alle chars in de grid.
   for (int y = 0; y < kolom; y++) {
      for (int x = 0; x < lijn; x++) {
         // Bij het einde van het programma worden beide loops gexit.
         if (feof(fh)) {
            y = kolom;
            break;
         }
         // Zet de huidige char in de grid.
         rp->grid[y][x] = fgetc(fh);
      }
   }

   // Sluit de file.
   fclose(fh);

   return rp;
}


// Render de speler op de huidige positie.
void speler(char *richting) {
   FILE *sp = fopen(richting, "r");

   int render_x = 80;
   int render_y = 48;

   // Print elke char in het object stuk voor stuk.
   for (int y = 0; y < 16; y++) {
      for (int x = 0; x < 16; x++) {
         // Beweeg naar de huidige render positie.
         move(render_y + y, render_x + x);

         // Bij het einde van het programma worden beide loops gexit.
         if (feof(sp)) {
            y = 16;
            break;
         }

         // Print het character in de juiste kleur.
         render_kleur((fgetc(sp)) + 1);
      }
   }
   fclose(sp);
   return;
}


// Print een 16x16 sprite, als visuele representatie.
void object16(int render_x, int render_y, char *filename) {
   FILE *ob = fopen(filename, "r");

   // Print elke char in het object stuk voor stuk.
   for (int y = 0; y < 17; y++) {
      for (int x = 0; x < 16; x++) {
         // Beweeg naar de huidige render positie.
         move(render_y + y, render_x + x);

         // Bij het einde van het programma worden beide loops gexit.
         if (feof(ob)) {
            y = 17;
            break;
         }

         // Print het character in de juiste kleur.
         render_kleur((fgetc(ob)) + 1);
      }
   }
   fclose(ob);
   return;
}

// Render een object met een meegegeven breedte.
void object_var(int render_x, int render_y, int breedte, char *filename) {
   FILE *var = fopen(filename, "r");

   // Print elke char in het object stuk voor stuk.
   for (int y = 0; y < 40; y++) {
      for (int x = 0; x < breedte; x++) {

         // Beweeg naar de huidige render positie.
         move(render_y + y, render_x + x);

         // Bij het einde van het programma worden beide loops gexit.
         if (feof(var)) {
            y = 81;
            break;
         }

         // Print het character in de juiste kleur.
         render_kleur((fgetc(var)) + 1);
      }
   }
   fclose(var);
   return;
}


// Print een fullscreen van 128x112.
void render128(char *filename) {
   FILE *re = fopen(filename, "r");

   // Print elke char in het object stuk voor stuk.
   for (int y = 0; y < 113; y++) {
      for (int x = 0; x < 128; x++) {
         move(y, x);

         // Bij het einde van het programma worden beide loops gexit.
         if (feof(re)) {
            y = 129;
            break;
         }

         // Print het character in de juiste kleur.
         render_kleur((fgetc(re)) + 1);
      }
   }
   fclose(re);
   return;
}


// Render elk character in de juiste kleur.
void render_kleur(int c) {
   int kleur = 0;

   // Switch nodig door de rode hoed en blauwe rugzak van de speler.
   switch (c) {
      case '1': kleur = 1; break;
      case '2': kleur = 2; break;
      case '3': kleur = 3; break;
      case '4': kleur = 4; break;
      case '6': kleur = 5; break;
      case '7': kleur = 6; break;
   }

   if (kleur != 0) {
      attron(A_INVIS);
      attron(COLOR_PAIR(kleur));
      addch(c);
      attron(COLOR_PAIR(kleur));
      attroff(A_INVIS);
   }

   return;
}


// Vraag de huidige toestand van het spel op.
toestand rooster_vraag_toestand(const rooster *rp) {
   return rp->toestand;
}


// Verander de huidige toestand van het spel.
void rooster_zet_toestand(rooster *rp, toestand t) {
   rp->toestand = t;
}


// Geef alle resources vrij die zijn gealloceerd voor een rooster.
void rooster_klaar(rooster *rp) {
   free(rp);
}


// Kijk welk object er staat op een bepaalde positie in het rooster.
char rooster_kijk(const rooster *rp, int x, int y) {
   // Als de x of y buiten het rooster valt, return dan een L (leeg vakje).
   if (x < 1 || y < 1 || x >= rp->breedte || y >= rp->hoogte) {
      return 'L';
   }

   // Anders: return die positie van de coordinaten in de grid als object.
   char c = rp->grid[y][x];
   return c;
}


// Schrijf een bepaald object op een bepaalde positie in het rooster.
int rooster_plaats(rooster *rp, int x, int y, char c) {
   // Anders zet die positie in de grid gelijk aan het object en return 1
   rp->grid[y][x] = c;
   return 1;
}
