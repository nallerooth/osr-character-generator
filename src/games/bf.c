#include <stdio.h>
#include <stdlib.h>

#include "../game.h"
#include "../types.h"

static void
bf_add_races_and_classes(struct game *g)
{
    g->num_races = 4;

    g->races = malloc(sizeof(struct character_race) * g->num_races);
    if (g->races == NULL) {
        fprintf(stderr, "Unable to allocate memory for races, exiting");
        exit(1);
    }

    // Races
    struct character_race *r = &g->races[0];

    sprintf(r->name, "Dwarf");
    sprintf(r->abilities, "Darkvision 60', Stonesense");
    r->req.co = 9;
    r->save_bonuses.deathray = 4;
    r->save_bonuses.wand = 4,
    r->save_bonuses.paralyze = 4,
    r->save_bonuses.breath = 3,
    r->save_bonuses.spell = 4;

    r++;
    sprintf(r->name, "Elf");
    sprintf(r->abilities, "Darkvision 60', Observant");
    r->save_bonuses.deathray = 0;
    r->save_bonuses.wand = 2,
    r->save_bonuses.paralyze = 1,
    r->save_bonuses.breath = 0,
    r->save_bonuses.spell = 2;

    r++;
    sprintf(r->name, "Halfling");
    sprintf(r->abilities, "Accurate, Hinding bonus");
    r->req.de = 9;
    r->save_bonuses.deathray = 4;
    r->save_bonuses.wand = 4,
    r->save_bonuses.paralyze = 4,
    r->save_bonuses.breath = 3,
    r->save_bonuses.spell = 4;

    r++;
    sprintf(r->name, "Human");
    sprintf(r->abilities, "10%% extra XP");
    /*r->save_bonuses.deathray = 0;*/
    /*r->save_bonuses.wand = 0,*/
    /*r->save_bonuses.paralyze = 0,*/
    /*r->save_bonuses.breath = 0,*/
    /*r->save_bonuses.spell = 0;*/

    // Classes
    g->num_classes = 4;
    g->classes = malloc(sizeof(struct character_class) * g->num_classes);
}

struct game *
bf_game_create()
{
    struct game *g = malloc(sizeof(struct game));
    if (g == NULL) {
        fprintf(stderr, "Unable to allocate memory for game, exiting");
        exit(1);
    }

    bf_add_races_and_classes(g);

    return g;

}
