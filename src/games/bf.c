#include <stdio.h>
#include <stdlib.h>

#include "../game.h"
#include "../types.h"

static void bf_cleric_saves(struct saves *s);
static void bf_fighter_saves(struct saves *s);
static void bf_magic_user_saves(struct saves *s);
static void bf_thief_saves(struct saves *s);

static void
bf_add_races(struct game *g)
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

}

static void
bf_add_classes(struct game *g)
{
    // Classes
    g->num_classes = 4;
    g->classes = malloc(sizeof(struct character_class) * g->num_classes);

    struct character_class *c = &g->classes[0];
    sprintf(c->name, "Cleric");
    c->hit_die = 6u;
    c->attack_bonus = 1u;
    bf_cleric_saves(&c->saves);

    c++;
    sprintf(c->name, "Fighter");
    c->hit_die = 8u;
    c->attack_bonus = 1u;
    bf_fighter_saves(&c->saves);

    c++;
    sprintf(c->name, "Magic-User");
    c->hit_die = 4u;
    c->attack_bonus = 1u;
    bf_magic_user_saves(&c->saves);

    c++;
    sprintf(c->name, "Thief");
    c->hit_die = 4u;
    c->attack_bonus = 1u;
    bf_thief_saves(&c->saves);
}

static void
bf_cleric_saves(struct saves *s)
{
    s->deathray = 11u;
    s->wand = 12u;
    s->paralyze = 14u;
    s->breath = 16u;
    s->spell = 15u;
}

static void
bf_fighter_saves(struct saves *s)
{
    s->deathray = 12u;
    s->wand = 13u;
    s->paralyze = 14u;
    s->breath = 15u;
    s->spell = 17u;
}

static void
bf_magic_user_saves(struct saves *s)
{
    s->deathray = 13u;
    s->wand = 14u;
    s->paralyze = 13u;
    s->breath = 16u;
    s->spell = 15u;
}

static void
bf_thief_saves(struct saves *s)
{
    s->deathray = 13u;
    s->wand = 14u;
    s->paralyze = 13u;
    s->breath = 16u;
    s->spell = 15u;
}

struct game *
bf_game_create()
{
    struct game *g = malloc(sizeof(struct game));
    if (g == NULL) {
        fprintf(stderr, "Unable to allocate memory for game, exiting");
        exit(1);
    }

    bf_add_races(g);
    bf_add_classes(g);

    return g;

}
