/*
 * =====================================================================================
 *
 *       Filename:  game.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  10/09/19 12:22:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */

#ifndef __GAME_H__
#define __GAME_H__

#include "types.h"

struct game {
    struct character_class *classes;
    int num_classes;

    struct character_race *races;
    int num_races;

     void (*roll_hp)(struct character *c);
     void (*roll_attributes)(struct character *c);
     int (*get_valid_races)(int *valid, struct game *g, struct character *c);
     int (*attr_mod)(unsigned int attr);
};

void game_destroy(struct game *g);

#endif
