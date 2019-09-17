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
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "types.h"
#include "game.h"
#include "rulesets/basic_fantasy.h"

static int check_race_requirements(struct character_race *r, struct character *c)
{
    return
        c->attrs.st >= r->req_min.st && c->attrs.st <= r->req_max.st &&
        c->attrs.de >= r->req_min.de && c->attrs.de <= r->req_max.de &&
        c->attrs.co >= r->req_min.co && c->attrs.co <= r->req_max.co &&
        c->attrs.in >= r->req_min.in && c->attrs.in <= r->req_max.in &&
        c->attrs.wi >= r->req_min.wi && c->attrs.wi <= r->req_max.wi &&
        c->attrs.ch >= r->req_min.ch && c->attrs.ch <= r->req_max.ch;
}


static int check_class_requirements(struct character_class *cl, struct character *c)
{
    return
        c->attrs.st >= cl->req.st &&
        c->attrs.de >= cl->req.de &&
        c->attrs.co >= cl->req.co &&
        c->attrs.in >= cl->req.in &&
        c->attrs.wi >= cl->req.wi &&
        c->attrs.ch >= cl->req.ch;
}

void
character_create(struct character *c, struct game *g) {

    /* At least one of STR, DEX, INT or WIS will be 9 or higher, allowing at
     * least one of the base classes. Also, humans can have any attributes,
     * so at least one race will be available. */
    g->roll_attributes(c);


    int num_valid_races = 0;
    int *valid_races = malloc(sizeof(int) * g->num_races);
    memset(valid_races, 0, sizeof(*valid_races));

    /* Race */
    for (int i = 0; i < g->num_races; i++) {
        if (check_race_requirements(&g->races[i], c)) {
            valid_races[num_valid_races++] = i;
        }
    }

    if (num_valid_races == 0) {
        fprintf(stderr, "No valid races for given attributes. Exiting.");
        exit(1);
    }
    unsigned int rce = rand() % num_valid_races;
    c->race = &g->races[rce];

    /* Class */
    int num_valid_classes = 0;
    int *valid_classes = malloc(sizeof(int) * g->num_races);
    memset(valid_classes, 0, sizeof(*valid_classes));


    for (int i = 0; i < g->num_classes; i++) {
        if (check_class_requirements(&g->classes[i], c)) {
            valid_classes[num_valid_classes++] = i;
        }
    }

    if (num_valid_classes == 0) {
        fprintf(stderr, "No valid classes for given attributes. Exiting.");
        exit(1);
    }
    unsigned int cls = rand() % num_valid_classes;
    c->race = &g->races[rce];

    printf("Attributes: %2d %2d %2d %2d %2d %2d\n",
            c->attrs.st,
            c->attrs.de,
            c->attrs.co,
            c->attrs.in,
            c->attrs.wi,
            c->attrs.ch);
    printf("Classes: ");
    for(int i = 0; i < num_valid_classes; i++) {
        printf(" %d", valid_classes[i]);
    }

    exit(0);
    /* Attempt to assign the most suitable class for the race */

    unsigned int cls2, cls_id;
    do {
        cls = rand() % g->num_classes;
        /* Can the selected race have the current class? */
        cls_id = pow(2, cls); // Class array index to bitmask
        if ((c->race->allowed_classes & cls_id) != cls_id) {
            continue;
        }

        struct character_class *rc = &g->classes[cls];
        if (c->attrs.st >= rc->req.st &&
            c->attrs.de >= rc->req.de &&
            c->attrs.co >= rc->req.co &&
            c->attrs.in >= rc->req.in &&
            c->attrs.wi >= rc->req.wi &&
            c->attrs.ch >= rc->req.ch)
        {
            /* Requirements are met -> assign class */
            c->cls = &g->classes[cls];
        } else {
            printf("Missing primary attribute for class %s\n", g->classes[cls].name);
        }
    } while (c->cls == NULL);

    /* Roll hitpoints */
    g->roll_hp(c);

    sprintf(c->name, "Unnamed Char");
    c->lvl = 1u;

    /* Cleanup */
    free(valid_races);
    free(valid_classes);
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
    printf("  %s\t\tAB: %u\n", de, c->cls->attack_bonus);
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
