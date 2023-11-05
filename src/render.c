#define _POSIX_C_SOURCE 199309L
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include "render.h"

// Sleep struct voor tijd tussen letters printen.
struct timespec tekst = {
    .tv_sec = 0,
    .tv_nsec = 30000000,
};

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

         // Print alleen de character als het een juiste code is.
         int pixel = fgetc(sp);
         if (pixel > 13) {
             render_kleur(pixel + 1);
         } else {
            x--;
         }
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

         // Print alleen de character als het een juiste code is.
         int pixel = fgetc(ob);
         if (pixel > 13) {
             render_kleur(pixel + 1);
         } else {
            x--;
         }
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

         // Print alleen de character als het een juiste code is.
         int pixel = fgetc(var);
         if (pixel > 13) {
             render_kleur(pixel + 1);
         } else {
            x--;
         }
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

         // Print alleen de character als het een juiste code is.
         int pixel = fgetc(re);
         if (pixel > 13) {
             render_kleur(pixel + 1);
         } else {
            x--;
         }
      }
   }
   fclose(re);
   return;
}


// Render een tekstbox met de gegeven string in ascii.
void render_tekst(char *str) {
   // Correctie is nodig zodat het de correcte render positie kan bijhouden.
   int correctie = 0;
   for (size_t i = 0; i < strlen(str)+correctie;) {
      // Render de tekst box zonder letters.
      object_var(0, 75, 176, "assets/tekst/tekstbox.txt");

      int render_x = 9;
      int render_y = 84;

      // Elke tekstbox is maximaal 52 characters.
      for (;i < strlen(str)+correctie; i++, render_x += 6) {

         // Automatic wrapping voor woorden in de tekstbox.
         if (str[i-correctie] >= 'a' && i > 0) {
            // Bereken de laatste character van een woord.
            int i2;
            for (i2 = i; str[i2] != ' ' && str[i2] != '\0'; i2++);

            int laatste;
            // Check of het laatste character niet buiten de tekst zit.
            if (render_x + ((i2 - i - correctie) * 6) > 162) {
               if (render_y == 84) {
                  render_x = 9;
                  render_y = 95;
                  laatste = i2;
               } else if (laatste != i2) {
                  break;
               }
            }
         }

         // Handel speciale characters af.
         char file[20];
         switch (str[i-correctie]) {
            case '.': strcpy(file, "dot");         break;
            case ',': strcpy(file, "comma");       break;
            case ' ': strcpy(file, "space");       break;
            case '?': strcpy(file, "question");    break;
            case '!': strcpy(file, "exclemation"); break;
            default:
               snprintf(file, sizeof(file), "%c", tolower(str[i-correctie]));
               break;
         }

         // Print de character in de string uit.
         char filename[50];
         snprintf(filename, sizeof(filename), "assets/tekst/%s%s", file, ".txt");
         object_var(render_x, render_y, 5, filename);

         nanosleep(&tekst, NULL);
         refresh();
      }
      correctie++;
      i++;
      getch();
   }
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
