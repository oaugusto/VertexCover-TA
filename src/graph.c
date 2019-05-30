#include <stdio.h>
#include <stdlib.h>

#include "../include/graph.h"

graph* makeGraph(int size) {
    V_t i = 0;

    if (size < 0) {
        return NULL;
    }

    //graph struct
    graph* g = (graph*)malloc(sizeof(graph));
    
    g->nNodes = size;
    g->nEdges = 0;

    //adjacent list of edges
    g->edges = (pointer*)malloc(size * sizeof(pointer));

    for (i = 0; i < size; i++) {
        g->edges[i] = NULL;
    }

    return g;
}

int isEdge(graph* g, int a, int b) {
    pointer next = NULL;

    if (a < 0 || b < 0) {
        printf("erro: isEdge\n");
        return -1;
    }

    next = g->edges[a];

    while (next != NULL) {
        if (next->id == b) {
            return 1;
        }

        next = next->next;
    }

    return 0;

}

void insertEdge(graph* g, int a, int b, W_t w) {

    if (a < 0 || b < 0 || a >= g->nNodes || b >= g->nNodes) {
        printf("erro: insertEdge(invalid values: %d, %d)\n", a, b);
        return;
    }

    pointer e1 = (pointer)malloc(sizeof(edge));
    pointer e2 = (pointer)malloc(sizeof(edge));

    //insert first edge
    e1->id = b;
    e1->weight = w;
    e1->next = g->edges[a];
    g->edges[a] = e1;

    //second edge
    e2->id = a;
    e2->weight = w;
    e2->next = g->edges[b];
    g->edges[b] = e2;

    //increment the number of edges,
    //considering only one edge between a and b
    g->nEdges++;

}

void printGraph(graph* g) {
    int i = 0;
    pointer next = NULL;

    for (i = 0; i < g->nNodes; i++) {

        printf("node %d:", i);

        for (next = g->edges[i]; next != NULL; next = next->next) {
            printf(" %d", next->id);
        }

        printf("\n");
    }

}

void removeEdge(graph* g, int a, int b) {
    pointer prev = NULL;
    pointer next = g->edges[a];

    if (next == NULL) {
        printf("Error: no edge to delete!\n");
        return;
    }

    //delete edge from a to b

    while (next != NULL && next->id != b) {
        prev = next;
        next = next->next;
    }

    if (next == NULL) {
        printf("Error: no edge (%d, %d)\n", a, b);
        return;
    }

    if (prev == NULL) {
        g->edges[a] = NULL;
        free(next);
    } else { 
        prev->next = next->next;
        free(next);
    }

    //delete edge from b to a

    prev = NULL;
    next = g->edges[b];

    while (next != NULL && next->id != a) {
        prev = next;
        next = next->next;
    }

    if (prev == NULL) {
        g->edges[a] = NULL;
        free(next);
    } else { 
        prev->next = next->next;
        free(next);
    }

    //decrease the number of edges
    g->nEdges--;
}

void removeGraph(graph* g) {
    int i = 0;
    pointer next = NULL;
    pointer tmp = NULL;

    for (i = 0; i < g->nNodes; i++) {

        next = g->edges[i];

        while (next != NULL) {
            tmp = next;
            next = next->next;
            free(tmp);
        }

    }

    free(g);
}
