#ifndef _RENDER_H
#define _RENDER_H

void speler(char *richting);

void object16(int render_x, int render_y, char *filename);

void object_var(int render_x, int render_y, int breedte, char *filename);

void render128(char *filename);

void render_tekst(char *str);

void render_kleur(int c);

#endif