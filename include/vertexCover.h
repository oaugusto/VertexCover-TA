#ifndef VERTEXCOVER_H
#define VERTEXCOVER_H

#include <stdlib.h>
#include "graph.h"

V_t min(V_t x, V_t y);

/* Find the minimum vertex cover for a tree using dynamic programming */
V_t vertexCoverTreeSolver(graph *tree, V_t root);

V_t vertexCoverHeuristic(graph* tree);

#endif