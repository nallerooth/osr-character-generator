#include <stdio.h>
#include <stdlib.h>

#include "../common.h"
#include "../game.h"
#include "../types.h"


enum ClassIndex{
    C_CLERIC     = 1,
    C_FIGHTER    = 2,
    C_MAGIC_USER = 4,
    C_THIEF      = 8 };

/* PROTOTYPES */

static void _bf_cleric_saves(struct saves *s);
static void _bf_fighter_saves(struct saves *s);
static void _bf_magic_user_saves(struct saves *s);
static void _bf_thief_saves(struct saves *s);
static void _bf_set_base_reqs(struct character_race *r);
static char _bf_check_valid_attrs(struct character *c);

int bf_character_attr_mod(unsigned int attr);
void bf_roll_hp(struct character *c);

/* PROTOTYPES END */

void
bf_roll_attributes(struct character *c)
{
    do {
        fprintf(stderr, "Rolling attributes..\n");
        c->attrs.st = roll(3, 6);
        c->attrs.de = roll(3, 6);
        c->attrs.co = roll(3, 6);
        c->attrs.in = roll(3, 6);
        c->attrs.wi = roll(3, 6);
        c->attrs.ch = roll(3, 6);
    } while (!_bf_check_valid_attrs(c));
}

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
    r->allowed_classes = C_CLERIC|C_FIGHTER|C_THIEF;
    sprintf(r->name, "Dwarf");
    sprintf(r->desc, "Dwarven");
    sprintf(r->abilities, "Darkvision 60', Stonesense");
    _bf_set_base_reqs(r);
    r->req_min.co = 9;
    r->req_max.ch = 17;
    r->save_bonuses.deathray = 4;
    r->save_bonuses.wand = 4,
    r->save_bonuses.paralyze = 4,
    r->save_bonuses.breath = 3,
    r->save_bonuses.spell = 4;

    r++;
    r->allowed_classes = C_CLERIC|C_FIGHTER|C_MAGIC_USER|C_THIEF;
    sprintf(r->name, "Elf");
    sprintf(r->desc, "Elven");
    sprintf(r->abilities, "Darkvision 60', Observant");
    _bf_set_base_reqs(r);
    r->req_min.in = 9;
    r->req_max.co = 17;
    r->save_bonuses.deathray = 0;
    r->save_bonuses.wand = 2,
    r->save_bonuses.paralyze = 1,
    r->save_bonuses.breath = 0,
    r->save_bonuses.spell = 2;

    r++;
    r->allowed_classes = C_CLERIC|C_FIGHTER|C_THIEF;
    sprintf(r->name, "Halfling");
    sprintf(r->desc, "Halfling");
    sprintf(r->abilities, "Accurate, Hinding bonus");
    _bf_set_base_reqs(r);
    r->req_min.de = 9;
    r->req_max.st = 17;
    r->save_bonuses.deathray = 4;
    r->save_bonuses.wand = 4,
    r->save_bonuses.paralyze = 4,
    r->save_bonuses.breath = 3,
    r->save_bonuses.spell = 4;

    r++;
    r->allowed_classes = C_CLERIC|C_FIGHTER|C_MAGIC_USER|C_THIEF;
    sprintf(r->name, "Human");
    sprintf(r->desc, "Human");
    sprintf(r->abilities, "10%% extra XP");
    _bf_set_base_reqs(r);
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
    _bf_cleric_saves(&c->saves);
    c->req.wi = 9;

    c++;
    sprintf(c->name, "Fighter");
    c->hit_die = 8u;
    c->attack_bonus = 1u;
    _bf_fighter_saves(&c->saves);
    c->req.st = 9;

    c++;
    sprintf(c->name, "Magic-User");
    c->hit_die = 4u;
    c->attack_bonus = 1u;
    _bf_magic_user_saves(&c->saves);
    c->req.in = 9;

    c++;
    sprintf(c->name, "Thief");
    c->hit_die = 4u;
    c->attack_bonus = 1u;
    _bf_thief_saves(&c->saves);
    c->req.de = 9;
}

static void
_bf_cleric_saves(struct saves *s)
{
    s->deathray = 11u;
    s->wand = 12u;
    s->paralyze = 14u;
    s->breath = 16u;
    s->spell = 15u;
}

static void
_bf_fighter_saves(struct saves *s)
{
    s->deathray = 12u;
    s->wand = 13u;
    s->paralyze = 14u;
    s->breath = 15u;
    s->spell = 17u;
}

static void
_bf_magic_user_saves(struct saves *s)
{
    s->deathray = 13u;
    s->wand = 14u;
    s->paralyze = 13u;
    s->breath = 16u;
    s->spell = 15u;
}

static void
_bf_thief_saves(struct saves *s)
{
    s->deathray = 13u;
    s->wand = 14u;
    s->paralyze = 13u;
    s->breath = 16u;
    s->spell = 15u;
}

static char
_bf_check_valid_attrs(struct character *c)
{
    return c->attrs.st >= 9 ||
        c->attrs.de >= 9 ||
        c->attrs.in >= 9 ||
        c->attrs.wi >= 9;
}

static void _bf_set_base_reqs(struct character_race *r)
{
    r->req_min.st = 3;
    r->req_min.de = 3;
    r->req_min.co = 3;
    r->req_min.in = 3;
    r->req_min.wi = 3;
    r->req_min.ch = 3;

    r->req_max.st = 18;
    r->req_max.de = 18;
    r->req_max.co = 18;
    r->req_max.in = 18;
    r->req_max.wi = 18;
    r->req_max.ch = 18;
}

void
bf_roll_hp(struct character *c)
{
    int hp = (rand() % c->cls->hit_die) + 1;
    hp += bf_character_attr_mod(c->attrs.co);

    c->hp = hp > 0 ? hp : 1;
}

int
bf_character_attr_mod(unsigned int attr)
{
    if (attr <= 3) return -3;
    if (attr <= 5) return -2;
    if (attr <= 8) return -1;
    if (attr <= 12) return 0;
    if (attr <= 15) return 1;
    if (attr <= 17) return 2;
    return 3;
}

struct game *
bf_game_create()
{
    struct game *g = malloc(sizeof(struct game));
    if (g == NULL) {
        fprintf(stderr, "Unable to allocate memory for game, exiting");
        exit(1);
    }

    // Populate game struct with rule specific funtions
    g->roll_hp = bf_roll_hp;
    g->roll_attributes = bf_roll_attributes;
    g->attr_mod = bf_character_attr_mod;
    bf_add_races(g);
    bf_add_classes(g);

    return g;

}
