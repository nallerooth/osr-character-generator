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
character_create(struct character *c, struct game *g) {
    c->attrs.st = roll(3, 6);
    c->attrs.de = roll(3, 6);
    c->attrs.co = roll(3, 6);
    c->attrs.in = roll(3, 6);
    c->attrs.wi = roll(3, 6);
    c->attrs.ch = roll(3, 6);

    sprintf(c->name, "Unnamed Char");
    c->lvl = 1u;

    // Race
    unsigned int rce = rand() % g->num_races;
    c->race = &g->races[rce];

    // Class
    unsigned int cls = rand() % g->num_classes;
    c->cls = &g->classes[cls];

    // Roll hitpoints
    g->roll_hp(c);
}

void
character_print(struct character *c, struct game *g)
{
    /* ATTRIBUTES */
    unsigned int attrlen = 14;
    char st[attrlen],
         de[attrlen],
         co[attrlen],
         in[attrlen],
         wi[attrlen],
         ch[attrlen];

    const char attrf[] = {"%s:\t%2d [%+d]"};
    sprintf(st, attrf, "STR", c->attrs.st, g->attr_mod(c->attrs.st));
    sprintf(de, attrf, "DEX", c->attrs.de, g->attr_mod(c->attrs.de));
    sprintf(co, attrf, "CON", c->attrs.co, g->attr_mod(c->attrs.co));
    sprintf(in, attrf, "INT", c->attrs.in, g->attr_mod(c->attrs.in));
    sprintf(wi, attrf, "WIS", c->attrs.wi, g->attr_mod(c->attrs.wi));
    sprintf(ch, attrf, "CHA", c->attrs.ch, g->attr_mod(c->attrs.ch));

    /* ATTRIBUTES END */





    /* OUTPUT */
    printf("\n%s :: %s %s \tLevel: %u\n",
            c->name,
            c->race->desc,
            c->cls->name,
            c->lvl);

    printf("--------------------------------------------------------------------------------\n");

    printf("  %s\t\tHP: %u\n", st, c->hp);
    printf("  %s\t\t\n", de);
    printf("  %s\t\t\n", co);
    printf("  %s\t\t\n", in);
    printf("  %s\t\t\n", wi);
    printf("  %s\t\t\n", ch);
    /* OUTPUT END */

}

int
main ()
{
    srand(time(NULL));

    // Setup game rules
    struct game *g = bf_game_create();

    struct character c;
    character_create(&c, g);

    character_print(&c, g);


    /*
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

    printf("\n");

    for (int i=0; i<g->num_classes; i++) {
        printf("%s, HD: %u, AB: %u, Saves: [%u, %u, %u, %u, %u]\n",
                g->classes[i].name,
                g->classes[i].hit_die,
                g->classes[i].attack_bonus,
                g->classes[i].saves.deathray,
                g->classes[i].saves.wand,
                g->classes[i].saves.paralyze,
                g->classes[i].saves.breath,
                g->classes[i].saves.spell);
    }
    */
    game_destroy(g);
}
