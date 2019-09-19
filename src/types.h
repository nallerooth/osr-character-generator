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
    unsigned int st;
    unsigned int de;
    unsigned int co;
    unsigned int in;
    unsigned int wi;
    unsigned int ch;
};

struct saves {
    unsigned short deathray;
    unsigned short wand;
    unsigned short paralyze;
    unsigned short breath;
    unsigned short spell;
};

struct character_class {
    unsigned int class_id;
    char name[20];
    unsigned char hit_die;
    unsigned short attack_bonus;
    struct saves saves;
    struct attributes req;
};

struct character_race {
    unsigned int allowed_classes;
    char name[16];
    char desc[16];
    char abilities[255];
    struct attributes req_min;
    struct attributes req_max;
    struct saves save_bonuses;
};

struct item {
    char name[16];
    unsigned int qty;
};

struct character {
    char name[20];
    struct attributes attrs;
    struct character_race *race;
    struct character_class *cls;
    unsigned short lvl;
    unsigned int hp;
    struct item inventory[5];
};

#endif
