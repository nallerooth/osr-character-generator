#include <stdlib.h>

#include "game.h"

void
game_destroy(struct game *g)
{
    free(g->classes);
    free(g->races);
}
