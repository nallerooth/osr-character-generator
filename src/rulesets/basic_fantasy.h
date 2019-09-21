#ifndef __GAMES_BF_H__
#define __GAMES_BF_H__

#include "../types.h"

struct game * bf_game_create();
/* Attributes will be valid for at least one of the base classes */
void bf_roll_attributes(struct character *c);

int bf_character_attr_mod(unsigned int attr);
void bf_roll_hp(struct character *c);
#endif
