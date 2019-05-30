#ifndef VERTEXCOVER_H
#define VERTEXCOVER_H

#include <stdlib.h>
#include "graph.h"

V_t min(V_t x, V_t y);

V_t vertexCoverTreeSolver(graph *g, V_t root);

#endif