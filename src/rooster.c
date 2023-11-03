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
