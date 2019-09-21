#include "basic_fantasy_test.h"
#include "../lib/minunit.h"
#include "../../src/rulesets/basic_fantasy.h"

char * test_bf_character_attr_mod()
{
    mu_assert("Mod for value 3 should be -3", bf_character_attr_mod(3u) == -3);
    mu_assert("Mod for value 5 should be -2", bf_character_attr_mod(5u) == -2);
    mu_assert("Mod for value 8 should be -1", bf_character_attr_mod(8u) == -1);
    mu_assert("Mod for value 9 should be 0",  bf_character_attr_mod(9u) == 0);
    mu_assert("Mod for value 12 should be 0",  bf_character_attr_mod(12u) == 0);
    mu_assert("Mod for value 14 should be +1", bf_character_attr_mod(14u) == 1);
    mu_assert("Mod for value 16 should be +2", bf_character_attr_mod(16u) == 2);
    mu_assert("Mod for value 18 should be +3", bf_character_attr_mod(18u) == 3);
    mu_assert("Mod for value >18 should be +3", bf_character_attr_mod(20u) == 3);

    return 0;
}
