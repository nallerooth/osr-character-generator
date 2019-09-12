/*
 * =====================================================================================
 *
 *       Filename:  types.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  10/09/19 12:26:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef __TYPES_H__
#define __TYPES_H__

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
    char name[16];
    unsigned char hit_die;
    unsigned short attack_bonus;
    struct saves saves;
};

struct character_race {
    char name[16];
    struct attributes req;
    char abilities[255];
    struct saves save_bonuses;
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

#endif
