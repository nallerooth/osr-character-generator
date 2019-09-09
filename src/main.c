/*
 * =====================================================================================
 *
 *      Filename:  main.c
 *
 *      Description:  A basic character generator for Basic Fantasy
 *
 *      Version:  1.0
 *      Created:  09/09/19 12:16:13
 *      Revision:  none
 *      Compiler:  gcc
 *
 *      Author:  Nalle Rooth (nalle.rooth@gmail.com)
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum character_classes {C_CLERIC, C_FIGHTER, C_MAGIC_USER, C_THIEF};
enum character_races {R_DWARF, R_ELF, R_HALFLING, R_HUMAN};

struct attributes {
    int st;
    int de;
    int co;
    int in;
    int wi;
    int ch;
};

struct saves {
    unsigned short deathray;
    unsigned short wand;
    unsigned short paralyze;
    unsigned short breath;
    unsigned short spell;
};

struct character_class {
    char name[11];
    unsigned char hit_dice;
    struct saves saves;
};

struct character_race {
    char name[9];
    struct attributes req;
    char abilities[255];
};

struct item {
    char name[16];
    unsigned int qty;
};

struct character {
    char name[20];
    struct attributes attrs;
    unsigned short cls;
    unsigned short lvl;
    struct item inventory[5];
};

int roll(int ndie, int sides)
{
    int val = 0;
    while (ndie-- > 0) {
        val += (random() % sides) + 1;
    }
    return val;
}

void
character_create(struct character *c) {
    c->attrs.st = roll(3, 6);
    c->attrs.de = roll(3, 6);
    c->attrs.co = roll(3, 6);
    c->attrs.in = roll(3, 6);
    c->attrs.wi = roll(3, 6);
    c->attrs.ch = roll(3, 6);


}

int
character_attr_mod(int attr)
{
    if (attr <= 3) return -3;
    if (attr <= 5) return -2;
    if (attr <= 8) return -1;
    if (attr <= 12) return  0;
    if (attr <= 15) return 1;
    if (attr <= 17) return 2;
    if (attr <= 18) return 3;
}

void
character_print(struct character *c)
{
    const char attrf[] = {"  %s:\t%2d [%+d]\n"};
    printf(attrf, "STR", c->attrs.st, character_attr_mod(c->attrs.st));
    printf(attrf, "DEX", c->attrs.de, character_attr_mod(c->attrs.de));
    printf(attrf, "CON", c->attrs.co, character_attr_mod(c->attrs.co));
    printf(attrf, "INT", c->attrs.in, character_attr_mod(c->attrs.in));
    printf(attrf, "WIS", c->attrs.wi, character_attr_mod(c->attrs.wi));
    printf(attrf, "CHA", c->attrs.ch, character_attr_mod(c->attrs.ch));
}

int
main ()
{
    srand(time(NULL));

    struct character c;
    character_create(&c);

    character_print(&c);
}
