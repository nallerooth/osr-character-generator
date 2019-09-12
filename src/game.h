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
};

void game_destroy(struct game *g);

#endif
