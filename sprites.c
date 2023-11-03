#include "sprites.h"

// Globale character pointer array van alle sprites.
char *sprites[128];

// Laad alle sprites in de char pointer array.
void sprite_array(void) {
    // Simpele pokemon sprites.
    sprites['a'] = "assets/pokemons/charmander.txt";
    sprites['b'] = "assets/pokemons/bulbasaur.txt";
    sprites['c'] = "assets/pokemons/squirtle.txt";

    // Alle standaard 16x16 buiten sprites
    sprites['X'] = "assets/sprites/valstrik.txt";
    sprites['#'] = "assets/sprites/steen.txt";
    sprites[' '] = "assets/sprites/ondergrond.txt";
    sprites[';'] = "assets/sprites/ondergrond2.txt";
    sprites['G'] = "assets/sprites/gras.txt";
    sprites['L'] = "assets/sprites/niks.txt";
    sprites['S'] = "assets/sprites/bosje.txt";
    sprites['W'] = "assets/sprites/water2.txt";
    sprites['_'] = "assets/sprites/springmuur.txt";
    sprites['-'] = "assets/sprites/niks_tp.txt";
    sprites['<'] = "assets/sprites/niks_tp.txt";

    // Alle water gerelateerde sprites
    sprites['W'] = "assets/sprites/water/water2.txt";
    sprites['!'] = "assets/sprites/water/waterkant_boven.txt";
    sprites['@'] = "assets/sprites/water/waterkant_links.txt";
    sprites['^'] = "assets/sprites/water/waterkant_rechts.txt";
    sprites['&'] = "assets/sprites/water/waterkant_linksehoek.txt";
    sprites['%'] = "assets/sprites/water/waterkant_rechtsehoek.txt";

    // Alle 16x16 sprites binnen gebouwen.
    sprites['V'] = "assets/sprites/binnenhuis/vloer.txt";
    sprites['>'] = "assets/sprites/binnenhuis/vloer_oak.txt";
    sprites['M'] = "assets/sprites/binnenhuis/muur.txt";
    sprites['R'] = "assets/sprites/binnenhuis/raam.txt";
    sprites['T'] = "assets/sprites/binnenhuis/trap.txt";
    sprites['E'] = "assets/sprites/binnenhuis/tv.txt";
    sprites['H'] = "assets/sprites/binnenhuis/bed1.txt";
    sprites['I'] = "assets/sprites/binnenhuis/bed2.txt";
    sprites['N'] = "assets/sprites/binnenhuis/nes.txt";
    sprites['J'] = "assets/sprites/binnenhuis/deurmat.txt";
    sprites['K'] = "assets/sprites/binnenhuis/trap_beneden.txt";
    sprites['O'] = "assets/sprites/binnenhuis/pc.txt";
    sprites['P'] = "assets/sprites/binnenhuis/pc2.txt";
    sprites['Q'] = "assets/sprites/binnenhuis/plant1.txt";
    sprites['U'] = "assets/sprites/binnenhuis/plant2.txt";
    sprites['Y'] = "assets/sprites/binnenhuis/doolhof1.txt";
    sprites['Z'] = "assets/sprites/binnenhuis/doolhof2.txt";
    sprites['{'] = "assets/sprites/binnenhuis/doolhof1_onder.txt";
    sprites['}'] = "assets/sprites/binnenhuis/doolhof2_onder.txt";
    sprites['['] = "assets/sprites/binnenhuis/boekenkast1.txt";
    sprites[']'] = "assets/sprites/binnenhuis/boekenkast2.txt";
    sprites['='] = "assets/sprites/binnenhuis/stoel.txt";
    sprites['+'] = "assets/sprites/oak.txt";
    sprites[':'] = "assets/sprites/moeder.txt";

    // 32x32 Boom sprite.
    sprites['A'] = "assets/boom/boom1.txt";
    sprites['B'] = "assets/boom/boom2.txt";
    sprites['C'] = "assets/boom/boom3.txt";
    sprites['D'] = "assets/boom/boom4.txt";

    // Alle buiten gebouw sprite onderdelen.
    sprites['f'] = "assets/gebouwen/huis1oak1.txt";
    sprites['g'] = "assets/gebouwen/huis23oak234.txt";
    sprites['h'] = "assets/gebouwen/huis4oak5.txt";
    sprites['i'] = "assets/gebouwen/huis5oak6.txt";
    sprites['j'] = "assets/gebouwen/huis6.txt";
    sprites['k'] = "assets/gebouwen/huis7.txt";
    sprites['l'] = "assets/gebouwen/huis8oak10.txt";
    sprites['m'] = "assets/gebouwen/huis9oak11.txt";
    sprites['n'] = "assets/gebouwen/huis10oak12.txt";
    sprites['o'] = "assets/gebouwen/huis11.txt";
    sprites['p'] = "assets/gebouwen/huis12.txt";
    sprites['q'] = "assets/gebouwen/oak7.txt";
    sprites['r'] = "assets/gebouwen/oak8.txt";
    sprites['s'] = "assets/gebouwen/oak9.txt";
    sprites['t'] = "assets/gebouwen/oak13.txt";
    sprites['u'] = "assets/gebouwen/oak14.txt";
    sprites['v'] = "assets/gebouwen/oak15.txt";
    sprites['w'] = "assets/gebouwen/huis6no.txt";
}