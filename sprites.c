#include "sprites.h"

// Globale character pointer array van alle sprites.
char *sprites[128];

// Laad alle sprites in de char pointer array.
void sprite_array(void) {
    // Simpele pokemon sprites.
    sprites['a'] = "assets/pokemons/charmander_1lijn.txt";
    sprites['b'] = "assets/pokemons/bulbasaur_1lijn.txt";
    sprites['c'] = "assets/pokemons/squirtle_1lijn.txt";

    // Alle standaard 16x16 buiten sprites
    sprites['X'] = "assets/sprites/valstrik_1lijn.txt";
    sprites['#'] = "assets/sprites/steen_1lijn.txt";
    sprites[' '] = "assets/sprites/ondergrond_1lijn.txt";
    sprites[';'] = "assets/sprites/ondergrond2_1lijn.txt";
    sprites['G'] = "assets/sprites/gras_1lijn.txt";
    sprites['L'] = "assets/sprites/niks_1lijn.txt";
    sprites['S'] = "assets/sprites/bosje_1lijn.txt";
    sprites['W'] = "assets/sprites/water2_1lijn.txt";
    sprites['_'] = "assets/sprites/springmuur_1lijn.txt";
    sprites['-'] = "assets/sprites/niks_tp_1lijn.txt";
    sprites['<'] = "assets/sprites/niks_tp_1lijn.txt";

    // Alle water gerelateerde sprites
    sprites['W'] = "assets/sprites/water/water2_1lijn.txt";
    sprites['!'] = "assets/sprites/water/waterkant_boven_1lijn.txt";
    sprites['@'] = "assets/sprites/water/waterkant_links_1lijn.txt";
    sprites['^'] = "assets/sprites/water/waterkant_rechts_1lijn.txt";
    sprites['&'] = "assets/sprites/water/waterkant_linksehoek_1lijn.txt";
    sprites['%'] = "assets/sprites/water/waterkant_rechtsehoek_1lijn.txt";

    // Alle 16x16 sprites binnen gebouwen.
    sprites['V'] = "assets/sprites/binnenhuis/vloer_1lijn.txt";
    sprites['>'] = "assets/sprites/binnenhuis/vloer_oak_1lijn.txt";
    sprites['M'] = "assets/sprites/binnenhuis/muur_1lijn.txt";
    sprites['R'] = "assets/sprites/binnenhuis/raam_1lijn.txt";
    sprites['T'] = "assets/sprites/binnenhuis/trap_1lijn.txt";
    sprites['E'] = "assets/sprites/binnenhuis/tv_1lijn.txt";
    sprites['H'] = "assets/sprites/binnenhuis/bed1_1lijn.txt";
    sprites['I'] = "assets/sprites/binnenhuis/bed2_1lijn.txt";
    sprites['N'] = "assets/sprites/binnenhuis/nes_1lijn.txt";
    sprites['J'] = "assets/sprites/binnenhuis/deurmat_1lijn.txt";
    sprites['K'] = "assets/sprites/binnenhuis/trap_beneden_1lijn.txt";
    sprites['O'] = "assets/sprites/binnenhuis/pc_1lijn.txt";
    sprites['P'] = "assets/sprites/binnenhuis/pc2_1lijn.txt";
    sprites['Q'] = "assets/sprites/binnenhuis/plant1_1lijn.txt";
    sprites['U'] = "assets/sprites/binnenhuis/plant2_1lijn.txt";
    sprites['Y'] = "assets/sprites/binnenhuis/doolhof1_1lijn.txt";
    sprites['Z'] = "assets/sprites/binnenhuis/doolhof2_1lijn.txt";
    sprites['{'] = "assets/sprites/binnenhuis/doolhof1_onder_1lijn.txt";
    sprites['}'] = "assets/sprites/binnenhuis/doolhof2_onder_1lijn.txt";
    sprites['['] = "assets/sprites/binnenhuis/boekenkast1_1lijn.txt";
    sprites[']'] = "assets/sprites/binnenhuis/boekenkast2_1lijn.txt";
    sprites['='] = "assets/sprites/binnenhuis/stoel_1lijn.txt";
    sprites['+'] = "assets/sprites/oak_1lijn.txt";
    sprites[':'] = "assets/sprites/moeder_1lijn.txt";

    // 32x32 Boom sprite.
    sprites['A'] = "assets/boom/boom1_1lijn.txt";
    sprites['B'] = "assets/boom/boom2_1lijn.txt";
    sprites['C'] = "assets/boom/boom3_1lijn.txt";
    sprites['D'] = "assets/boom/boom4_1lijn.txt";

    // Alle buiten gebouw sprite onderdelen.
    sprites['f'] = "assets/gebouwen/huis1oak1_1lijn.txt";
    sprites['g'] = "assets/gebouwen/huis23oak234_1lijn.txt";
    sprites['h'] = "assets/gebouwen/huis4oak5_1lijn.txt";
    sprites['i'] = "assets/gebouwen/huis5oak6_1lijn.txt";
    sprites['j'] = "assets/gebouwen/huis6_1lijn.txt";
    sprites['k'] = "assets/gebouwen/huis7_1lijn.txt";
    sprites['l'] = "assets/gebouwen/huis8oak10_1lijn.txt";
    sprites['m'] = "assets/gebouwen/huis9oak11_1lijn.txt";
    sprites['n'] = "assets/gebouwen/huis10oak12_1lijn.txt";
    sprites['o'] = "assets/gebouwen/huis11_1lijn.txt";
    sprites['p'] = "assets/gebouwen/huis12_1lijn.txt";
    sprites['q'] = "assets/gebouwen/oak7_1lijn.txt";
    sprites['r'] = "assets/gebouwen/oak8_1lijn.txt";
    sprites['s'] = "assets/gebouwen/oak9_1lijn.txt";
    sprites['t'] = "assets/gebouwen/oak13_1lijn.txt";
    sprites['u'] = "assets/gebouwen/oak14_1lijn.txt";
    sprites['v'] = "assets/gebouwen/oak15_1lijn.txt";
    sprites['w'] = "assets/gebouwen/huis6no_1lijn.txt";
}