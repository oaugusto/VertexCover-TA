#ifndef GRAPH_H
#define GRAPH_H

#include "types.h"

typedef struct edge* pointer;

typedef struct edge {
    V_t id;
    W_t weight;
    pointer next;
} edge;

typedef struct graph {
    int nNodes;
    int nEdges;
    pointer* edges; 
} graph;

graph* makeGraph(int size);

int isEdge(graph* g, int a, int b);

void insertEdge(graph* g, int a, int b, W_t w);

void removeEdge(graph* g, int a, int b);

void printGraph(graph* g);

void removeGraph(graph* g);

#endif
