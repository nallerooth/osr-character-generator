/*
 * ============================================================================
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
 * ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "types.h"
#include "game.h"
#include "games/bf.h"

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

    struct game *g = bf_game_create();

    printf("Num Races: %d\n", g->num_races);

    for (int i=0; i<g->num_races; i++) {
        printf("%s, Requirements: %d, %d, %d, %d, %d, %d Saves: %d, %d, %d, %d, %d, Special abilities: %s\n",
                g->races[i].name,
                g->races[i].req.st,
                g->races[i].req.de,
                g->races[i].req.co,
                g->races[i].req.in,
                g->races[i].req.wi,
                g->races[i].req.ch,
                g->races[i].save_bonuses.deathray,
                g->races[i].save_bonuses.wand,
                g->races[i].save_bonuses.paralyze,
                g->races[i].save_bonuses.breath,
                g->races[i].save_bonuses.spell,
                g->races[i].abilities);
    }

    game_destroy(g);
}
